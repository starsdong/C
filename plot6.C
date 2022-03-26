#include "style.C+"
#include "draw.C+"

void plot(TH1* d0, double x1=0., double x2=1., double y1=0., double y2=10., const char* xtitle="p_{T} (GeV/c)", const char* ytitle="(d^{2}N)/(2#pip_{T}dp_{T}dy) (GeV/c)^{-2}", const char* output="test", const int logy=0, TF1* fitfun = 0, double xfit1=0., double xfit2=1., double *par = 0)
{
  
   TCanvas *c1 = new TCanvas("c1", "c1",0,0,800,600);
   if(logy) c1->SetLogy();
   int i1 = d0->GetXaxis()->FindBin(x1+0.000001);
   int i2 = d0->GetXaxis()->FindBin(x2-0.000001);

   if(y2<=y1) {
     y2 = d0->GetMaximum()/0.8;
     if(logy) y2 = d0->GetMaximum()/0.2;
   }

   d0->GetXaxis()->SetRange(i1, i2);
   d0->SetMinimum(y1);
   d0->SetMaximum(y2);
   d0->GetXaxis()->SetTitle(xtitle);
   d0->GetYaxis()->SetTitle(ytitle);
   d0->Sumw2();
   d0->Draw();

   if(fitfun) {
     fitfun->SetParameters(par);
     fitfun->SetRange(xfit1,xfit2);
     fitfun->SetLineWidth(2);
     fitfun->SetLineColor(2);
     d0->Fit(fitfun,"R");
   }

   drawHistBox(x1,x2,y1,y2);

   c1->Update();
   char outputfile[100];
   sprintf(outputfile,"fig/%s.png",output);
   c1->SaveAs(outputfile);
   sprintf(outputfile,"fig/%s.pdf",output);
   c1->SaveAs(outputfile);

}

