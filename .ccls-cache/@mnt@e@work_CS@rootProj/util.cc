double limP(const TF1& func, double ix){
	double iy = func.Eval(ix);
	while(isnan(iy) || isinf(iy)){
		ix += numeric_limits<double>().epsilon();
		iy = func.Eval(ix);	
	}
	return iy;
}
