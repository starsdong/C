Double_t Gamma(Double_t mass)
{
  const Double_t MassPi = 0.13957;
  const Double_t MassRho = 0.77549;
  const Double_t Gamma0 = 0.1491;
  if(mass>2.*MassPi) 
    return Gamma0*MassRho/mass*TMath::Power((mass*mass-4.*MassPi*MassPi)/(MassRho*MassRho-4.*MassPi*MassPi),1.5);
  else
    return 0;
}

Double_t GammaE(Double_t mass)
{
  const Double_t MassE = 0.000511;
  const Double_t MassRho = 0.77549;
  const Double_t Gamma0 = 0.1491;
  if(mass>2.*MassE) 
    return Gamma0*MassRho/mass*TMath::Power((mass*mass-4.*MassE*MassE)/(MassRho*MassRho-4.*MassE*MassE),0.5);
  else
    return 0;
}

Double_t GammaE2(Double_t mass) // from C.M. Ko
{
  const Double_t MassE = 0.000511;
  const Double_t MassRho = 0.77549;
  if(mass>2.*MassE) 
    return 8.8e-6*TMath::Power(MassRho,4.)/3./TMath::Power(mass,3.)*TMath::Power(1.-4.*MassE*MassE/mass/mass,0.5)*(1.+2.*MassE*MassE/mass/mass)*1.e3;
  else
    return 0;
}

Double_t d(Double_t mass)
{
  const Double_t MassPi = 0.13957;
  const Double_t MassRho = 0.77549;
  const Double_t Pi = 3.1415927;
  if(mass>2.*MassPi) {
    Double_t k = TMath::Sqrt(mass*mass/4.-MassPi*MassPi);
    return 3./Pi*MassPi*MassPi/k/k*TMath::Log((mass+2.*k)/2./MassPi)+mass/2/Pi/k-MassPi*MassPi*mass/Pi/k/k/k;
  } else {
    return 0.;
  }
}

Double_t R(Double_t mass)
{
  const Double_t alpha = 1./137.036;
  const Double_t MassPi = 0.13957;
  const Double_t MassRho = 0.77549;
  const Double_t Gamma0 = 0.1491;
  if(mass>2.*MassPi) 
    return alpha*alpha/36.*TMath::Power((mass*mass-4.*MassPi*MassPi)/mass/mass,1.5)*TMath::Power(mass/Gamma(mass)+d(mass),2.)*2.e4;
  else
    return 0.;
}

Double_t PS(Double_t mass, Double_t pT, Double_t T)
{
  return mass/TMath::Sqrt(mass*mass+pT*pT)*TMath::Exp(-TMath::Sqrt(mass*mass+pT*pT)/T);
}

Double_t massDist(Double_t *x, Double_t *par)
{
  const Double_t MassRho = 0.77549;
  const Double_t Gamma0 = 0.1491;
  double m = x[0];
  return m*MassRho*Gamma(m)/(TMath::Power((MassRho*MassRho-m*m),2.)+MassRho*MassRho*Gamma(m)*Gamma(m));
}

Double_t massDistF1(Double_t *x, Double_t *par)
{
  const Double_t MassRho = 0.77549;
  const Double_t Gamma0 = 0.1491;
  double pT = par[0];
  double T = par[1];
  double m = x[0];
  return m*MassRho*Gamma(m)/(TMath::Power((MassRho*MassRho-m*m),2.)+MassRho*MassRho*Gamma(m)*Gamma(m))*PS(m,pT,T)*1e2;
}

Double_t massDistF(Double_t *x, Double_t *par)
{
  const Double_t MassRho = 0.77549;
  const Double_t Gamma0 = 0.1491;
  const Double_t Gamma2 = 4.72e-5;
  double pT = par[0];
  double T = par[1];
  double m = x[0];
  return m*MassRho*GammaE(m)/(TMath::Power((MassRho*MassRho-m*m),2.)+MassRho*MassRho*(Gamma(m)+GammaE(m)*Gamma2)*(Gamma(m)+GammaE(m)*Gamma2))*PS(m,pT,T)*1e2;
}

Double_t massDistF2(Double_t *x, Double_t *par)
{
  const Double_t MassRho = 0.77549;
  const Double_t Gamma0 = 0.1491;
  const Double_t Gamma2 = 4.72e-5;
  double pT = par[0];
  double T = par[1];
  double m = x[0];
  return m*MassRho*GammaE2(m)/(TMath::Power((MassRho*MassRho-m*m),2.)+MassRho*MassRho*(Gamma(m)+GammaE2(m)*Gamma2)*(Gamma(m)+GammaE2(m)*Gamma2))*PS(m,pT,T)*1e2;
}

Double_t massDist0(Double_t *x, Double_t *par)
{
  const Double_t MassRho = 0.77549;
  const Double_t Gamma0 = 0.1491;
  double m = x[0];
  return m*MassRho*Gamma0/(TMath::Power((MassRho*MassRho-m*m),2.)+MassRho*MassRho*Gamma0*Gamma0);
}

Double_t massDistCeres(Double_t *x, Double_t *par)
{
  const Double_t MassPi = 0.13957;
  const Double_t MassRho = 0.77549;
  const Double_t Gamma0 = 0.1491;
  double m = x[0];
  double pT = par[0];
  double T = par[1];
  if(m>2.*MassPi)
    return TMath::Power(1-4.*MassPi*MassPi/m/m,1.5)/(TMath::Power(m*m-MassRho*MassRho,2.)+m*m*Gamma0*Gamma0)*PS(m,pT,T)*1e1;
  else
    return 0.;
}

Double_t massDistEE(Double_t *x, Double_t *par)
{
  return massDist(x,par)*R(x[0]);
}

Double_t massDistEEF(Double_t *x, Double_t *par)
{
  return massDistF1(x,par)*R(x[0]);
}

void massRhoPiPi()
{

  gROOT->Reset();

  const Double_t x1 = 0;
  const Double_t x2 = 1.5;

  TF1 *func0 = new TF1("func0",massDist0,x1,x2,0);
  //  func0->Draw();

//   TF1 *func = new TF1("func",massDist,x1,x2,0);
//   func->SetLineColor(2);
//   func->Draw("same");

//   TF1 *funcee = new TF1("funcee",massDistEE,x1,x2,0);
//   funcee->SetLineColor(4);
//   funcee->Draw("same");
  
  TF1 *funcF = new TF1("funcF",massDistF,x1,x2,2);
  funcF->SetParameters(0.5,0.16);
  //  funcF->SetLineStyle(2);
  funcF->SetLineColor(2);
  funcF->Draw();

  TF1 *funcF2 = new TF1("funcF2",massDistF2,x1,x2,2);
  funcF2->SetParameters(0.5,0.16);
  //  funcF2->SetLineStyle(2);
  funcF2->SetLineColor(1);
  funcF2->Draw("same");

  TF1 *funceeF = new TF1("funceeF",massDistEEF,x1,x2,2);
  funceeF->SetParameters(0.5,0.16);
  //  funceeF->SetLineStyle(2);
  funceeF->SetLineColor(4);
  funceeF->Draw("same");

  TF1 *funceeCeres = new TF1("funceeCeres",massDistCeres,x1,x2,2);
  funceeCeres->SetParameters(0.5,0.16);
  funceeCeres->SetLineColor(6);
  funceeCeres->Draw("same");
}
