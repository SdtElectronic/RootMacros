#include "util.h"

auto FFTP(const TF1& func, int pts, const char* opt = " ", double ll = 0, double hl = 0){
	
	double in1[pts]; 
	TVirtualFFT *fft1 = TVirtualFFT::FFT(1, &pts, "R2C K");
	ll = func.GetXmin();
	hl = func.GetXmax();
	for (int i=0; i<pts; i++){
		double ix   = ll + (hl-ll)/(pts-1)*i;
		in1[i] = limP(func, ix);
	}
	fft1->SetPoints(in1);
	fft1 -> Transform();

	Double_t re, im;
						 
	for (int i=0;i<=pts;i++){
		fft1 -> GetPointComplex(i,re,im);
		printf("%f %f\n", re, im);
    }
							   
    delete fft1;
    return 0;
}
