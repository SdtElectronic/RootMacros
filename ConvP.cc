#pragma once

auto ConvP(const TF1& f1,const TF1& f2, unsigned int pts = 1e3, double ll = 0, double hl = 0, const char* title = nullptr){
	if(ll == hl){
		double rang = f1.GetXmax() - f1.GetXmin();
		ll = f2.GetXmin() - rang;
		hl = f2.GetXmax() + rang;
	}
	auto f_conv = make_unique<TF1Convolution>(const_cast<TF1*>(&f1), const_cast<TF1*>(&f2), ll, hl, pts);
	if(pts)
		f_conv->SetNofPointsFFT(pts);
	else
		f_conv->SetNumConv();
	auto fret =  make_shared<TF1>(title, *f_conv, ll, hl, f_conv->GetNpar());
	return fret;
}

template<typename T>
auto ConvP(const T& a1, const T& a2, size_t a1l, size_t a2l, size_t a1s, size_t a2s, const char* title = nullptr){
	const size_t len = a1l + a2l;
	const size_t ll = a1s + a2s;
	std::vector<double> convd(len);
	for(size_t ind2 = 0; ind2 != a2l; ++ind2)
		for(size_t ind1 = 0; ind1 != a2l; ++ind1)
			convd[ind2 + ind1] += a1[ind1] * a2[ind2];
	auto lmb = [=](const double *x, const double *p){return convd[ll + x[0]];};
	return make_shared<TF1>(title, lmb, ll, ll + len - 1, len);
}

template<typename T>
auto ConvP(const T& a1, const T& a2, size_t a1s = 0, size_t a2s = 0, const char* title = nullptr){
	return ConvP(a1, a2, a1.size(), a2.size(), a1s, a2s, title);
}

auto ConvP(const std::initializer_list<double>& a1, const std::initializer_list<double>& a2, size_t a1s = 0, size_t a2s = 0, const char* title = nullptr){
	return ConvP(std::vector<double>(a1), std::vector<double>(a2), a1.size(), a2.size(), a1s, a2s, title);
}