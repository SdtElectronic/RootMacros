double seg(const std::vector<double>& val, const std::vector<double>& range, double deft_val = 0){
	double ret = deft_val;
	for(auto lim = range.cbegin(); lim != range.cend();)
		if((lim + 1) != range.cend() && x >= *lim && x < *(++lim))
			return val[lim - range.cbegin()];
}

double stepU(double x){
	return x < 0 ? 0 : 1;
}
