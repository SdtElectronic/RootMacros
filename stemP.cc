auto stemP(const TF1& func, double ll, double ul, const char* opt = "aps"){
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
auto stemP(const TF1& func, const char* opt = "aps"){	
	return stemP(func, ceil(func.GetXmin()), floor(func.GetXmax()), opt);
}

auto stemP(const std::shared_ptr<TF1> objPtr, int npx = 0, const char* title = nullptr, const char* opt = "aps"){	
	objPtr->SetNpx(npx ? npx : objPtr->GetNpx());
	objPtr->SetTitle(title?title:objPtr->GetName());
	//new shared_ptr<TF1>(objPtr);
	return shared_ptr<TGraphAsymmErrors>(stemP(*objPtr, opt));
}