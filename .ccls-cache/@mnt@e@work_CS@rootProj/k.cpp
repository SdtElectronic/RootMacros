#include "util.h"

auto FFTP(const TF1& func, int pts, const char* opt = " ", double ll = 0, double hl = 0){
    if(ll == hl){
		ll = func.GetXmin();
		hl = func.GetXmax();
	}
	double y[pts];
	std::unique_ptr<TVirtualFFT> fft1 (TVirtualFFT::FFT(1, &pts, "R2C K"));
	//TVirtualFFT * fft1 = TVirtualFFT::FFT(1, &pts, "R2C K");
    for(int i=0; i!=pts; i++){
        double ix = ll + (hl-ll)/(pts-1.)*i;
        y[i] = limP(func, ix);
		printf("%f\n", y[pts]);
    }
    fft1->SetPoints(y);
    fft1->Transform();
    double re, im; 
	double fi = pts / (ll - hl) / 2.;
	double fll = fi;
	double step = 1. / (hl - ll);
	auto TGFmag = std::make_shared<TGraph>(pts);
	auto TGFphi = std::make_unique<TGraph>(pts);
	auto TGFcmp = std::make_shared<TGraph2D>(pts);
    for (int i = 0; i != pts; i++){
        fft1->GetPointComplex(i, re, im);
		printf("%f %f %f\n", fi, re, im);
        TGFmag->SetPoint(i, fi, sqrt(re*re + im*im));
	//	printf("%f %f %f\n", fi, re, im);
		TGFphi->SetPoint(i, fi, atan(im / re));
		TGFcmp->SetPoint(i, fi, re, im);
		fi += step;
	}
	TGFmag->Draw();
	//TGFmag->SetBit(TGraph::kIsSortedX);
	auto LFmag = std::make_shared<std::function<double(const double*, const double*)> >([&TGFmag](const double *x, const double *p){
				return TGFmag->Eval(x[0]);});
	auto LFphi = std::make_shared<std::function<double(const double*, const double*)> >([&TGFphi](const double *x, const double *p){
				return TGFphi->Eval(x[0]);});
	auto TFFmag = std::make_shared<TF1>("mag", *LFmag, fll, fi, pts);
	//TGFmag->Draw();
	auto TFFphi = std::make_shared<TF1>("phi", *LFphi, fll, fi, pts);
    return make_tuple(TGFmag, TFFphi, TGFcmp);
}
