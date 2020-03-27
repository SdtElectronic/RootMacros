# CERN Root Macros
Macros For Visualization and Discrete Data Analysis On [CERN Root](https://root.cern/)

## Demos

### util.h
---
Utilities for plotting ＆ helper functions, etc. Include to access all macros available in this project.

#### DrawP()
`shared_ptr<T>* DrawP(shared_ptr<T> objPtr, const char* opt = nullptr)`


### stemP.cc
---
Draw functions with stem plot style.

#### stemP()

`std::shared_ptr<TGraphAsymmErrors> stemP(const TF1& func, const char* opt = "aps", double ll = 0, double ul = 0)`

Parameters

* func Function plotted
* opt Draw options  ***For TGraph***
* lo Minimum value on X axis
* ul Maximum value on X axis
![Sa Function plotted by stemP](https://github.com/SdtElectronic/RootMacros/blob/master/ScrShot/sa.png "stemP Demo")

`DrawP(stemP(TF1("sa", "sin(x)/(x)", -12, 12)))`