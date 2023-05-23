/* PDG method in dealing with asymmetric errors when calculating chi2
Ref:
https://pdg.lbl.gov/2019/reviews/rpp2019-rev-rpp-intro.pdf
page 14
*/
double reset_error(double aa,double eaa_lo,double eaa_hi,double inbb){

  if(inbb<aa-eaa_lo){ return eaa_lo;}
  else if(inbb>aa+eaa_hi){ return eaa_hi;}
  else{
    return ( (eaa_lo-eaa_hi)/(eaa_lo+eaa_hi)*aa + eaa_hi - (inbb-eaa_hi)*(eaa_lo-eaa_hi)/(eaa_lo+eaa_hi)  );
  }

}
