///////////////////////////////////////////////////////////////////////////////
// Levy function
// par[0] - dN/dy, par[1] - T , par[2] - n, par[3] = m0
///////////////////////////////////////////////////////////////////////////////
// dN/pTdpT
Double_t Levy(Double_t *x, Double_t *par)
{
  double pT = x[0];
  double dNdy = par[0];
  double T = par[1];
  double n = par[2];
  double m0 = par[3];

  double A = TMath::Power(1+(TMath::Sqrt(pT*pT+m0*m0)-m0)/n/T,-n);
  return 0.5*TMath::Pi()*dNdy*(n-1)*(n-2)/n/T/(n*T+m0*(n-2))*A;
}

// dN/dpT
Double_t Levy_dNdpT(Double_t *x, Double_t *par)
{
  double pT = x[0];
  double dNdy = par[0];
  double T = par[1];
  double n = par[2];
  double m0 = par[3];

  double A = TMath::Power(1+(TMath::Sqrt(pT*pT+m0*m0)-m0)/n/T,-n);
  return 0.5*pT*TMath::Pi()*dNdy*(n-1)*(n-2)/n/T/(n*T+m0*(n-2))*A;
}
