auto intP(const TF1& func, double ll, double ul, double C, double epsilon = 1.e-3, double epsrel = 1.e-12){
	size_t npx = (ul - ll)/epsilon + 1;
	auto tgp = std::make_shared<TGraph>(npx);
	double ax = ll;
	tgp->SetPoint(0, ax, C);
	for(size_t ix = 1; ix != npx; ++ix){
		tgp->SetPoint(ix, ax, const_cast<TF1&>(func).Integral(ll, ax, epsrel) + C);
		ax += epsilon;
	}
	auto lmb = [tgp](const double* x, const double* p){return tgp->Eval(x[0]);};
	return std::make_shared<TF1>(func.GetName(), lmb, ll, ul, 0);
}

auto intP(const TF1& func, double ll, double ul){
	return intP(func, ll, ul, const_cast<TF1&>(func).Integral(func.GetXmin(), ll));
}

auto intP(const TF1& func){	
	return intP(func, func.GetXmin(), func.GetXmax(), 0);
}
