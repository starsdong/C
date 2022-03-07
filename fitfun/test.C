Double_t Gauss2DRot(Double_t *x, Double_t *par)
{
  Double_t x_p[2];
  x_p[0] = TMath::Cos(par[5])*x[0] + TMath::Sin(par[5])*x[1];
  x_p[1] = -TMath::Sin(par[5])*x[0] + TMath::Cos(par[5])*x[1];
  Double_t A = par[0]/(2.0*TMath::Pi())/par[2]/par[4]*TMath::Exp(-0.5*TMath::Power((x_p[0]-par[1])/par[2], 2.0)-0.5*TMath::Power((x_p[1]-par[3])/par[4],2.0));
  //  return Gauss2D(x_p, par);
  return A;
}

void test()
{
  TF2 *f2 = new TF2("f2",Gauss2DRot,-1,1,-1,1,6);
  f2->SetParameters(100,0,0.1,0,0.3,1.57);
  f2->Draw("lego");

}
