class TFFT{	
	public:
	TFFT(): points(0),
			lowerlim(0),
			uperlim(0),
			tuperlim(0),
			fft1(nullptr),
			TGFmag(),
			TGFphi(),
			TGFcmp(){

	}
	template<typename T>
	TFFT(const T& cont, int pts, double ll, double ul, const char* opt = "R2C K"): points(pts),
																					  lowerlim(ll),
																					  uperlim(ul),
																					  tuperlim(pts / (ul - ll) / 2.),
																					  fft1(TVirtualFFT::FFT(1, &pts, opt)),
																					  TGFmag(pts),
																					  TGFphi(pts),
																					  TGFcmp(pts){	
		for(size_t i = 0; i != pts; ++i)
			fft1->SetPoint(i, cont[i]);
	}
	template<typename T>
	TFFT(const T& cont, int pts, const char* opt = "R2C K"): TFFT(cont, pts, -pts/2, pts/2, opt){

	}

	TFFT(const TF1& func, int pts, double ll, double ul, const char* opt = "R2C K"): TFFT(USamp<TF1>(func, pts, ll, ul), pts, ll, ul, opt){
		
	}
	TFFT(const TF1& func, int pts, const char* opt = "R2C K"): TFFT(func, pts, func.GetXmin(), func.GetXmax(), opt){

	}

	TFFT(const std::vector<double>& cont, double ll, double ul, const char* opt = "R2C K"): TFFT(cont, cont.size(), ll, ul, opt){

	}
	TFFT(const std::vector<double>& cont, const char* opt = "R2C K"): TFFT(cont, cont.size(), opt){

	}

	TFFT& trans(void){
		fft1->Transform();
		double re, im; 
		double fi = -tuperlim;
		double step = 1. / (uperlim - lowerlim);
		for(int i = points / 2; i != points; i++){
        	fft1->GetPointComplex(i, re, im);
        	TGFmag.SetPoint(i, fi, sqrt(re*re + im*im));
			TGFphi.SetPoint(i, fi, atan(im / re));
			TGFcmp.SetPoint(i, fi, re, im);
			fi += step;
		}
		for(int i = 0; i != points / 2; i++){
        	fft1->GetPointComplex(i, re, im);
        	TGFmag.SetPoint(i, fi, sqrt(re*re + im*im));
			TGFphi.SetPoint(i, fi, atan(im / re));
			TGFcmp.SetPoint(i, fi, re, im);
			fi += step;
		}
		return *this;
	}

	auto GetMag(bool norm = true){
		auto TGMcpy = std::make_shared<TGraph>(TGFmag);
		if(norm){
			for(size_t i = 0; i != points; ++i)
				TGMcpy->SetPointY(i, TGMcpy->GetPointY(i)*2/points);
			TGMcpy->SetPointY(points / 2, TGMcpy->GetPointY(points / 2)*2/points);
		}
		auto LFmag = [TGMcpy](const double *x, const double *p){return TGMcpy->Eval(x[0]);};
		return std::make_shared<TF1>("Magnitude", LFmag, -tuperlim, tuperlim, points);
	}

	template<typename T>
	static auto FFTP(const T& cont, int pts, double ll, double ul, const char* opt = "R2C K"){
		return TFFT(cont, pts, ll, ul, opt).trans().GetMag();
	}
	template<typename T>
	static auto FFTP(const T& cont, int pts, const char* opt = "R2C K"){
		return TFFT(cont, pts, opt).trans().GetMag();
	}
	/*
	static std::shared_ptr<TF1> FFTP(const TF1& cont, int pts, const char* opt = "R2C K"){
		//double ll = cont.GetXmin();
		//double ul = cont.GetXmax();
		//return TFFT(USamp<TF1>(cont, pts, ll, ul), pts, ll, ul, opt).trans().GetMag();
		return TFFT(USamp<TF1>(cont, pts, ll, ul), pts, ll, ul, opt).trans().GetMag();
	}
	static std::shared_ptr<TF1> FFTP(const TF1& cont, int pts, double ll, double ul, const char* opt = "R2C K"){
		//return TFFT(USamp<TF1>(cont, pts, ll, ul), pts, ll, ul, opt).trans().GetMag();
	}
	*/
	TComplex operator [](size_t ind){
		double re, im; 
		fft1->GetPointComplex(ind, re, im);
		return TComplex(re, im);
	}

	auto operator ()(bool norm = true){
		auto TGMcpy = std::make_shared<TGraph>(TGFmag);
		auto TGPcpy = std::make_shared<TGraph>(TGFphi);
		auto TGCcpy = std::make_shared<TGraph2D>(TGFcmp);
		if(norm){
			for(size_t i = 0; i != points; ++i)
				TGMcpy->SetPointY(i, TGMcpy->GetPointY(i)*2/points);
			TGMcpy->SetPointY(points / 2, TGMcpy->GetPointY(points / 2)*2/points);
		}
		return make_tuple(TGMcpy, TGPcpy, TGCcpy);
	}

	private:
	size_t points;
	double lowerlim;
	double uperlim;
	double tuperlim;
	std::unique_ptr<TVirtualFFT> fft1;
	TGraph TGFmag;
	TGraph TGFphi;
	TGraph2D TGFcmp;
};
/*

template<>
TFFT::TFFT(std::vector<double> cont, int pts = cont.size(), double ll, double ul, const char* opt = "R2C K"): TFFT(cont, pts, ll, ul, opt){

}

template<>
TFFT::TFFT(std::vector<double> cont, int pts = cont.size(), const char* opt = "R2C K"): TFFT(cont, pts, opt){

}
TFFT::TFFT(const TFFT& cp): points(cp.points),
					  lowerlim(cp.lowerlim),
					  uperlim(cp.uperlim),
					  tuperlim(cp.tuperlim),
					  fft1(new typename std::decay<decltype(cp.fft1)>::type(cp.fft1)),
					  TGFmag(cp.TGFmag),
					  TGFphi(cp.TGFphi),
					  TGFcmp(cp.TGFcmp){
		
}

auto FFTP(const TF1& func, double ll, double hl, int pts = 1000, const char* opt = nullptr){
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

auto FFTP(const TF1& func, int pts = 1000, const char* opt = nullptr){	
	return FFTP(func, func.GetXmin(), func.GetXmax(), pts, opt);
}
*/