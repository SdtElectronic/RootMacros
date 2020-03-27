auto stemP(const TF1& func, const char* opt = "aps", double lo = 0, double up = 0){
	if(lo == up){
		lo = ceil(func.GetXmin());
		up = floor(func.GetXmax());
	}
	size_t len =  static_cast<size_t>(++up - lo);
	double ax[len], ayh[len], ayl[len], ay[len], axz[len];
	for(double ix = lo; ix != up; ++ix){
		int ind = ix -lo;
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
	//ret->Draw(opt);
	return ret;
}
