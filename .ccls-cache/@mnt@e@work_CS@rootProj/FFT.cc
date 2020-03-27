#include "util.h"

auto FFTP(const TF1& func, int pts, const char* opt = " ", double ll = 0, double hl = 0){
	//TH1::AddDirectory(kFALSE);
	if(ll == hl){
		ll = func.GetXmin();
		hl = func.GetXmax();
	}
	printf("%f %f", ll, hl);
	TH1D* samp= new TH1D(" ", " ", pts, ll, hl);
	//double ix = ll;
	//double step = (hl - ll) / pts;
	for(int bin = 1; bin <= pts; ++bin){
		double ixx = samp->GetBinCenter(bin);
		samp->SetBinContent(ixx, limP(func, ixx));
//		ix += step;
	}
	TH1* fftd;
	//TVirtualFFT::SetTransform(0);
	fftd = samp->FFT(fftd, "MAG");
	fftd->SetTitle(func.GetName());
	fftd->Draw();
	return fftd;
}
