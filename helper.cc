double seg(double x, const std::vector<double>& val, const std::vector<double>& range, double deft_val = 0){
	for(auto lim = range.begin(); lim != (range.cend() - 1); ++lim)
		if(x >= *lim && x < *(lim + 1))
			return val[lim - range.cbegin()];
	return deft_val;
}

double seg(double x, const std::initializer_list<double>& val, std::initializer_list<double>& range, double deft_val = 0){
	return seg(x, std::vector<double>(val), std::vector<double>(range), deft_val);
}

template<typename T>
double seg(double x, const std::vector<T>& func, const std::vector<double>& range, double deft_val = 0){
	for(auto lim = range.begin(); lim != (range.cend() - 1); ++lim)
		if(x >= *lim && x < *(lim + 1))
			return func[lim - range.cbegin()](x);
	return deft_val;
}

template<typename T, typename TT>
double seg(double x, const std::vector<T>& func, const std::vector<double>& range, TT deft_func){
	for(auto lim = range.begin(); lim != (range.cend() - 1); ++lim)
		if(x >= *lim && x < *(lim + 1))
			return func[lim - range.cbegin()](x);
	return deft_func(x);
}

template<typename T>
double seg(double x, const std::initializer_list<T>& func, const std::initializer_list<double>& range, double deft_val = 0){
	return seg(x, std::vector<T>(func), std::vector<double>(range), deft_val);
}

template<typename T, typename TT>
double seg(double x, const std::initializer_list<T>& func, const std::initializer_list<double>& range, TT deft_func){
	return seg(x, std::vector<T>(func), std::vector<double>(range), deft_func);
}

auto make_seg(const std::vector<double>& val, const std::vector<double>& range, double deft_val = 0){
	return std::bind((double(*)(double, const std::vector<double>&, const std::vector<double>&, double))seg, std::placeholders::_1, val, range, deft_val);
}

auto make_seg(const std::initializer_list<double>& val, std::initializer_list<double>& range, double deft_val = 0){
	return std::bind((double(*)(double, const std::initializer_list<double>&, std::initializer_list<double>&, double))&seg, std::placeholders::_1, val, range, deft_val);
}

template<typename T>
auto make_seg(const std::vector<T>& func, const std::vector<double>& range, double deft_val = 0){
	return std::bind((double(*)(double, const std::vector<T>&, const std::vector<double>&, double))seg, std::placeholders::_1, func, range, deft_val);
}

template<typename T>
auto make_seg(const std::initializer_list<T>& func, const std::initializer_list<double>& range, double deft_val = 0){
	return std::bind((double(*)(double, const std::vector<T>&, const std::vector<double>&, double))&seg, std::placeholders::_1, std::vector<T>(func), std::vector<double>(range), deft_val);
}

template<typename T, typename TT>
auto make_seg(const std::vector<T>& func, const std::vector<double>& range, TT deft_func){
	return std::bind((double(*)(double, const std::vector<T>&, const std::vector<double>&, TT))seg, std::placeholders::_1, func, range, deft_func);
}

template<typename T, typename TT>
auto make_seg(const std::initializer_list<T>& func, const std::initializer_list<double>& range, TT deft_func){
	return std::bind((double(*)(double, const std::vector<T>&, const std::vector<double>&, TT))seg, std::placeholders::_1, std::vector<T>(func), std::vector<double>(range), deft_func);
}

double stepU(double x){
	return x < 0 ? 0 : 1;
}
