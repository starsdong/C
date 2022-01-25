void weightedAverage(double y1, double y2, double e1, double e2)
{
  double w1 = 1/e1/e1;
  double w2 = 1/e2/e2;
  double y = (w1*y1+w2*y2)/(w1+w2);
  double e = 1/sqrt(w1+w2);
  cout << y << " +/- " << e << endl;
}
