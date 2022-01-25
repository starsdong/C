void eff_err(double m, double n, double* eff, double* err)
{
  *eff = 0;
  *err = 0;

  if (m<0 || n<=0) return;
  if (m>n) return;

  *eff = m/n;
  *err = sqrt((m+1)/(n+2)*((m+2)/(n+3)-(m+1)/(n+2)));

  return;
}
