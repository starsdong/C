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
   //   d0->Sumw2();
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

void plot(TGraphErrors* gr, double x1=0., double x2=1., double y1=0., double y2=10., const char* xtitle="p_{T} (GeV/c)", const char* ytitle="(d^{2}N)/(2#pip_{T}dp_{T}dy) (GeV/c)^{-2}", const char* output="test", const int logy=0, TF1* fitfun = 0, double xfit1=0., double xfit2=1., double *par = 0)
{
   TCanvas *c1 = new TCanvas("c1", "c1",0,0,800,600);
   if(logy) c1->SetLogy();

   if(y2<=y1) {
     y2 = d0->GetMaximum()/0.8;
     if(logy) y2 = d0->GetMaximum()/0.2;
   }

   TH1D *d0 = new TH1D("d0","",1,x1,x2);
   d0->SetMinimum(y1);
   d0->SetMaximum(y2);
   d0->GetXaxis()->SetTitle(xtitle);
   d0->GetYaxis()->SetTitle(ytitle);
   d0->Draw();

   gr->SetLineWidth(2);
   gr->Draw("p");

   if(fitfun) {
     fitfun->SetParameters(par);
     fitfun->SetLineWidth(2);
     fitfun->SetLineColor(2);
     gr->Fit(fitfun,"R");

     fitfun->GetParameters(par);
   }

   drawHistBox(x1,x2,y1,y2);

   c1->Update();
   char outputfile[100];
   sprintf(outputfile,"fig/%s.png",output);
   c1->SaveAs(outputfile);
   sprintf(outputfile,"fig/%s.pdf",output);
   c1->SaveAs(outputfile);

}

void plot(TGraph* gr, double x1=0., double x2=1., double y1=0., double y2=10., const char* xtitle="p_{T} (GeV/c)", const char* ytitle="(d^{2}N)/(2#pip_{T}dp_{T}dy) (GeV/c)^{-2}", const char* output="test", const int logy=0)
{
   TCanvas *c1 = new TCanvas("c1", "c1",0,0,800,600);
   if(logy) c1->SetLogy();

   if(y2<=y1) {
     y2 = d0->GetMaximum()/0.8;
     if(logy) y2 = d0->GetMaximum()/0.2;
   }

   TH1D *d0 = new TH1D("d0","",1,x1,x2);
   d0->SetMinimum(y1);
   d0->SetMaximum(y2);
   d0->GetXaxis()->SetTitle(xtitle);
   d0->GetYaxis()->SetTitle(ytitle);
   d0->Draw();

   gr->SetLineWidth(2);
   gr->Draw("c");

   drawHistBox(x1,x2,y1,y2);

   c1->Update();
   char outputfile[100];
   sprintf(outputfile,"fig/%s.png",output);
   c1->SaveAs(outputfile);
   sprintf(outputfile,"fig/%s.pdf",output);
   c1->SaveAs(outputfile);

}


void plot(TGraph* gr1, TGraph* gr2, double x1=0., double x2=1., double y1=0., double y2=10., const char* xtitle="p_{T} (GeV/c)", const char* ytitle="(d^{2}N)/(2#pip_{T}dp_{T}dy) (GeV/c)^{-2}", const char* output="test", const int logy=0, const int icolor=1)
{
   TCanvas *c1 = new TCanvas("c1", "c1",0,0,800,600);
   if(logy) c1->SetLogy();

   if(y2<=y1) {
     y2 = d0->GetMaximum()/0.8;
     if(logy) y2 = d0->GetMaximum()/0.2;
   }

   TH1D *d0 = new TH1D("d0","",1,x1,x2);
   d0->SetMinimum(y1);
   d0->SetMaximum(y2);
   d0->GetXaxis()->SetTitle(xtitle);
   d0->GetYaxis()->SetTitle(ytitle);
   d0->Draw();

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

   drawHistBox(x1,x2,y1,y2);

   c1->Update();
   char outputfile[100];
   sprintf(outputfile,"fig/%s.png",output);
   c1->SaveAs(outputfile);
   sprintf(outputfile,"fig/%s.pdf",output);
   c1->SaveAs(outputfile);

}

