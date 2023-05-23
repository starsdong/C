#include "TGraph.h"

void findChi2Min(const TGraph *chi2, const Int_t nsigma, double *chi2_min, double *x_min, double *x_el, double *x_eh)
{
  double d_chi2 = nsigma*nsigma;
  *chi2_min = 1.e+99;  
  Int_t N = chi2->GetN();
  for(int i=0;i<N-1;i++) {
    double x0 = chi2->GetX()[i];
    double x1 = chi2->GetX()[i+1];
    double dx = (x1-x0)/10.;
    for(int j=0;j<10;j++) {
      double x_j = x0 + dx*j;
      double y_j = chi2->Eval(x_j, 0, "S");  // TSpline  interpretation
      if(y_j<*chi2_min) {
	*chi2_min = y_j;
	*x_min = x_j;
      }
    }
  }

  const double chi2err = *chi2_min + d_chi2;
  double x_j_old = -999.;
  double y_j_old = 1.e+99;

  // search for the lower end
  bool found = false;
  for(int i=0;i<N-1;i++) {
    if(found) break;
    double x0 = chi2->GetX()[i];
    double x1 = chi2->GetX()[i+1];
    if(x1>*x_min) break;  // only need to search up to x_min
    double dx = (x1-x0)/10.;
    for(int j=0;j<10;j++) {
      if(found) break;
      double x_j = x0 + dx*j;
      double y_j = chi2->Eval(x_j, 0, "S");
      if(y_j>chi2err) {
	x_j_old = x_j;
	y_j_old = y_j;
      } else {
	if(y_j_old>chi2err) {  // found
	  *x_el = *x_min - x_j_old;
	  found = true;
	}
      }
    }
  }
  
  // search for the higher end
  x_j_old = 999.;
  y_j_old = 1.e+99;
  found = false;
  for(int i=0;i<N-1;i++) {
    if(found) break;
    double x0 = chi2->GetX()[i];
    double x1 = chi2->GetX()[i+1];
    if(x0<*x_min) continue;  // only need to search from x_min on
    double dx = (x1-x0)/10.;
    for(int j=0;j<10;j++) {
      if(found) break;
      double x_j = x0 + dx*j;
      double y_j = chi2->Eval(x_j, 0, "S");
      if(y_j<chi2err) {
	x_j_old = x_j;
	y_j_old = y_j;
      } else {
	if(y_j_old<chi2err) {  // found
	  *x_eh = x_j - *x_min;
	  found = true;
	}
      }
    }
  }

  return;
  
}
