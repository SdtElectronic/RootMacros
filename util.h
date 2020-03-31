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
shared_ptr<T>* DrawP(const shared_ptr<T> objPtr, const char* opt = nullptr){
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

auto DrawP(std::tuple<std::shared_ptr<TF1>, std::shared_ptr<TF1>, std::shared_ptr<TGraph2D>> tp, int npx = 0, const char* opt = nullptr){	
	auto objPtr = std::get<0>(tp);
	objPtr->SetNpx(npx ? npx : objPtr->GetNpx());
	objPtr->Draw(opt);
	return new shared_ptr<TF1>(objPtr);
}

template<typename TO, typename TI>
auto DrawP(shared_ptr<TO> objPtrO, shared_ptr<TI> objPtrI, const char* title = nullptr, int npxO = 1000, double scale2 = 0, const char* optO = nullptr, const char* optI = nullptr){	
	auto c1 = new TCanvas("c1");
	auto pad = new TPad("pad","",0,0,1,1);
	objPtrI->SetTitle(title?title:objPtrO->GetName());
	objPtrO->SetTitle("");
	objPtrO->SetNpx(npxO);
	pad->Draw();
	pad->cd();
	objPtrO->Draw(optO);
	c1->cd();
	auto overlay = new TPad("overlay","",0,0,1,1);
	overlay->SetFillStyle(4000);
	overlay->SetFillColor(0);
	overlay->SetFrameFillStyle(4000);
	overlay->Draw();
	overlay->cd();
	std::string opt(optI?optI:"");
	objPtrI->SetLineColor(kBlue);
	objPtrI->Draw((opt += "Y+").c_str());
	/*
	auto xMax = pad->GetUxmax();
	auto yMin = overlay->GetUymin();
	auto yMax = yMin + (scale2?scale2:1)*(overlay->GetUymax() - yMin);
	auto axis = new TGaxis(xMax, yMin, xMax, yMax, yMin, yMax, 510, "+L");	
	printf("%f %f", yMax, yMin);
	axis->Draw();
	*/
	return new std::pair<shared_ptr<TO>, shared_ptr<TI>>(objPtrO, objPtrI);
}

template<typename TO>
auto DrawP(shared_ptr<TO> objPtrO, shared_ptr<TF1> objPtrI, const char* title = nullptr, int npxO = 1000, double scale2 = 0, const char* optO = nullptr, const char* optI = nullptr){	
	string opt(optI?optI:"");
	return DrawP<TO, TF1>(objPtrO, objPtrI, title, npxO, scale2, optO, (opt += " C").c_str());
}


#include "USamp.cc"
#include "stemP.cc"
#include "ConvP.cc"
#include "intP.cc"
#include "FFTP.cc"
#include "Tz.cc"
