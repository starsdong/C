#include "stdio.h"
#include "iomanip.h"

void eff_err_print(double m, double n, double& eff, double& err)
{
  if (m<0 || n<=0) return;
  if (m>n) return;

  *eff = m/n;
  *err = sqrt((m+1)/(n+2)*((m+2)/(n+3)-(m+1)/(n+2)));

  cout << " eff = " << *eff << " +/- " << *err << endl;
  return;
}
