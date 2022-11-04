double rapidity(double e_com, int ion = 1)
{
  const double mu = 0.9315; // atomic mass
  const double mp = 0.93827;

  double e = e_com/2.0;
  double pz = 0;
  if(ion) {
    pz = sqrt(e*e - mu*mu);
  } else{
    pz = sqrt(e*e - mp*mp);
  }

  return 0.5*log((e+pz)/(e-pz));
}
