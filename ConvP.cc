#pragma once

auto ConvP(const TF1& f1,const TF1& f2, unsigned int pts = 1e3, double ll = 0, double hl = 0, const char* title = nullptr){
	if(ll == hl){
		double rang = f1.GetXmax() - f1.GetXmin();
		ll = f2.GetXmin() - rang;
		hl = f2.GetXmax() + rang;
	}
	auto f_conv = make_unique<TF1Convolution>(const_cast<TF1*>(&f1), const_cast<TF1*>(&f2), ll, hl, pts);
	if(pts)
		f_conv->SetNofPointsFFT(pts);
	else
		f_conv->SetNumConv();
	auto fret =  make_shared<TF1>(title, *f_conv, ll, hl, f_conv->GetNpar());
	return fret;
}
