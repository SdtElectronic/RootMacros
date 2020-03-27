auto intP(const TF1& func, double ll, double ul, double C, double epsrel = 1.e-3){
	long long npx = (ul - ll)/epsrel + 1;
	printf("%lld %f %f %f", npx, ll , ul, epsrel);
	auto tgp = std::make_shared<TGraph>(npx);
	double ax = ll;
	tgp->SetPoint(0, ax, C);
	for(long long ix = 1; ix != npx; ++ix){
		tgp->SetPoint(ix, ax, const_cast<TF1&>(func).Integral(ll, ax) + C);
		ax += epsrel;
	}
	auto lmb = [tgp](const double* x, const double* p){return tgp->Eval(x[0]);};
	return std::make_shared<TF1>(func.GetName(), lmb, ll, ul, 0);
	//return std::make_shared<TF1>(func.GetName(), [&](const double* x, const double* p){return tgp->Eval(x[0]);}, ll, ul);
}

auto intP(const TF1& func, double ll, double ul){
	return intP(func, ll, ul, const_cast<TF1&>(func).Integral(func.GetXmin(), ll));
}

auto intP(const TF1& func){	
	return intP(func, func.GetXmin(), func.GetXmax(), 0);
}
