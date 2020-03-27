#pragma once

constexpr double infty = numeric_limits<double>().max();
constexpr double delta = numeric_limits<double>().epsilon();

double limP(const TF1& func, double ix){
	double iy = func.Eval(ix);
	while(isnan(iy) || isinf(iy)){
		ix += delta;
		iy = func.Eval(ix);	
	}
	return iy;
}

auto TServ(const char* addr = "http:127.0.0.1:3120"){
	return new THttpServer(addr);
}

template<typename T>
shared_ptr<T>* DrawP(shared_ptr<T> objPtr, const char* opt = nullptr){
	objPtr->Draw(opt);
	return new shared_ptr<T>(objPtr);
}

auto DrawP(const std::shared_ptr<TGraphAsymmErrors> objPtr, const char* opt = "aps"){
	objPtr->Draw(opt);
	return new shared_ptr<TGraphAsymmErrors>(objPtr);
}

auto DrawP(const std::shared_ptr<TF1> objPtr, int npx = 0, const char* opt = nullptr){	
	objPtr->SetNpx(npx ? npx : objPtr->GetNpx());
	objPtr->Draw(opt);
	return new shared_ptr<TF1>(objPtr);
}

double stepU(double x){
	return x < 0 ? 0 : 1;
}

#include "stemP.cc"
#include "ConvP.cc"
#include "intP.cc"
#include "Tz.cc"
