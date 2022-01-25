#include "stdio.h"
#include "iomanip.h"

Double_t dNmTdmT(Double_t *x, Double_t *par)
{
  double mT = x[0];
  double T = par[0];
  return TMath::Exp(-mT/T);
}

Double_t dNdmT(Double_t *x, Double_t *par)
{
  double mT = x[0];
  return mT*dNmTdmT(x, par);
}

Double_t mTdNdmT(Double_t *x, Double_t *par)
{
  double mT = x[0];
  return mT*dNdmT(x, par);
}

void mtExpPositionTest(const double dmT = 0.2, const double T = 0.3)
{
  gROOT->Reset();

  cout << " Teff = " << T << endl;

  TF1 *fdNdmT = new TF1("fdNdmT", dNdmT, 0., 5., 1);
  fdNdmT->SetParameter(0, T);
  TF1 *fmTdNdmT = new TF1("fmTdNdmT", mTdNdmT, 0., 5., 1);
  fmTdNdmT->SetParameter(0, T);

  for(int i=0;i<(int)(5./dmT);i++) {
    double m1 = i*dmT;
    double m2 = (i+1)*dmT;
    double mTc = (m1+m2)/2.;
    double meanmT = fmTdNdmT->Integral(m1,m2)/fdNdmT->Integral(m1,m2);
    double mTlw = fdNdmT->GetX(fdNdmT->Integral(m1,m2)/dmT,m1,m2);
    cout << "m1=" << setw(6) << m1 << " m2=" << setw(6) << m2 << " mTc=" << setw(6) << mTc << " meanmT=" << setw(8) << meanmT << " mTlw=" << setw(8) << mTlw << endl;
  }

}