/*
void plot(const TGraphErrors* gr, double x1=0., double x2=1., double y1=0., double y2=10., const char* xtitle="p_{T} (GeV/c)", const char* ytitle="(d^{2}N)/(2#pip_{T}dp_{T}dy) (GeV/c)^{-2}", const char* output="test", const int logy=0, const TF1* fitfun = 0, const double xfit1=0., const double xfit2=1., const double *par = 0)
{

  gROOT->Reset();

   TCanvas *c1 = new TCanvas("c1", "c1",0,0,800,600);
   gStyle->SetOptFit(0);
   gStyle->SetOptStat(0);
   gStyle->SetEndErrorSize(0.01);
   if(logy) c1->SetLogy();
   c1->SetFillColor(10);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameFillColor(0);
   c1->SetFrameBorderMode(0);

   c1->SetGridx();
   c1->SetGridy();

   c1->SetLeftMargin(0.13);
   c1->SetBottomMargin(0.13);
   c1->SetTopMargin(0.02);
   c1->SetRightMargin(0.06);

   if(y2<=y1) {
     y2 = d0->GetMaximum()/0.8;
     if(logy) y2 = d0->GetMaximum()/0.2;
   }

   TH1D *d0 = new TH1D("d0","",1,x1,x2);
   d0->SetMinimum(y1);
   d0->SetMaximum(y2);
   d0->GetXaxis()->SetNdivisions(208);
   d0->GetXaxis()->SetTitle(xtitle);
   d0->GetXaxis()->SetTitleOffset(0.9);
   d0->GetXaxis()->SetTitleSize(0.06);
   d0->GetXaxis()->SetLabelOffset(0.01);
   d0->GetXaxis()->SetLabelSize(0.045);
   d0->GetXaxis()->SetLabelFont(42);
   d0->GetXaxis()->SetTitleFont(42);
   d0->GetYaxis()->SetNdivisions(210);
   d0->GetYaxis()->SetTitle(ytitle);
   d0->GetYaxis()->SetTitleOffset(1.0);
   d0->GetYaxis()->SetTitleSize(0.06);
   d0->GetYaxis()->SetLabelOffset(0.005);
   d0->GetYaxis()->SetLabelSize(0.045);
   d0->GetYaxis()->SetLabelFont(42);
   d0->GetYaxis()->SetTitleFont(42);
   d0->SetLineWidth(2);
   d0->Draw();

   TLine *l1 = new TLine(x1,y1,x2,y1);
   l1->SetLineWidth(3);
   l1->Draw("same");
   TLine *l2 = new TLine(x1,y2,x2,y2);
   l2->SetLineWidth(3);
   l2->Draw("same");
   TLine *l3 = new TLine(x1,y1,x1,y2);
   l3->SetLineWidth(3);
   l3->Draw("same");
   TLine *l4 = new TLine(x2,y1,x2,y2);
   l4->SetLineWidth(3);
   l4->Draw("same");

   // gr->SetMarkerSize(1.8);
   // gr->SetMarkerStyle(20);
   gr->SetLineWidth(2);
   gr->Draw("p");
//    TLegend *leg = new TLegend(0.50, 0.66, 0.96, 0.94);
//    leg->SetFillColor(10);
//    leg->SetFillStyle(10);
//    leg->SetLineStyle(4000);
//    leg->SetLineColor(10);
//    leg->SetLineWidth(0.);
//    leg->SetTextFont(42);
//    leg->SetTextSize(0.045);
//    leg->Draw();

   if(fitfun) {
     fitfun->SetParameters(par);
     fitfun->SetLineWidth(2);
     fitfun->SetLineColor(2);
     gr->Fit(fitfun,"R");

     fitfun->GetParameters(par);
   }

   c1->Update();
   char outputfile[100];
   sprintf(outputfile,"fig/%s.png",output);
   c1->SaveAs(outputfile);
   sprintf(outputfile,"fig/%s.pdf",output);
   c1->SaveAs(outputfile);

}

void plot(const TGraph* gr, double x1=0., double x2=1., double y1=0., double y2=10., const char* xtitle="p_{T} (GeV/c)", const char* ytitle="(d^{2}N)/(2#pip_{T}dp_{T}dy) (GeV/c)^{-2}", const char* output="test", const int logy=0)
{

  gROOT->Reset();

   TCanvas *c1 = new TCanvas("c1", "c1",0,0,800,600);
   gStyle->SetOptFit(0);
   gStyle->SetOptStat(0);
   gStyle->SetEndErrorSize(0.01);
   if(logy) c1->SetLogy();
   c1->SetFillColor(10);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameFillColor(0);
   c1->SetFrameBorderMode(0);

   c1->SetGridx();
   c1->SetGridy();

   c1->SetLeftMargin(0.13);
   c1->SetBottomMargin(0.13);
   c1->SetTopMargin(0.02);
   c1->SetRightMargin(0.06);

   if(y2<=y1) {
     y2 = d0->GetMaximum()/0.8;
     if(logy) y2 = d0->GetMaximum()/0.2;
   }

   TH1D *d0 = new TH1D("d0","",1,x1,x2);
   d0->SetMinimum(y1);
   d0->SetMaximum(y2);
   d0->GetXaxis()->SetNdivisions(208);
   d0->GetXaxis()->SetTitle(xtitle);
   d0->GetXaxis()->SetTitleOffset(0.9);
   d0->GetXaxis()->SetTitleSize(0.06);
   d0->GetXaxis()->SetLabelOffset(0.01);
   d0->GetXaxis()->SetLabelSize(0.045);
   d0->GetXaxis()->SetLabelFont(42);
   d0->GetXaxis()->SetTitleFont(42);
   d0->GetYaxis()->SetNdivisions(210);
   d0->GetYaxis()->SetTitle(ytitle);
   d0->GetYaxis()->SetTitleOffset(1.0);
   d0->GetYaxis()->SetTitleSize(0.06);
   d0->GetYaxis()->SetLabelOffset(0.005);
   d0->GetYaxis()->SetLabelSize(0.045);
   d0->GetYaxis()->SetLabelFont(42);
   d0->GetYaxis()->SetTitleFont(42);
   d0->SetLineWidth(2);
   d0->Draw();

   TLine *l1 = new TLine(x1,y1,x2,y1);
   l1->SetLineWidth(3);
   l1->Draw("same");
   TLine *l2 = new TLine(x1,y2,x2,y2);
   l2->SetLineWidth(3);
   l2->Draw("same");
   TLine *l3 = new TLine(x1,y1,x1,y2);
   l3->SetLineWidth(3);
   l3->Draw("same");
   TLine *l4 = new TLine(x2,y1,x2,y2);
   l4->SetLineWidth(3);
   l4->Draw("same");

   // gr->SetMarkerSize(1.8);
   // gr->SetMarkerStyle(20);
   gr->SetLineWidth(2);
   gr->Draw("c");
//    TLegend *leg = new TLegend(0.50, 0.66, 0.96, 0.94);
//    leg->SetFillColor(10);
//    leg->SetFillStyle(10);
//    leg->SetLineStyle(4000);
//    leg->SetLineColor(10);
//    leg->SetLineWidth(0.);
//    leg->SetTextFont(42);
//    leg->SetTextSize(0.045);
//    leg->Draw();

   c1->Update();
   char outputfile[100];
   sprintf(outputfile,"fig/%s.png",output);
   c1->SaveAs(outputfile);
   sprintf(outputfile,"fig/%s.pdf",output);
   c1->SaveAs(outputfile);

}


void plot(const TGraph* gr1, const TGraph* gr2, double x1=0., double x2=1., double y1=0., double y2=10., const char* xtitle="p_{T} (GeV/c)", const char* ytitle="(d^{2}N)/(2#pip_{T}dp_{T}dy) (GeV/c)^{-2}", const char* output="test", const int logy=0, const int icolor=1)
{

  gROOT->Reset();

   TCanvas *c1 = new TCanvas("c1", "c1",0,0,800,600);
   gStyle->SetOptFit(0);
   gStyle->SetOptStat(0);
   gStyle->SetEndErrorSize(0.01);
   if(logy) c1->SetLogy();
   c1->SetFillColor(10);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameFillColor(0);
   c1->SetFrameBorderMode(0);

   c1->SetGridx();
   c1->SetGridy();

   c1->SetLeftMargin(0.13);
   c1->SetBottomMargin(0.15);
   c1->SetTopMargin(0.02);
   c1->SetRightMargin(0.06);

   if(y2<=y1) {
     y2 = d0->GetMaximum()/0.8;
     if(logy) y2 = d0->GetMaximum()/0.2;
   }

   TH1D *d0 = new TH1D("d0","",1,x1,x2);
   d0->SetMinimum(y1);
   d0->SetMaximum(y2);
   d0->GetXaxis()->SetNdivisions(208);
   d0->GetXaxis()->SetTitle(xtitle);
   d0->GetXaxis()->SetTitleOffset(1.0);
   d0->GetXaxis()->SetTitleSize(0.06);
   d0->GetXaxis()->SetLabelOffset(0.01);
   d0->GetXaxis()->SetLabelSize(0.045);
   d0->GetXaxis()->SetLabelFont(42);
   d0->GetXaxis()->SetTitleFont(42);
   d0->GetYaxis()->SetNdivisions(205);
   d0->GetYaxis()->SetTitle(ytitle);
   d0->GetYaxis()->SetTitleOffset(1.0);
   d0->GetYaxis()->SetTitleSize(0.06);
   d0->GetYaxis()->SetLabelOffset(0.005);
   d0->GetYaxis()->SetLabelSize(0.045);
   d0->GetYaxis()->SetLabelFont(42);
   d0->GetYaxis()->SetTitleFont(42);
   d0->SetLineWidth(2);
   d0->Draw();

   TLine *l1 = new TLine(x1,y1,x2,y1);
   l1->SetLineWidth(3);
   l1->Draw("same");
   TLine *l2 = new TLine(x1,y2,x2,y2);
   l2->SetLineWidth(3);
   l2->Draw("same");
   TLine *l3 = new TLine(x1,y1,x1,y2);
   l3->SetLineWidth(3);
   l3->Draw("same");
   TLine *l4 = new TLine(x2,y1,x2,y2);
   l4->SetLineWidth(3);
   l4->Draw("same");

   TLine *l0 = new TLine(x1,1,x2,1);
   l0->SetLineWidth(2);
   l0->SetLineStyle(4);
   l0->Draw("same");
   
   gr1->SetLineStyle(1);
   gr1->SetLineWidth(2);
   gr1->SetLineColor(icolor);
   gr1->Draw("c");

   gr2->SetLineStyle(2);
   gr2->SetLineWidth(2);
   gr2->SetLineColor(icolor);
   gr2->Draw("c");
   
   //    TLegend *leg = new TLegend(0.50, 0.66, 0.96, 0.94);
//    leg->SetFillColor(10);
//    leg->SetFillStyle(10);
//    leg->SetLineStyle(4000);
//    leg->SetLineColor(10);
//    leg->SetLineWidth(0.);
//    leg->SetTextFont(42);
//    leg->SetTextSize(0.045);
//    leg->Draw();


   c1->Update();
   char outputfile[100];
   sprintf(outputfile,"fig/%s.png",output);
   c1->SaveAs(outputfile);
   sprintf(outputfile,"fig/%s.pdf",output);
   c1->SaveAs(outputfile);

}

void plot(const TH1* d0, double x1=0., double x2=1., double y1=0., double y2=10., const char* xtitle="p_{T} (GeV/c)", const char* ytitle="(d^{2}N)/(2#pip_{T}dp_{T}dy) (GeV/c)^{-2}", const char* output="test", const int logy=0, const TF1* fitfun = 0)
{

  gROOT->Reset();

   TCanvas *c1 = new TCanvas("c1", "c1",0,0,800,600);
   gStyle->SetOptFit(0);
   gStyle->SetOptStat(0);
   gStyle->SetEndErrorSize(0.01);
   if(logy) c1->SetLogy();
   c1->SetFillColor(10);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameFillColor(0);
   c1->SetFrameBorderMode(0);

   c1->SetGridx();
   c1->SetGridy();

   c1->SetLeftMargin(0.13);
   c1->SetBottomMargin(0.15);
   c1->SetTopMargin(0.02);
   c1->SetRightMargin(0.06);

   int i1 = d0->GetXaxis()->FindBin(x1+0.00001);
   int i2 = d0->GetXaxis()->FindBin(x2-0.00001);

   if(y2<=y1) {
     y2 = d0->GetMaximum()/0.8;
     if(logy) y2 = d0->GetMaximum()/0.2;
   }

   d0->GetXaxis()->SetRange(i1, i2);
   d0->SetMinimum(y1);
   d0->SetMaximum(y2);
   d0->GetXaxis()->SetNdivisions(208);
   d0->GetXaxis()->SetTitle(xtitle);
   d0->GetXaxis()->SetTitleOffset(1.0);
   d0->GetXaxis()->SetTitleSize(0.06);
   d0->GetXaxis()->SetLabelOffset(0.01);
   d0->GetXaxis()->SetLabelSize(0.045);
   d0->GetXaxis()->SetLabelFont(42);
   d0->GetXaxis()->SetTitleFont(42);
   d0->GetYaxis()->SetNdivisions(205);
   d0->GetYaxis()->SetTitle(ytitle);
   d0->GetYaxis()->SetTitleOffset(1.0);
   d0->GetYaxis()->SetTitleSize(0.06);
   d0->GetYaxis()->SetLabelOffset(0.005);
   d0->GetYaxis()->SetLabelSize(0.045);
   d0->GetYaxis()->SetLabelFont(42);
   d0->GetYaxis()->SetTitleFont(42);
   d0->SetLineWidth(2);
   d0->SetLineColor(1);
   if(fitfun) d0->Draw("e");
   else d0->Draw();

//    TLegend *leg = new TLegend(0.50, 0.66, 0.96, 0.94);
//    leg->SetFillColor(10);
//    leg->SetFillStyle(10);
//    leg->SetLineStyle(4000);
//    leg->SetLineColor(10);
//    leg->SetLineWidth(0.);
//    leg->SetTextFont(42);
//    leg->SetTextSize(0.045);
//    leg->Draw();

   if(fitfun) {
     fitfun->SetLineWidth(2);
     fitfun->SetLineColor(2);
     d0->Fit(fitfun,"R");

   }


   TLine *l1 = new TLine(x1,y1,x2,y1);
   l1->SetLineWidth(3);
   l1->Draw("same");
   TLine *l2 = new TLine(x1,y2,x2,y2);
   l2->SetLineWidth(3);
   l2->Draw("same");
   TLine *l3 = new TLine(x1,y1,x1,y2);
   l3->SetLineWidth(3);
   l3->Draw("same");
   TLine *l4 = new TLine(x2,y1,x2,y2);
   l4->SetLineWidth(3);
   l4->Draw("same");

   c1->Update();
   char outputfile[100];
   sprintf(outputfile,"fig/%s.png",output);
   c1->SaveAs(outputfile);
   sprintf(outputfile,"fig/%s.pdf",output);
   c1->SaveAs(outputfile);

}

void plot(const TGraphErrors* gr, double x1=0., double x2=1., double y1=0., double y2=10., const char* xtitle="p_{T} (GeV/c)", const char* ytitle="(d^{2}N)/(2#pip_{T}dp_{T}dy) (GeV/c)^{-2}", const char* output="test", const int logy=0, const TF1* func = 0)
{

  gROOT->Reset();

   TCanvas *c1 = new TCanvas("c1", "c1",0,0,800,600);
   gStyle->SetOptFit(0);
   gStyle->SetOptStat(0);
   gStyle->SetEndErrorSize(0.01);
   if(logy) c1->SetLogy();
   c1->SetFillColor(10);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameFillColor(0);
   c1->SetFrameBorderMode(0);

   c1->SetGridx();
   c1->SetGridy();

   c1->SetLeftMargin(0.13);
   c1->SetBottomMargin(0.13);
   c1->SetTopMargin(0.02);
   c1->SetRightMargin(0.06);

   if(y2<=y1) {
     y2 = d0->GetMaximum()/0.8;
     if(logy) y2 = d0->GetMaximum()/0.2;
   }

   TH1D *d0 = new TH1D("d0","",1,x1,x2);
   d0->SetMinimum(y1);
   d0->SetMaximum(y2);
   d0->GetXaxis()->SetNdivisions(208);
   d0->GetXaxis()->SetTitle(xtitle);
   d0->GetXaxis()->SetTitleOffset(0.9);
   d0->GetXaxis()->SetTitleSize(0.06);
   d0->GetXaxis()->SetLabelOffset(0.01);
   d0->GetXaxis()->SetLabelSize(0.045);
   d0->GetXaxis()->SetLabelFont(42);
   d0->GetXaxis()->SetTitleFont(42);
   d0->GetYaxis()->SetNdivisions(205);
   d0->GetYaxis()->SetTitle(ytitle);
   d0->GetYaxis()->SetTitleOffset(1.0);
   d0->GetYaxis()->SetTitleSize(0.06);
   d0->GetYaxis()->SetLabelOffset(0.005);
   d0->GetYaxis()->SetLabelSize(0.045);
   d0->GetYaxis()->SetLabelFont(42);
   d0->GetYaxis()->SetTitleFont(42);
   d0->SetLineWidth(2);
   d0->Draw();

   TLine *l1 = new TLine(x1,y1,x2,y1);
   l1->SetLineWidth(3);
   l1->Draw("same");
   TLine *l2 = new TLine(x1,y2,x2,y2);
   l2->SetLineWidth(3);
   l2->Draw("same");
   TLine *l3 = new TLine(x1,y1,x1,y2);
   l3->SetLineWidth(3);
   l3->Draw("same");
   TLine *l4 = new TLine(x2,y1,x2,y2);
   l4->SetLineWidth(3);
   l4->Draw("same");

   gr->SetMarkerSize(1.8);
   gr->SetMarkerStyle(20);
   gr->SetLineWidth(2);
   gr->Draw("p");
//    TLegend *leg = new TLegend(0.50, 0.66, 0.96, 0.94);
//    leg->SetFillColor(10);
//    leg->SetFillStyle(10);
//    leg->SetLineStyle(4000);
//    leg->SetLineColor(10);
//    leg->SetLineWidth(0.);
//    leg->SetTextFont(42);
//    leg->SetTextSize(0.045);
//    leg->Draw();

   if(func) {
     func->SetLineWidth(2);
     func->SetLineColor(2);
     gr->Fit(func,"R");
   }

   c1->Update();
   char outputfile[100];
   sprintf(outputfile,"fig/%s.png",output);
   c1->SaveAs(outputfile);
   sprintf(outputfile,"fig/%s.pdf",output);
   c1->SaveAs(outputfile);

}

void plot(const TH1* d0, const TH1* d1, double x1=0., double x2=1., double y1=0., double y2=10., const char* xtitle="p_{T} (GeV/c)", const char* ytitle="(d^{2}N)/(2#pip_{T}dp_{T}dy) (GeV/c)^{-2}", const char* leg0="a", const char* leg1="b",const char* output="test", const int logy=0)
{

  gROOT->Reset();
 
  TCanvas *c1 = new TCanvas("c1","c1",0,0,800,600);

   gStyle->SetOptFit(0);
   gStyle->SetOptStat(0);
   gStyle->SetEndErrorSize(0.01);
   if(logy) c1->SetLogy();
   c1->SetFillColor(10);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameFillColor(0);
   c1->SetFrameBorderMode(0);

   c1->SetGridx();
   c1->SetGridy();

   c1->SetLeftMargin(0.13);
   c1->SetBottomMargin(0.13);
   c1->SetTopMargin(0.02);
   c1->SetRightMargin(0.06);

   int i1 = d0->GetXaxis()->FindBin(x1+0.000001);
   int i2 = d0->GetXaxis()->FindBin(x2-0.000001);

   if(y2<=y1) {
     y2 = d0->GetMaximum()/0.8;
     if(logy) {
       y2 = d0->GetMaximum()/0.2;
     }
   }
   // cout << i1 << " " << i2 << " " << x1 << " " << x2 << " " << y1 << " " << y2 << endl;
   
   d0->GetXaxis()->SetRange(i1, i2);
   d0->SetMinimum(y1);
   d0->SetMaximum(y2);
   d0->GetXaxis()->SetNdivisions(208);
   d0->GetXaxis()->SetTitle(xtitle);
   d0->GetXaxis()->SetTitleOffset(0.9);
   d0->GetXaxis()->SetTitleSize(0.06);
   d0->GetXaxis()->SetLabelOffset(0.01);
   d0->GetXaxis()->SetLabelSize(0.045);
   d0->GetXaxis()->SetLabelFont(42);
   d0->GetXaxis()->SetTitleFont(42);
   d0->GetYaxis()->SetNdivisions(205);
   d0->GetYaxis()->SetTitle(ytitle);
   d0->GetYaxis()->SetTitleOffset(1.0);
   d0->GetYaxis()->SetTitleSize(0.06);
   d0->GetYaxis()->SetLabelOffset(0.005);
   d0->GetYaxis()->SetLabelSize(0.045);
   d0->GetYaxis()->SetLabelFont(42);
   d0->GetYaxis()->SetTitleFont(42);
   d0->SetLineWidth(2);
   d0->Draw();

   d1->SetLineWidth(2);
   d1->SetLineColor(2);
   d1->SetLineStyle(2);
   d1->Draw("same");

   TLine *l1 = new TLine(x1,y1,x2,y1);
   l1->SetLineWidth(3);
   l1->Draw("same");
   TLine *l2 = new TLine(x1,y2,x2,y2);
   l2->SetLineWidth(3);
   l2->Draw("same");
   TLine *l3 = new TLine(x1,y1,x1,y2);
   l3->SetLineWidth(3);
   l3->Draw("same");
   TLine *l4 = new TLine(x2,y1,x2,y2);
   l4->SetLineWidth(3);
   l4->Draw("same");

   TLegend *leg = new TLegend(0.74, 0.76, 0.92, 0.94);
   leg->SetFillColor(10);
   leg->SetFillStyle(10);
   leg->SetLineStyle(4000);
   leg->SetLineColor(10);
   leg->SetLineWidth(0.);
   leg->SetTextFont(42);
   leg->SetTextSize(0.045);
   leg->AddEntry(d1,leg1,"l");
   leg->AddEntry(d0,leg0,"l");
   leg->Draw();

   c1->Update();
   char outputfile[100];
   sprintf(outputfile,"fig/%s.png",output);
   c1->SaveAs(outputfile);
   sprintf(outputfile,"fig/%s.pdf",output);
   c1->SaveAs(outputfile);

}

void plot(const TH1* d0, const TH1* d1, const TH1* d2, double x1=0., double x2=1., double y1=0., double y2=10., const char* xtitle="p_{T} (GeV/c)", const char* ytitle="(d^{2}N)/(2#pip_{T}dp_{T}dy) (GeV/c)^{-2}", const char* leg0="a", const char* leg1="b", const char* leg2="c", const char* output="test", const int logy=0)
{

  gROOT->Reset();

   TCanvas *c1 = new TCanvas("c1", "c1",0,0,800,600);
   gStyle->SetOptFit(0);
   gStyle->SetOptStat(0);
   gStyle->SetEndErrorSize(0.01);
   if(logy) c1->SetLogy();
   c1->SetFillColor(10);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameFillColor(0);
   c1->SetFrameBorderMode(0);

   c1->SetGridx();
   c1->SetGridy();

   c1->SetLeftMargin(0.13);
   c1->SetBottomMargin(0.13);
   c1->SetTopMargin(0.02);
   c1->SetRightMargin(0.06);

   int i1 = d0->GetXaxis()->FindBin(x1+0.000001);
   int i2 = d0->GetXaxis()->FindBin(x2-0.000001);

   if(y2<=y1) {
     y2 = d0->GetMaximum()/0.8;
     if(logy) {
       y2 = d0->GetMaximum()/0.2;
     }
   }

   d0->GetXaxis()->SetRange(i1, i2);
   d0->SetMinimum(y1);
   d0->SetMaximum(y2);
   d0->GetXaxis()->SetNdivisions(208);
   d0->GetXaxis()->SetTitle(xtitle);
   d0->GetXaxis()->SetTitleOffset(0.9);
   d0->GetXaxis()->SetTitleSize(0.06);
   d0->GetXaxis()->SetLabelOffset(0.01);
   d0->GetXaxis()->SetLabelSize(0.045);
   d0->GetXaxis()->SetLabelFont(42);
   d0->GetXaxis()->SetTitleFont(42);
   d0->GetYaxis()->SetNdivisions(205);
   d0->GetYaxis()->SetTitle(ytitle);
   d0->GetYaxis()->SetTitleOffset(1.0);
   d0->GetYaxis()->SetTitleSize(0.06);
   d0->GetYaxis()->SetLabelOffset(0.005);
   d0->GetYaxis()->SetLabelSize(0.045);
   d0->GetYaxis()->SetLabelFont(42);
   d0->GetYaxis()->SetTitleFont(42);
   d0->SetLineWidth(2);
   d0->Draw();

   d1->SetLineWidth(2);
   d1->SetLineColor(2);
   d1->SetLineStyle(1);
   d1->Draw("same");

   d2->SetLineWidth(2);
   d2->SetLineColor(4);
   d2->SetLineStyle(1);
   d2->Draw("same");

   TLine *l1 = new TLine(x1,y1,x2,y1);
   l1->SetLineWidth(3);
   l1->Draw("same");
   TLine *l2 = new TLine(x1,y2,x2,y2);
   l2->SetLineWidth(3);
   l2->Draw("same");
   TLine *l3 = new TLine(x1,y1,x1,y2);
   l3->SetLineWidth(3);
   l3->Draw("same");
   TLine *l4 = new TLine(x2,y1,x2,y2);
   l4->SetLineWidth(3);
   l4->Draw("same");

   TLegend *leg = new TLegend(0.7, 0.76, 0.9, 0.94);
   leg->SetFillColor(10);
   leg->SetFillStyle(10);
   leg->SetLineStyle(4000);
   leg->SetLineColor(10);
   leg->SetLineWidth(0.);
   leg->SetTextFont(42);
   leg->SetTextSize(0.045);
   leg->AddEntry(d0,leg0,"l");
   leg->AddEntry(d1,leg1,"l");
   leg->AddEntry(d2,leg2,"l");
   leg->Draw();

   c1->Update();
   char outputfile[100];
   sprintf(outputfile,"fig/%s.png",output);
   c1->SaveAs(outputfile);
   sprintf(outputfile,"fig/%s.pdf",output);
   c1->SaveAs(outputfile);

}

void plot(const TH1* d0, const TH1* d1, const TH1* d2, const TH1 *d3, double x1=0., double x2=1., double y1=0., double y2=10., const char* xtitle="p_{T} (GeV/c)", const char* ytitle="(d^{2}N)/(2#pip_{T}dp_{T}dy) (GeV/c)^{-2}", const char* leg0="a", const char* leg1="b", const char* leg2="c", const char* leg3="d", const char* output="test", const int logy=0)
{

  gROOT->Reset();

   TCanvas *c1 = new TCanvas("c1", "c1",0,0,800,600);
   gStyle->SetOptFit(0);
   gStyle->SetOptStat(0);
   gStyle->SetEndErrorSize(0.01);
   if(logy) c1->SetLogy();
   c1->SetFillColor(10);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetFrameFillColor(0);
   c1->SetFrameBorderMode(0);

   c1->SetGridx();
   c1->SetGridy();

   c1->SetLeftMargin(0.13);
   c1->SetBottomMargin(0.13);
   c1->SetTopMargin(0.02);
   c1->SetRightMargin(0.06);

   int i1 = d0->GetXaxis()->FindBin(x1+0.000001);
   int i2 = d0->GetXaxis()->FindBin(x2-0.000001);

   if(y2<=y1) {
     y2 = d0->GetMaximum()/0.8;
     if(logy) {
       y2 = d0->GetMaximum()/0.2;
     }
   }

   d0->GetXaxis()->SetRange(i1, i2);
   d0->SetMinimum(y1);
   d0->SetMaximum(y2);
   d0->GetXaxis()->SetNdivisions(208);
   d0->GetXaxis()->SetTitle(xtitle);
   d0->GetXaxis()->SetTitleOffset(0.9);
   d0->GetXaxis()->SetTitleSize(0.06);
   d0->GetXaxis()->SetLabelOffset(0.01);
   d0->GetXaxis()->SetLabelSize(0.045);
   d0->GetXaxis()->SetLabelFont(42);
   d0->GetXaxis()->SetTitleFont(42);
   d0->GetYaxis()->SetNdivisions(205);
   d0->GetYaxis()->SetTitle(ytitle);
   d0->GetYaxis()->SetTitleOffset(1.0);
   d0->GetYaxis()->SetTitleSize(0.06);
   d0->GetYaxis()->SetLabelOffset(0.005);
   d0->GetYaxis()->SetLabelSize(0.045);
   d0->GetYaxis()->SetLabelFont(42);
   d0->GetYaxis()->SetTitleFont(42);
   d0->SetLineWidth(2);
   d0->Draw();

   d1->SetLineWidth(2);
   d1->SetLineColor(2);
   d1->SetLineStyle(1);
   d1->Draw("same");

   d2->SetLineWidth(2);
   d2->SetLineColor(4);
   d2->SetLineStyle(1);
   d2->Draw("same");

   d3->SetLineWidth(2);
   d3->SetLineColor(6);
   d3->SetLineStyle(1);
   d3->Draw("same");

   TLine *l1 = new TLine(x1,y1,x2,y1);
   l1->SetLineWidth(3);
   l1->Draw("same");
   TLine *l2 = new TLine(x1,y2,x2,y2);
   l2->SetLineWidth(3);
   l2->Draw("same");
   TLine *l3 = new TLine(x1,y1,x1,y2);
   l3->SetLineWidth(3);
   l3->Draw("same");
   TLine *l4 = new TLine(x2,y1,x2,y2);
   l4->SetLineWidth(3);
   l4->Draw("same");

   TLegend *leg = new TLegend(0.7, 0.7, 0.9, 0.94);
   leg->SetFillColor(10);
   leg->SetFillStyle(10);
   leg->SetLineStyle(4000);
   leg->SetLineColor(10);
   leg->SetLineWidth(0.);
   leg->SetTextFont(42);
   leg->SetTextSize(0.045);
   leg->AddEntry(d0,leg0,"l");
   leg->AddEntry(d1,leg1,"l");
   leg->AddEntry(d2,leg2,"l");
   leg->AddEntry(d3,leg3,"l");
   leg->Draw();

   c1->Update();
   char outputfile[100];
   sprintf(outputfile,"fig/%s.png",output);
   c1->SaveAs(outputfile);
   sprintf(outputfile,"fig/%s.pdf",output);
   c1->SaveAs(outputfile);

}
*/
