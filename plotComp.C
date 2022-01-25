#include <stdio.h>
#include "iomanip.h"

void plotComp(const TH1* d0, const TH1* d1, double x1=0., double x2=1., double y1=0., double y2=10., const char* xtitle="p_{T} (GeV/c)", const char* ytitle="(d^{2}N)/(2#pip_{T}dp_{T}dy) (GeV/c)^{-2}", const char* output="test", const int logy=0, const int scale=1)
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

   int i1 = d0->GetXaxis()->FindBin(x1+0.0001);
   int i2 = d0->GetXaxis()->FindBin(x2-0.0001);

   double n1 = d0->Integral(i1, i2);
   double n2 = d1->Integral(i1, i2);
   double nn = d1->GetNbinsX();
   if(scale) {
     if(n2>nn) {
       d0->Scale(n2/n1);
     } else {
       double nn1 = d0->GetMaximum();
       double nn2 = d1->GetMaximum();
       d0->Scale(nn2/nn1);
     }
   }
   
   if(y2<=y1) {
     y1 = -d0->GetMaximum()*0.1;
     y2 = d0->GetMaximum()/0.7;
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
   d0->SetLineStyle(1);
   d0->Draw();

   d1->SetLineWidth(2);
   d1->SetLineColor(2);
   d1->Draw("same e");


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
   sprintf(outputfile,"fig/%s.eps",output);
   c1->SaveAs(outputfile);

}
