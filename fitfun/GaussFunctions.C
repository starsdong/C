///////////////////////////////////////////////////////////////////////////////
// Gaussian function
// par[0] - area, par[1] - mean , par[2] - sigma
///////////////////////////////////////////////////////////////////////////////
Double_t Gauss(Double_t *x, Double_t *par)
{
  Double_t A = par[0]/TMath::Sqrt(2.0*TMath::Pi())/par[2]*TMath::Exp(-0.5*TMath::Power((x[0]-par[1])/par[2], 2.0));
  return A;
}

///////////////////////////////////////////////////////////////////////////////
// Gaussian + linear function
// par[0] - area, par[1] - mean , par[2] - sigma, par[3], par[4] - linear pars
///////////////////////////////////////////////////////////////////////////////
Double_t GaussLinear(Double_t *x, Double_t *par)
{
  Double_t A = par[0]/TMath::Sqrt(2.0*TMath::Pi())/par[2]*TMath::Exp(-0.5*TMath::Power((x[0]-par[1])/par[2], 2.0));
  Double_t B = par[3] + par[4] * x[0];
  return A + B;
}

///////////////////////////////////////////////////////////////////////////////
// Gaussian + quadratic function
// par[0] - area, par[1] - mean , par[2] - sigma, par[3], par[4], par[5] - quadratic pars
///////////////////////////////////////////////////////////////////////////////
Double_t GaussQuadratic(Double_t *x, Double_t *par)
{
  Double_t A = par[0]/TMath::Sqrt(2.0*TMath::Pi())/par[2]*TMath::Exp(-0.5*TMath::Power((x[0]-par[1])/par[2], 2.0));
  Double_t B = par[3] + par[4] * x[0] + par[5] * x[0] * x[0];
  return A + B;
}

///////////////////////////////////////////////////////////////////////////////
// Gaussian + exponetial function
// par[0] - area, par[1] - mean , par[2] - sigma, par[3], par[4] - exponential
///////////////////////////////////////////////////////////////////////////////
Double_t GaussExp(Double_t *x, Double_t *par)
{
  Double_t A = par[0]/TMath::Sqrt(2.0*TMath::Pi())/par[2]*TMath::Exp(-0.5*TMath::Power((x[0]-par[1])/par[2], 2.0));
  Double_t B = TMath::Exp(par[3] + par[4]*x[0]);
  return A + B;
}

///////////////////////////////////////////////////////////////////////////////
// Gaussian + Gaussian function
// par[0], par[3] - area, par[1], par[4] - mean , par[2], par[5] - sigma
///////////////////////////////////////////////////////////////////////////////
Double_t Gauss2(Double_t *x, Double_t *par)
{
  Double_t A = par[0]/TMath::Sqrt(2.0*TMath::Pi())/par[2]*TMath::Exp(-0.5*TMath::Power((x[0]-par[1])/par[2], 2.0));
  Double_t B = par[3]/TMath::Sqrt(2.0*TMath::Pi())/par[5]*TMath::Exp(-0.5*TMath::Power((x[0]-par[4])/par[5], 2.0));
  return A + B;
}

///////////////////////////////////////////////////////////////////////////////
// Gaussian + Gaussian + Gaussian function
// par[0], par[3], par[6] - area, par[1], par[4], par[7] - mean , par[2], par[5], par[8] - sigma
///////////////////////////////////////////////////////////////////////////////
Double_t Gauss3(Double_t *x, Double_t *par)
{
  Double_t A = par[0]/TMath::Sqrt(2.0*TMath::Pi())/par[2]*TMath::Exp(-0.5*TMath::Power((x[0]-par[1])/par[2], 2.0));
  Double_t B = par[3]/TMath::Sqrt(2.0*TMath::Pi())/par[5]*TMath::Exp(-0.5*TMath::Power((x[0]-par[4])/par[5], 2.0));
  Double_t C = par[6]/TMath::Sqrt(2.0*TMath::Pi())/par[8]*TMath::Exp(-0.5*TMath::Power((x[0]-par[7])/par[8], 2.0));
  return A + B + C;
}

