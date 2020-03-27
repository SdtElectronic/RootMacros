auto stemP(const TF1& func, const char* opt = "aps", double ll = 0, double ul = 0){
	if(ll == ul){
		ll = ceil(func.GetXmin());
		ul = floor(func.GetXmax());
	}
	size_t len =  static_cast<size_t>(++ul - ll);
	double ax[len], ayh[len], ayl[len], ay[len], axz[len];
	for(double ix = ll; ix != ul; ++ix){
		int ind = ix -ll;
		axz[ind] = 0;
		ax[ind] = ix;
		double iy = limP(func, ix);
		ix = ax[ind];
		if(iy < 0){
			ayh[ind] = -iy;
			ayl[ind] = 0;
		}else{
			ayh[ind] = 0;
			ayl[ind] = iy;
		}
		ay[ind] = iy;
	}
	auto ret = shared_ptr<TGraphAsymmErrors>(new TGraphAsymmErrors(len, ax, ay, axz, axz, ayl, ayh));
	ret->SetLineColor(4);
	ret->SetMarkerColor(4);
	ret->SetTitle(func.GetName());
	ret->SetMarkerStyle(4);
	return ret;
}
