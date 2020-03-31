auto difP(const TF1& func, double ll, double ul, unsigned int pts = 1e3, double epsilon=0.001){
	auto lmb = [=](const double* x, const double* p){	
		return const_cast<TF1&>(func).Derivative( x[0], nullptr, epsilon);};
	auto ret = std::make_shared<TF1>(func.GetName(), lmb, ll, ul, 0);
	ret->SetNpx(pts);
	return ret;
}

auto difP(const TF1& func, unsigned int pts = 1e3){	
	return difP(func, func.GetXmin(), func.GetXmax(), pts);
}