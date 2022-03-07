#include <math.h>

/////////////////////////////////////////////////////////////////////////////
// power law function for dN/ptdpt
/////////////////////////////////////////////////////////////////////////////
Double_t powerlaw(Double_t *x, Double_t *par)
{
  double pT = x[0];
  double dNdy = par[0];
  double meanPt = par[1];
  double n = par[2];
  double p0 = meanPt * (n-3.)/2.;
  double A = dNdy*4.*(n-1)*(n-2)/(n-3)/(n-3)/meanPt/meanPt;
  return A*TMath::Power(1+pT/p0, -n);
}

/////////////////////////////////////////////////////////////////////////////
// power law function for dN/dpt
/////////////////////////////////////////////////////////////////////////////
Double_t powerlawdNdpt(Double_t *x, Double_t *par)
{
  double pT = x[0];
  double dNdy = par[0];
  double meanPt = par[1];
  double n = par[2];
  double p0 = meanPt * (n-3.)/2.;
  double A = dNdy*4.*(n-1)*(n-2)/(n-3)/(n-3)/meanPt/meanPt;
  return pT*A*TMath::Power(1+pT/p0, -n);
}

/////////////////////////////////////////////////////////////////////////////
// power law function for pt*dN/dpt
/////////////////////////////////////////////////////////////////////////////
Double_t powerlawptdNdpt(Double_t *x, Double_t *par)
{
  double pT = x[0];
  double dNdy = par[0];
  double meanPt = par[1];
  double n = par[2];
  double p0 = meanPt * (n-3.)/2.;
  double A = dNdy*4.*(n-1)*(n-2)/(n-3)/(n-3)/meanPt/meanPt;
  return pT*pT*A*TMath::Power(1+pT/p0, -n);
}