///////////////////////////////////////////////////////////////////////////////
// Gaussian + Gaussian with the same mean function
// par[0], par[3] - area, par[1] - mean , par[2], par[4] - sigma
///////////////////////////////////////////////////////////////////////////////
Double_t DoubleGauss(Double_t *x, Double_t *par)
{
  Double_t A = par[0]/TMath::Sqrt(2.0*TMath::Pi())/par[2]*TMath::Exp(-0.5*TMath::Power((x[0]-par[1])/par[2], 2.0));
  Double_t B = par[3]/TMath::Sqrt(2.0*TMath::Pi())/par[4]*TMath::Exp(-0.5*TMath::Power((x[0]-par[1])/par[4], 2.0));
  return A + B;
}

///////////////////////////////////////////////////////////////////////////////
// Gaussian with two sigmas function
// par[0] - height!!!, par[1] - mean , par[2], par[3] - sigma
///////////////////////////////////////////////////////////////////////////////
Double_t AsymmetricGauss(Double_t *x, Double_t *par)
{
  Double_t A = par[0]*TMath::Exp(-0.5*TMath::Power((x[0]-par[1])/par[2], 2.0));
  Double_t B = par[0]*TMath::Exp(-0.5*TMath::Power((x[0]-par[1])/par[3], 2.0));
  if (x[0]<par[1]) return A;
  else return B;
}

///////////////////////////////////////////////////////////////////////////////
// 2D Gaussian
// par[0] - area, par[1],par[3] - means, par[2], par[4] - sigmas
///////////////////////////////////////////////////////////////////////////////
Double_t Gauss2D(Double_t *x, Double_t *par)
{
  Double_t A = par[0]/(2.0*TMath::Pi())/par[2]/par[4]*TMath::Exp(-0.5*TMath::Power((x[0]-par[1])/par[2], 2.0)-0.5*TMath::Power((x[1]-par[3])/par[4],2.0));
  return A;
}

///////////////////////////////////////////////////////////////////////////////
// 2D Gaussian with rotation
// par[0] - area, par[1],par[3] - means, par[2],par[4] - sigmas,  par[5] - phi-phase rotation
///////////////////////////////////////////////////////////////////////////////
Double_t Gauss2DRot(Double_t *x, Double_t *par)
{
  Double_t x_p[2];
  x_p[0] = TMath::Cos(par[5])*(x[0]-par[1]) + TMath::Sin(par[5])*(x[1]-par[3]);
  x_p[1] = -TMath::Sin(par[5])*(x[0]-par[1]) + TMath::Cos(par[5])*(x[1]-par[3]);
  Double_t A = par[0]/(2.0*TMath::Pi())/par[2]/par[4]*TMath::Exp(-0.5*TMath::Power(x_p[0]/par[2], 2.0)-0.5*TMath::Power(x_p[1]/par[4],2.0));
  return A;
}
///////////////////////////////////////////////////////////////////////////////
// student-t function
// par[0] - normalization, par[1] - mean, par[2] - sigma, par[3] - nu
// nu->inf, this is Gaussian
///////////////////////////////////////////////////////////////////////////////
Double_t StudentT(Double_t *x, Double_t *par)
{
  Double_t norm = par[0];
  Double_t mean = par[1];
  Double_t sigma = par[2];
  Double_t nu = par[3];

  Double_t st = norm * (TMath::Gamma((nu+1.0)/2.0)/(TMath::Gamma(nu/2.0)*TMath::Sqrt(TMath::Pi()*nu)*sigma)) * TMath::Power( (1.0+TMath::Power((x[0]-mean)/sigma,2.0)/nu), (-(nu+1.0)/2.0) );
  return st;
}
