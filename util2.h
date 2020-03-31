#pragma once
double limP(const TF1& func, double ix){
	double iy = func.Eval(ix);
	while(isnan(iy) || isinf(iy)){
		ix += numeric_limits<double>().epsilon();
		iy = func.Eval(ix);	
	}
	return iy;
}

template<typename T>
T* DrawP(T objPtr, const char* opt = ""){
	objPtr->Draw(opt);
	return new shared_ptr<typename std::decay<decltype(*objPtr)>::type>(objPtr);
}
/*
auto DrawP(std::shared_ptr<TGraphAsymmErrors> objPtr, const char* opt = "aps"){
	objPtr->Draw(opt);
	printf("%s", opt);
	return new shared_ptr<TGraphAsymmErrors>(objPtr);
}
*/
auto ConvP(const TF1& f1,const TF1& f2, int pts = 1000, double ll = 0, double hl = 0, const char* title = " ", const char* opt = ""){
	if(ll == hl){
		ll = min(f1.GetXmin(), f2.GetXmin());
		hl = max(f1.GetXmax(), f2.GetXmax());
	}
	auto f_conv = make_unique<TF1Convolution>(const_cast<TF1*>(&f1), const_cast<TF1*>(&f2), ll, hl, static_cast<bool>(pts));
	if(pts)
		f_conv->SetNofPointsFFT(pts);
	else
		f_conv->SetNumConv();
	auto fret =  make_shared<TF1>(title, *f_conv, ll, hl, f_conv->GetNpar());
	fret->Draw(opt);
	return fret;
}
#include "stemP.cc"
