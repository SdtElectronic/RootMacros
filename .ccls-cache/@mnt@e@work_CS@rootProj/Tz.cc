class Tz :public TComplex{
	public:
		Tz(Double_t re, Double_t im=0, Bool_t polar=kFALSE):TComplex(re, im, polar), zpol(polar){}
		Tz(Tz& tzt):TComplex(tzt.Re(), tzt.Im(), tzt.Polar()){};
		Tz(Tz&& tzt):TComplex(tzt.Re(), tzt.Im(), tzt.Polar()){};
		virtual ~Tz(){}
		Tz operator ^ (double pow) const{
			TComplex tcoTem = TComplex::Power(*this, pow);
			return Tz(tcoTem.Re(), tcoTem.Im());
		}
		Tz operator ^ (int pow) const{
			TComplex tcoTem = TComplex::Power(*this, pow);
			return Tz(tcoTem.Re(), tcoTem.Im());
		}
		/*
		Tz operator / (int den) const{
			TComplex tcoTem = static_cast<TComplex>(*this) / static_cast<double>(den);
			return Tz(tcoTem.Re(), tcoTem.Im());
		}
		Tz operator + (int rha) const{
			TComplex tcoTem = static_cast<TComplex>(*this) + static_cast<double>(rha);
			return Tz(tcoTem.Re(), tcoTem.Im());
		}
		Tz operator - (int sub) const{
			TComplex tcoTem = static_cast<TComplex>(*this) - static_cast<double>(sub);
			return Tz(tcoTem.Re(), tcoTem.Im());
		}
		*/
		Tz operator ^= (double pow){
			TComplex tcoTem = TComplex::Power(*this, pow);
			(*this) = Tz(tcoTem.Re(), tcoTem.Im());
			return *this;
		}
		Tz operator ^= (int pow){
			TComplex tcoTem = TComplex::Power(*this, pow);
			(*this) = Tz(tcoTem.Re(), tcoTem.Im());
			return *this;
		}
		Tz operator /= (int den){
			TComplex tcoTem = static_cast<TComplex>(*this) / static_cast<double>(den);
			(*this) = Tz(tcoTem.Re(), tcoTem.Im());
			return *this;
		}
		Tz operator += (int rha){
			TComplex tcoTem = static_cast<TComplex>(*this) + static_cast<double>(rha);
			(*this) = Tz(tcoTem.Re(), tcoTem.Im());
			return *this;
		}
		Tz operator -= (int sub){
			TComplex tcoTem = static_cast<TComplex>(*this) - static_cast<double>(sub);
			(*this) = Tz(tcoTem.Re(), tcoTem.Im());
			return *this;
		}
		Tz& operator = (Tz& tzt){
			(*this)(tzt.Re(), tzt.Im());
			return *this;
		}
		Tz& operator = (Tz&& tzt){
			(*this)(tzt.Re(), tzt.Im());
			return *this;
		}
		Bool_t Polar(Bool_t pol){return zpol = pol;}
		Bool_t Polar(void){return zpol;}
	protected:
		Bool_t zpol;

};

string strRep(string str, const string& old_value, const string& new_value){     
    for(string::size_type pos(0); pos!=string::npos; pos+=new_value.length()){     
		if((pos=str.find(old_value,pos)) != string::npos) 
			str.replace(pos,old_value.length(),new_value);  
		else 
			break;
	}
    return str;     
}

auto plotZ(const char* expr, 
		     const char* name = "f1",
			 const char* dopt = "pol surf2",
		     double mx = 0.0f, double Mx = 1.0f, 
		     double my = -TMath::Pi(), double My = TMath::Pi()){
	stringstream sstem;
	auto tmpStr = strRep(strRep(string(expr), string("Z"), string("Tz(y, x, kTRUE)")), 
						 string(")("), string(")*("));
	sstem << "TComplex::Abs(" << strRep(tmpStr, string("j"), string("TComplex(0, 1)")) << ")";
	TF2 tftt(name, sstem.str().c_str(), my, My, mx, Mx);
	tftt.Draw(dopt);
	return tftt;
}
