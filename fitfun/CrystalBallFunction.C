///////////////////////////////////////////////////////////////////////////////
// Crystal-Ball function
// par[0] - N, par[1] - mean , par[2] - sigma, par[3] - n, par[4] - alpha
///////////////////////////////////////////////////////////////////////////////
Double_t CrystalBall(Double_t *x, Double_t *par)
{
  Double_t N = par[0];
  Double_t mu = par[1];
  Double_t s = par[2];
  Double_t n = par[3];
  Double_t alpha = par[4];

  Double_t A = TMath::Power(n/fabs(alpha), n) * TMath::Exp(-alpha*alpha/2.);
  Double_t B = n/fabs(alpha) - fabs(alpha);
  Double_t norm = (x[0]-mu)/s;

  if(norm > -alpha) {
    return N * TMath::Exp(-0.5*norm*norm);
  } else {
    return N * A * TMath::Power(B-norm, -n);
  }
}

///////////////////////////////////////////////////////////////////////////////
// Crystal-Ball function on both sides
// par[0] - N, par[1] - mean , par[2] - sigma, par[3] - n, par[4] - alpha
// par[5] - m, par[6] - beta
///////////////////////////////////////////////////////////////////////////////
Double_t CrystalBall2(Double_t *x, Double_t *par)
{
  Double_t N = par[0];
  Double_t mu = par[1];
  Double_t s = par[2];
  Double_t n = par[3];
  Double_t alpha = par[4];
  Double_t m = par[5];
  Double_t beta = par[6];

  Double_t A = TMath::Power(n/fabs(alpha), n) * TMath::Exp(-alpha*alpha/2.);
  Double_t B = n/fabs(alpha) - fabs(alpha);

  Double_t C = TMath::Power(m/fabs(beta), m) * TMath::Exp(-beta*beta/2.);
  Double_t D = m/fabs(beta) - fabs(beta);

  Double_t norm = (x[0]-mu)/s;

  if(norm < -alpha) {
    return N * A * TMath::Power(B-norm, -n);
  } else if(norm < beta) {
    return N * TMath::Exp(-0.5*norm*norm);
  } else {
    return N * C * TMath::Power(D+norm, -m);
  }
}