void plot(TH1* d0, double x1=0., double x2=1., double y1=0., double y2=10., const char* xtitle="p_{T} (GeV/c)", const char* ytitle="(d^{2}N)/(2#pip_{T}dp_{T}dy) (GeV/c)^{-2}", const char* output="test", const int logy=0, TF1* fitfun = 0)
{

   TCanvas *c1 = new TCanvas("c1", "c1",0,0,800,600);
   if(logy) c1->SetLogy();

   int i1 = d0->GetXaxis()->FindBin(x1+0.00001);
   int i2 = d0->GetXaxis()->FindBin(x2-0.00001);

   if(y2<=y1) {
     y2 = d0->GetMaximum()/0.8;
     if(logy) y2 = d0->GetMaximum()/0.2;
   }

   d0->GetXaxis()->SetRange(i1, i2);
   d0->SetMinimum(y1);
   d0->SetMaximum(y2);
   d0->GetXaxis()->SetTitle(xtitle);
   d0->GetYaxis()->SetTitle(ytitle);
   d0->SetLineWidth(2);
   d0->SetLineColor(1);
   if(fitfun) d0->Draw("e");
   else d0->Draw();

   if(fitfun) {
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

void plot(TGraphErrors* gr, double x1=0., double x2=1., double y1=0., double y2=10., const char* xtitle="p_{T} (GeV/c)", const char* ytitle="(d^{2}N)/(2#pip_{T}dp_{T}dy) (GeV/c)^{-2}", const char* output="test", const int logy=0, TF1* func = 0)
{
   TCanvas *c1 = new TCanvas("c1", "c1",0,0,800,600);
   if(logy) c1->SetLogy();

   if(y2<=y1) {
     y2 = d0->GetMaximum()/0.8;
     if(logy) y2 = d0->GetMaximum()/0.2;
   }

   TH1D *d0 = new TH1D("d0","",1,x1,x2);
   d0->SetMinimum(y1);
   d0->SetMaximum(y2);
   d0->GetXaxis()->SetTitle(xtitle);
   d0->GetYaxis()->SetTitle(ytitle);
   d0->SetLineWidth(2);
   d0->Draw();

   gr->SetMarkerSize(1.8);
   gr->SetMarkerStyle(20);
   gr->SetLineWidth(2);
   gr->Draw("p");

   if(func) {
     func->SetLineWidth(2);
     func->SetLineColor(2);
     gr->Fit(func,"R");
   }

   drawHistBox(x1,x2,y1,y2);

   c1->Update();
   char outputfile[100];
   sprintf(outputfile,"fig/%s.png",output);
   c1->SaveAs(outputfile);
   sprintf(outputfile,"fig/%s.pdf",output);
   c1->SaveAs(outputfile);

}

void plot(TH1* d0, TH1* d1, double x1=0., double x2=1., double y1=0., double y2=10., const char* xtitle="p_{T} (GeV/c)", const char* ytitle="(d^{2}N)/(2#pip_{T}dp_{T}dy) (GeV/c)^{-2}", const char* leg0="a", const char* leg1="b",const char* output="test", const int logy=0)
{

  TCanvas *c1 = new TCanvas("c1","c1",0,0,800,600);
   if(logy) c1->SetLogy();

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
   d0->GetXaxis()->SetTitle(xtitle);
   d0->GetYaxis()->SetTitle(ytitle);
   d0->SetLineWidth(2);
   d0->Draw();

   d1->SetLineWidth(2);
   d1->SetLineColor(2);
   d1->SetLineStyle(2);
   d1->Draw("same");


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

   drawHistBox(x1,x2,y1,y2);
   
   c1->Update();
   char outputfile[100];
   sprintf(outputfile,"fig/%s.png",output);
   c1->SaveAs(outputfile);
   sprintf(outputfile,"fig/%s.pdf",output);
   c1->SaveAs(outputfile);

}

void plot(TH1* d0, TH1* d1, TH1* d2, double x1=0., double x2=1., double y1=0., double y2=10., const char* xtitle="p_{T} (GeV/c)", const char* ytitle="(d^{2}N)/(2#pip_{T}dp_{T}dy) (GeV/c)^{-2}", const char* leg0="a", const char* leg1="b", const char* leg2="c", const char* output="test", const int logy=0)
{

   TCanvas *c1 = new TCanvas("c1", "c1",0,0,800,600);
   if(logy) c1->SetLogy();

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
   d0->GetXaxis()->SetTitle(xtitle);
   d0->GetYaxis()->SetTitle(ytitle);
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

   drawHistBox(x1,x2,y1,y2);
   
   c1->Update();
   char outputfile[100];
   sprintf(outputfile,"fig/%s.png",output);
   c1->SaveAs(outputfile);
   sprintf(outputfile,"fig/%s.pdf",output);
   c1->SaveAs(outputfile);

}

void plot(TH1* d0, TH1* d1, TH1* d2, TH1 *d3, double x1=0., double x2=1., double y1=0., double y2=10., const char* xtitle="p_{T} (GeV/c)", const char* ytitle="(d^{2}N)/(2#pip_{T}dp_{T}dy) (GeV/c)^{-2}", const char* leg0="a", const char* leg1="b", const char* leg2="c", const char* leg3="d", const char* output="test", const int logy=0)
{
   TCanvas *c1 = new TCanvas("c1", "c1",0,0,800,600);
   if(logy) c1->SetLogy();

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
   d0->GetXaxis()->SetTitle(xtitle);
   d0->GetYaxis()->SetTitle(ytitle);
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

   drawHistBox(x1,x2,y1,y2);

   c1->Update();
   char outputfile[100];
   sprintf(outputfile,"fig/%s.png",output);
   c1->SaveAs(outputfile);
   sprintf(outputfile,"fig/%s.pdf",output);
   c1->SaveAs(outputfile);

}
