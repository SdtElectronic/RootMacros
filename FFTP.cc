auto FFTP(const TF1& func, int pts = 1000, const char* opt = nullptr, double ll = 0, double hl = 0){
    if(ll == hl){
		ll = func.GetXmin();
		hl = func.GetXmax();
	}
	double y[pts];
	std::unique_ptr<TVirtualFFT> fft1 (TVirtualFFT::FFT(1, &pts, "R2C K"));
    for(int i=0; i!=pts; i++){
        double ix = ll + (hl-ll)/(pts-1.)*i;
        y[i] = limP(func, ix);
    }
    fft1->SetPoints(y);
    fft1->Transform();
    double re, im; 
	double fi = pts / (ll - hl) / 2.;
	double fll = fi;
	double step = 1. / (hl - ll);
	auto TGFmag = std::make_shared<TGraph>(pts);
	auto TGFphi = std::make_shared<TGraph>(pts);
	auto TGFcmp = std::make_shared<TGraph2D>(pts);
    for (int i = pts / 2; i != pts; i++){
        fft1->GetPointComplex(i, re, im);
        TGFmag->SetPoint(i, fi, sqrt(re*re + im*im));
		TGFphi->SetPoint(i, fi, atan(im / re));
		TGFcmp->SetPoint(i, fi, re, im);
		fi += step;
	}
	for (int i = 0; i != pts / 2; i++){
        fft1->GetPointComplex(i, re, im);
        TGFmag->SetPoint(i, fi, sqrt(re*re + im*im));
		TGFphi->SetPoint(i, fi, atan(im / re));
		TGFcmp->SetPoint(i, fi, re, im);
		fi += step;
	}
	auto LFmag = [TGFmag](const double *x, const double *p){return TGFmag->Eval(x[0]);};
	auto LFphi = [TGFphi](const double *x, const double *p){return TGFphi->Eval(x[0]);};
	auto TFFmag = std::make_shared<TF1>("Magnitude", LFmag, fll, fi, pts);
	auto TFFphi = std::make_shared<TF1>("Phase", LFphi, fll, fi, pts);
    return make_tuple(TFFmag, TFFphi, TGFcmp);
}
