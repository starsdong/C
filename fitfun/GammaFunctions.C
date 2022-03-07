#include <math.h>

/////////////////////////////////////////////////////////////////////////////
// return the value ln(Gamma(xx)) for xx>0
/////////////////////////////////////////////////////////////////////////////
Double_t GammaLn(Double_t xx)
{
  Double_t x,y,tmp,ser;
  static Double_t cof[6] = {76.1800917294746, -86.50532032941677,
			    24.01409824083091, -1.231739572450155,
			    0.120865097386617e-2, -0.5395239384953e-5};
  Int_t j;

  y=x=xx;
  tmp = x+5.5;
  tmp -= (x+0.5)*log(tmp);
  ser = 1.000000000190015;
  for (j=0;j<=5;j++) ser += cof[j]/++y;
  return -tmp+log(2.5066282746310005*ser/x);
}

/////////////////////////////////////////////////////////////////////////////
// return the value n!
/////////////////////////////////////////////////////////////////////////////
Double_t Factrl(Int_t n)
{
  static Int_t ntop = 4;
  static Float_t a[33] = {1.0, 1.0, 2.0, 6.0, 24.0};
  Int_t j;

  if (n<0) printf("Error! Negative factorial in routine Factrl()\n");
  if (n>32) return exp(GammaLn(n+1.0));
  while (ntop<n) {
    j = ntop++;
    a[ntop] = a[j]*ntop;
  }
  return a[n];
}

/////////////////////////////////////////////////////////////////////////////
// return the value ln(n!)
/////////////////////////////////////////////////////////////////////////////
Double_t FactLn(Int_t n)
{
  static Double_t a[101];

  if (n<0) printf("Error! Negative factorial in routine FactLn()\n");
  if (n<=1) return 0.0;
  if (n<=100) return a[n] ? a[n] : (a[n]=GammaLn(n+1.0));
  else return GammaLn(n+1.0);
}

/////////////////////////////////////////////////////////////////////////////
// return the binomial coefficienct (n,k) = n!/k!/(n-k)!
/////////////////////////////////////////////////////////////////////////////
Double_t Bico(Int_t n, Int_t k)
{
  return floor(0.5+exp(FactLn(n)-FactLn(k)-FactLn(n-k)));
}

/////////////////////////////////////////////////////////////////////////////
// return the value of Beta function B(z,w)=Gamma(z)*Gamma(w)/Gamma(z+w)
/////////////////////////////////////////////////////////////////////////////
Double_t Beta(Double_t z, Double_t w)
{
  return exp(Gammaln(z)+GammaLn(w)-GammaLn(z+w));
}

/////////////////////////////////////////////////////////////////////////////
// return the incomplete Gamma function P(a,x)
/////////////////////////////////////////////////////////////////////////////
Double_t GammaP(Double_t a, Double_t x)
{
  
}
