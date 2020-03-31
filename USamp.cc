template<typename T>
class USamp{	
	public:
	USamp(const T& samp, size_t pts, size_t ll, size_t ul): sample(samp), 
															points(pts), 
															lowerlim(ll), 
															uperlim(ul){	

	}

	auto operator [](size_t ind){
		return sample[lowerlim + ind - 1];
	}
	
	private:
	const T& sample;
	size_t points;
	size_t lowerlim;
	size_t uperlim;
};

template<>
auto USamp<TGraph>::operator [](size_t ind){
	return sample.GetPointY(lowerlim + ind - 1);
}

template<>
class USamp<TF1>{	
	public:
	USamp(const TF1& samp, size_t pts, double ll, double ul): sample(samp), 
															  points(pts), 
															  lowerlim(ll), 
															  uperlim(ul){	
		
	}
	USamp(const TF1& samp, size_t pts): USamp(samp, pts, samp.GetXmin(), samp.GetXmax()){	
		
	}
	auto operator [](size_t ind) const{
		double ix = lowerlim + (uperlim-lowerlim)/(points-1.)*ind;
		return limP(sample, ix);
	}
	
	private:
	const TF1& sample;
	size_t points;
	double lowerlim;
	double uperlim;
};
	/*

	USaIter begin(){

	}


	class USaIter{	
		public:
		USaIter(USamp samp, size_t ind = 0): sample(samp), index(ind){		
		
		}  

		operator +(size_t ad){		

		}
		operator +=(size_t ad){		

		}
		operator -(size_t ad){		

		}
		operator -=(size_t ad){		
			
		}
		private:
		USamp sample;
		size_t index;
	};
	
	*/
