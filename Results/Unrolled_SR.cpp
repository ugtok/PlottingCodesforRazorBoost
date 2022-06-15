#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TF1.h"
#include "TCanvas.h"
#include <stdio.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include "TString.h"
#include "TROOT.h"
#include "TStyle.h"
#include <TChain.h>
#include <math.h>
#include <TPad.h>
#include <TLegend.h>
#include <TLatex.h>
#include <THStack.h>
using namespace std;

void UnrolledPlots(){

  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  TH1::SetDefaultSumw2();

  TString dir = " /Users/ufuktok/Downloads/Datacard/run_2022_05_19_syst/"; 


  TFile* file1 = TFile::Open(dir+"Multijet.root");
  TFile* file2 = TFile::Open(dir+"Top.root");
  TFile* file3 = TFile::Open(dir+"WJet.root");
  TFile* file4 = TFile::Open(dir+"ZJet.root");
  TFile* file5 = TFile::Open(dir+"Multiboson.root");
  TFile* file6 = TFile::Open(dir+"T5ttcc.root");
  TFile* file7 = TFile::Open(dir+"TChiWZ.root");
  TFile* file8 = TFile::Open(dir+"TChiWH.root");

  string SigRegion[] = {
                        "SR_Had_1htop",     //////////// Hadronic channels start - 
                        "SR_Had_2htop", 
                        "SR_Had_V_b_45j", 
                        "SR_Had_V_b_6j", 
                        "SR_Had_1V_0b_34j", 
                        "SR_Had_1V_0b_5j", 
                        "SR_Had_2V_0b_24j", 
                        "SR_Had_2V_0b_5j",  //////////// Hadronic channels end.
                        "SR_Had_H_b_45j",  ////////////  Higgs channels start -
                        "SR_Had_H_b_6j", 
                        "SR_Had_2H_b_6j", 
                        "SR_Had_HV_b_6j", 
                        "SR_Had_1H_0b_34j",
                        "SR_Had_1H_0b_5j", 
                        "SR_Had_2H_0b_34j", 
                        "SR_Had_2H_0b_5j", 
                        "SR_Had_HV_0b_24j", 
                        "SR_Had_HV_0b_5j",
                        "SR_Lep_H_b", 
                        "SR_Lep_H_0b",      ///////////// Higgs channels end. 
                        "SR_Lep_1htop",     ////////////  Leptonic channels start -
                        "SR_Lep_V_b", 
                        "SR_Lep_V_0b",  
                        "SR_Leptop_0htop", 
                        "SR_Leptop_1htop",
                        "SR_Lepjet_0V_24j", 
                        "SR_Lepjet_0V_5j", 
                        "SR_Lepjet_1V_24j", 
                        "SR_Lepjet_1V_5j"   //////////// Leptonic channels end.
                                         };
TH2D* hist_1[8];
TH2D* hist_2[8];
TH2D* hist_3[8];
TH2D* htemp[8];

  //hist_1[0] = new TH2D("FirstSet", ";Bin;variation", 108, 0, 108, 23, 0, 23);
  //hist_2[0] = new TH2D("SecondSet", ";Bin;variation", 66, 0, 66, 23, 0, 23);
  hist_1[0] = new TH2D("FirstSet", ";Bin;variation", 64, 0, 64, 81, 0, 81);     // Hadronic -  8  -
  hist_2[0] = new TH2D("SecondSet", ";Bin;variation", 96, 0, 96, 81, 0, 81);    // Higgs    -  12 -
  hist_3[0] = new TH2D("ThirdSet", ";Bin;variation", 72, 0, 72, 81, 0, 81);     // Leptonic -  9  -

  for(int i=0;i<8;i++){ 
    hist_1[i]=(TH2D*)hist_1[0]->Clone();
    hist_2[i]=(TH2D*)hist_2[0]->Clone();  
    hist_3[i]=(TH2D*)hist_3[0]->Clone();  
  }
    
   for (int i=0; i<8;i++){         //  Hadronic SR
 
    htemp[0] = (TH2D*)file1->Get(Form("Background/MRR2_bkg_%s", SigRegion[i].c_str()));   // Multijet
    htemp[1] = (TH2D*)file2->Get(Form("Background/MRR2_bkg_%s", SigRegion[i].c_str()));   // Top
    htemp[2] = (TH2D*)file3->Get(Form("Background/MRR2_bkg_%s", SigRegion[i].c_str()));   // WJet
    htemp[3] = (TH2D*)file4->Get(Form("Background/MRR2_bkg_%s", SigRegion[i].c_str()));   // ZJet
    htemp[4] = (TH2D*)file5->Get(Form("Background/MRR2_bkg_%s", SigRegion[i].c_str()));   // Multiboson    
    htemp[5] = (TH2D*)file6->Get(Form("Signal/MRR2_S_signal_%s__1500_400", SigRegion[i].c_str()));
    htemp[6] = (TH2D*)file7->Get(Form("Signal/MRR2_S_signal_%s__700_200", SigRegion[i].c_str()));
    htemp[7] = (TH2D*)file8->Get(Form("Signal/MRR2_S_signal_%s__700_200", SigRegion[i].c_str()));


    for(int x=1;x<=8;x++){
      for(int y=1;y<=81;y++){
        hist_1[0]->SetBinContent(i*8+x, y, htemp[0]->GetBinContent(x,y));
        hist_1[1]->SetBinContent(i*8+x, y, htemp[1]->GetBinContent(x,y));
        hist_1[2]->SetBinContent(i*8+x, y, htemp[2]->GetBinContent(x,y));
        hist_1[3]->SetBinContent(i*8+x, y, htemp[3]->GetBinContent(x,y));
        hist_1[4]->SetBinContent(i*8+x, y, htemp[4]->GetBinContent(x,y));
        hist_1[5]->SetBinContent(i*8+x, y, htemp[5]->GetBinContent(x,y));
        hist_1[6]->SetBinContent(i*8+x, y, htemp[6]->GetBinContent(x,y));
        hist_1[7]->SetBinContent(i*8+x, y, htemp[7]->GetBinContent(x,y));

        hist_1[0]->SetBinError(i*8+x, y, htemp[0]->GetBinError(x,y));
        hist_1[1]->SetBinError(i*8+x, y, htemp[1]->GetBinError(x,y));
        hist_1[2]->SetBinError(i*8+x, y, htemp[2]->GetBinError(x,y));
        hist_1[3]->SetBinError(i*8+x, y, htemp[3]->GetBinError(x,y));
        hist_1[4]->SetBinError(i*8+x, y, htemp[4]->GetBinError(x,y));
        hist_1[5]->SetBinError(i*8+x, y, htemp[5]->GetBinError(x,y));
        hist_1[6]->SetBinError(i*8+x, y, htemp[6]->GetBinError(x,y));
        hist_1[7]->SetBinError(i*8+x, y, htemp[7]->GetBinError(x,y));         

      }
    }
  }

     for (int i=8; i<20;i++){         //  Hadronic Higgs SR
 
    htemp[0] = (TH2D*)file1->Get(Form("Background/MRR2_bkg_%s", SigRegion[i].c_str()));   // Multijet
    htemp[1] = (TH2D*)file2->Get(Form("Background/MRR2_bkg_%s", SigRegion[i].c_str()));   // Top
    htemp[2] = (TH2D*)file3->Get(Form("Background/MRR2_bkg_%s", SigRegion[i].c_str()));   // WJet
    htemp[3] = (TH2D*)file4->Get(Form("Background/MRR2_bkg_%s", SigRegion[i].c_str()));   // ZJet
    htemp[4] = (TH2D*)file5->Get(Form("Background/MRR2_bkg_%s", SigRegion[i].c_str()));   // Multiboson    
    htemp[5] = (TH2D*)file6->Get(Form("Signal/MRR2_S_signal_%s__1500_400", SigRegion[i].c_str()));
    htemp[6] = (TH2D*)file7->Get(Form("Signal/MRR2_S_signal_%s__700_200", SigRegion[i].c_str()));
    htemp[7] = (TH2D*)file8->Get(Form("Signal/MRR2_S_signal_%s__700_200", SigRegion[i].c_str()));


    for(int x=1;x<=8;x++){
      for(int y=1;y<=81;y++){
        hist_2[0]->SetBinContent((i-8)*8+x, y, htemp[0]->GetBinContent(x,y));
        hist_2[1]->SetBinContent((i-8)*8+x, y, htemp[1]->GetBinContent(x,y));
        hist_2[2]->SetBinContent((i-8)*8+x, y, htemp[2]->GetBinContent(x,y));
        hist_2[3]->SetBinContent((i-8)*8+x, y, htemp[3]->GetBinContent(x,y));
        hist_2[4]->SetBinContent((i-8)*8+x, y, htemp[4]->GetBinContent(x,y));
        hist_2[5]->SetBinContent((i-8)*8+x, y, htemp[5]->GetBinContent(x,y));
        hist_2[6]->SetBinContent((i-8)*8+x, y, htemp[6]->GetBinContent(x,y));
        hist_2[7]->SetBinContent((i-8)*8+x, y, htemp[7]->GetBinContent(x,y));

        hist_2[0]->SetBinError((i-8)*8+x, y, htemp[0]->GetBinError(x,y));
        hist_2[1]->SetBinError((i-8)*8+x, y, htemp[1]->GetBinError(x,y));
        hist_2[2]->SetBinError((i-8)*8+x, y, htemp[2]->GetBinError(x,y));
        hist_2[3]->SetBinError((i-8)*8+x, y, htemp[3]->GetBinError(x,y));
        hist_2[4]->SetBinError((i-8)*8+x, y, htemp[4]->GetBinError(x,y));
        hist_2[5]->SetBinError((i-8)*8+x, y, htemp[5]->GetBinError(x,y));
        hist_2[6]->SetBinError((i-8)*8+x, y, htemp[6]->GetBinError(x,y));
        hist_2[7]->SetBinError((i-8)*8+x, y, htemp[7]->GetBinError(x,y));         

      }
    }
  }

  for (int i=20; i<29;i++){    // Leptonic SR

    htemp[0] = (TH2D*)file1->Get(Form("Background/MRR2_bkg_%s", SigRegion[i].c_str()));
    htemp[1] = (TH2D*)file2->Get(Form("Background/MRR2_bkg_%s", SigRegion[i].c_str()));
    htemp[2] = (TH2D*)file3->Get(Form("Background/MRR2_bkg_%s", SigRegion[i].c_str()));
    htemp[3] = (TH2D*)file4->Get(Form("Background/MRR2_bkg_%s", SigRegion[i].c_str()));
    htemp[4] = (TH2D*)file5->Get(Form("Background/MRR2_bkg_%s", SigRegion[i].c_str()));
    htemp[5] = (TH2D*)file6->Get(Form("Signal/MRR2_S_signal_%s__1500_400", SigRegion[i].c_str()));
    htemp[6] = (TH2D*)file7->Get(Form("Signal/MRR2_S_signal_%s__700_200", SigRegion[i].c_str()));
    htemp[7] = (TH2D*)file8->Get(Form("Signal/MRR2_S_signal_%s__700_200", SigRegion[i].c_str()));

    for(int x=1;x<=8;x++){
      for(int y=1;y<=81;y++){
        hist_3[0]->SetBinContent((i-20)*8+x, y, htemp[0]->GetBinContent(x,y));
        hist_3[1]->SetBinContent((i-20)*8+x, y, htemp[1]->GetBinContent(x,y));
        hist_3[2]->SetBinContent((i-20)*8+x, y, htemp[2]->GetBinContent(x,y));
        hist_3[3]->SetBinContent((i-20)*8+x, y, htemp[3]->GetBinContent(x,y));
        hist_3[4]->SetBinContent((i-20)*8+x, y, htemp[4]->GetBinContent(x,y));
        hist_3[5]->SetBinContent((i-20)*8+x, y, htemp[5]->GetBinContent(x,y));
        hist_3[6]->SetBinContent((i-20)*8+x, y, htemp[6]->GetBinContent(x,y));
        hist_3[7]->SetBinContent((i-20)*8+x, y, htemp[7]->GetBinContent(x,y));

        hist_3[0]->SetBinError((i-20)*8+x, y, htemp[0]->GetBinError(x,y));
        hist_3[1]->SetBinError((i-20)*8+x, y, htemp[1]->GetBinError(x,y));
        hist_3[2]->SetBinError((i-20)*8+x, y, htemp[2]->GetBinError(x,y));
        hist_3[3]->SetBinError((i-20)*8+x, y, htemp[3]->GetBinError(x,y));
        hist_3[4]->SetBinError((i-20)*8+x, y, htemp[4]->GetBinError(x,y));
        hist_3[5]->SetBinError((i-20)*8+x, y, htemp[5]->GetBinError(x,y));
        hist_3[6]->SetBinError((i-20)*8+x, y, htemp[6]->GetBinError(x,y));
        hist_3[7]->SetBinError((i-20)*8+x, y, htemp[7]->GetBinError(x,y));

      }
    }
  }

  TH1D* histo_1[8];
  TH1D* histo_2[8];
  TH1D* histo_3[8];

  //histo_1[0] = new TH1D("First", ";Bin;Counts", 108, 0, 108);
  //histo_2[0] = new TH1D("Second", ";Bin;Counts", 66, 0, 66);
  histo_1[0] = new TH1D("First", ";Bin;Counts", 64, 0, 64);   // 8
  histo_2[0] = new TH1D("Second", ";Bin;Counts", 96, 0, 96);  // 12
  histo_3[0] = new TH1D("Third", ";Bin;Counts", 72, 0, 72);   // 9

  for(int i=0;i<8;i++) {
    histo_1[i]=(TH1D*)histo_1[0]->Clone();
    histo_2[i]=(TH1D*)histo_2[0]->Clone();
    histo_3[i]=(TH1D*)histo_3[0]->Clone();
  }

  double error_1, error_2, error_3;

  for(int i=0;i<8;i++){
    for(int x=1;x<=64;x++){
      error_1 = 0;
      histo_1[i]->SetBinContent(x, hist_1[i]->GetBinContent(x,1));
      error_1 += (hist_1[i]->GetBinError(x,1)*hist_1[i]->GetBinError(x,1));
      for(int y=2;y<=81;y++) {
        if(hist_1[i]->GetBinContent(x,1)-hist_1[i]->GetBinContent(x,y) > 0)error_1 += (hist_1[i]->GetBinContent(x,1)-hist_1[i]->GetBinContent(x,y))*(hist_1[i]->GetBinContent(x,1)-hist_1[i]->GetBinContent(x,y));
      }
      histo_1[i]->SetBinError(x, sqrt(error_1));
    }
  }

  for(int i=0;i<8;i++){
    for(int x=1;x<=96;x++){
      error_2 = 0;
      histo_2[i]->SetBinContent(x, hist_2[i]->GetBinContent(x,1));
      error_2 += (hist_2[i]->GetBinError(x,1)*hist_2[i]->GetBinError(x,1));
      for(int y=2;y<=81;y++) {
        if(hist_2[i]->GetBinContent(x,1)-hist_2[i]->GetBinContent(x,y) > 0)error_2 += (hist_2[i]->GetBinContent(x,1)-hist_2[i]->GetBinContent(x,y))*(hist_2[i]->GetBinContent(x,1)-hist_2[i]->GetBinContent(x,y));
      }
      histo_2[i]->SetBinError(x, sqrt(error_2));
    }
  }

  for(int i=0;i<8;i++){
    for(int x=1;x<=72;x++){
      error_3 = 0;
      histo_3[i]->SetBinContent(x, hist_3[i]->GetBinContent(x,1));
      error_3 += (hist_3[i]->GetBinError(x,1)*hist_3[i]->GetBinError(x,1));
      for(int y=2;y<=81;y++) {
        if(hist_3[i]->GetBinContent(x,1)-hist_3[i]->GetBinContent(x,y) > 0)error_2 += (hist_3[i]->GetBinContent(x,1)-hist_3[i]->GetBinContent(x,y))*(hist_3[i]->GetBinContent(x,1)-hist_3[i]->GetBinContent(x,y));
      }
      histo_3[i]->SetBinError(x, sqrt(error_3));
    }
  }

  histo_1[0]->SetFillColor(619);
  histo_1[1]->SetFillColor(633);
  histo_1[2]->SetFillColor(418);
  histo_1[3]->SetFillColor(401);
  histo_1[4]->SetFillColor(601);  
  histo_1[5]->SetLineColor(3);
  histo_1[5]->SetLineStyle(2);
  histo_1[5]->SetLineWidth(4);
  histo_1[6]->SetLineColor(1);
  histo_1[6]->SetLineStyle(2);
  histo_1[6]->SetLineWidth(4);
  histo_1[7]->SetLineColor(kMagenta);
  histo_1[7]->SetLineStyle(2);
  histo_1[7]->SetLineWidth(4);

  TH1D* total_1;
  total_1 = (TH1D*)histo_1[0]->Clone();
  total_1->Add(histo_1[1]);
  total_1->Add(histo_1[2]);
  total_1->Add(histo_1[3]);
  total_1->Add(histo_1[4]);  
  total_1->SetFillColor(13);
  total_1->SetFillStyle(3235);

  THStack *hs1_1 = new THStack("hs1_1","");
  hs1_1->Add(histo_1[4]);
  hs1_1->Add(histo_1[1]);
  hs1_1->Add(histo_1[2]);
  hs1_1->Add(histo_1[0]);
  hs1_1->Add(histo_1[3]);

//////////////////////////////////////////
  histo_2[0]->SetFillColor(619);
  histo_2[1]->SetFillColor(633);
  histo_2[2]->SetFillColor(418);
  histo_2[3]->SetFillColor(401);
  histo_2[4]->SetFillColor(601);  
  histo_2[5]->SetLineColor(3);
  histo_2[5]->SetLineStyle(2);
  histo_2[5]->SetLineWidth(4);
  histo_2[6]->SetLineColor(1);
  histo_2[6]->SetLineStyle(2);
  histo_2[6]->SetLineWidth(4);
  histo_2[7]->SetLineColor(kMagenta);
  histo_2[7]->SetLineStyle(2);
  histo_2[7]->SetLineWidth(4);

  TH1D* total_2;
  total_2 = (TH1D*)histo_2[3]->Clone();
  total_2->Add(histo_2[2]);
  total_2->Add(histo_2[1]);
  total_2->Add(histo_2[0]);
  total_2->Add(histo_2[4]);  
  total_2->SetFillColor(13);
  total_2->SetFillStyle(3235);

  THStack *hs1_2 = new THStack("hs1_2","");
  hs1_2->Add(histo_2[4]);
  hs1_2->Add(histo_2[1]);
  hs1_2->Add(histo_2[2]);
  hs1_2->Add(histo_2[0]);
  hs1_2->Add(histo_2[3]);

///////////////////////////////////////////
  histo_3[0]->SetFillColor(619);
  histo_3[1]->SetFillColor(633);
  histo_3[2]->SetFillColor(418);
  histo_3[3]->SetFillColor(401);
  histo_3[4]->SetFillColor(601);  
  histo_3[5]->SetLineColor(3);
  histo_3[5]->SetLineStyle(2);
  histo_3[5]->SetLineWidth(4);
  histo_3[6]->SetLineColor(1);
  histo_3[6]->SetLineStyle(2);
  histo_3[6]->SetLineWidth(4);
  histo_3[7]->SetLineColor(kMagenta);
  histo_3[7]->SetLineStyle(2);
  histo_3[7]->SetLineWidth(4);

  TH1D* total_3;
  total_3 = (TH1D*)histo_3[3]->Clone();
  total_3->Add(histo_3[2]);
  total_3->Add(histo_3[1]);
  total_3->Add(histo_3[0]);
  total_3->Add(histo_3[4]);  
  total_3->SetFillColor(13);
  total_3->SetFillStyle(3235);

  THStack *hs1_3 = new THStack("hs1_3","");
  hs1_3->Add(histo_3[4]);
  hs1_3->Add(histo_3[1]);
  hs1_3->Add(histo_3[2]);
  hs1_3->Add(histo_3[0]);
  hs1_3->Add(histo_3[3]);
////////////////////////////////////////////

  string MRR2Bins_1[64] = {"0-200", "200-300", "300-400", "400-500", "500-750", "750-850", "850-1000", "1000-3000", // SR_Had_1htop
                         "0-200", "200-300", "300-400", "400-500", "500-600", "600-800", "800-1000", "1000-3000",   // SR_Had_2htop
                         "0-200", "200-300", "300-350", "350-400", "400-500", "500-600", "600-800", "800-3000",     // SR_Had_V_b_45j
                         "0-200", "200-300", "300-350", "350-400", "400-500", "500-600", "600-800", "800-3000",     // SR_Had_V_b_6j
                         "0-200", "200-250", "250-300", "300-400", "400-500", "500-600", "600-1000", "1000-3000",   // SR_Had_1V_0b_34j
                         "0-200", "200-250", "250-300", "300-400", "400-500", "500-600", "600-1000", "1000-3000",   // SR_Had_1V_0b_5j
                         "0-200", "200-250", "250-300", "300-350", "350-500", "500-800", "800-1000", "1000-3000",   // SR_Had_2V_0b_24j
                         "0-200", "200-250", "250-300", "300-350", "350-450", "450-800", "800-1000", "1000-3000" }; // SR_Had_2V_0b_5j

  string MRR2Bins_2[96] = {"0-200", "200-250", "250-350", "350-450", "450-500", "500-600", "600-800", "800-3000",   // SR_Had_H_b_45j
                          "0-200", "200-300", "300-350", "350-400", "400-500", "500-600", "600-800","800-3000",   // SR_Had_H_b_6j
                          "0-200", "200-250", "250-300", "300-350", "350-400", "400-450", "450-600", "600-3000",    // SR_Had_2H_b_6j
                          "0-200", "200-250", "250-350", "350-400", "400-450", "450-500", "500-600", "600-3000",    // SR_Had_HV_b_6j
                          "0-200", "200-300", "300-350", "350-450", "450-650", "650-850", "850-1000", "1000-3000",  // SR_Had_1H_0b_34j
                          "0-200", "200-300", "300-350", "350-400", "400-500", "500-600", "600-800", "800-3000",  // SR_Had_1H_0b_5j
                          "0-250", "250-300", "300-350", "350-400", "400-450", "450-800", "800-1000", "1000-3000",  // SR_Had_2H_0b_34j
                          "0-250", "250-300", "300-350", "350-400", "400-450", "450-800", "800-1000", "1000-3000",  // SR_Had_2H_0b_5j
                          "0-200", "200-250", "250-300", "300-350", "350-400", "400-800", "800-1500", "1500-3000",  // SR_Had_HV_0b_24j
                          "0-200", "200-250", "250-300", "300-350", "350-400", "400-500", "500-600", "600-3000",  // SR_Had_HV_0b_5j
                          "0-250", "250-300", "300-350", "350-400", "400-450", "450-500", "500-800", "800-3000",    // SR_Lep_H_b
                          "0-200", "200-250", "250-300", "300-350", "350-400", "400-500", "500-600", "600-3000"};   // SR_Lep_H_0b

  string MRR2Bins_3[72] = {"0-200", "200-300", "300-400", "400-500", "500-600", "600-800", "800-1000", "1000-3000",   // SR_Lep_1htop
                          "0-200", "200-300", "300-350", "350-400", "400-500", "500-600", "600-1500", "1500-3000",    // SR_Lep_V_b
                          "0-200", "200-300", "300-350", "350-400", "400-500", "500-600", "600-700", "700-3000",    // SR_Lep_V_0b                      
                          "0-200", "200-300", "300-400", "400-500", "500-600", "600-800", "800-1000", "1000-3000",    // SR_Leptop_0htop
                          "0-300", "300-500", "500-600", "600-700", "700-750", "750-800", "800-1000", "1000-3000",  // SR_Leptop_1htop
                          "0-200", "200-300", "300-400", "400-500", "500-600", "600-700", "700-1000", "1000-3000", // SR_Lepjet_0V_24j
                          "0-200", "200-300", "300-400", "400-500", "500-600", "600-800", "800-1000", "1000-3000", // SR_Lepjet_0V_5j
                          "0-200", "200-250", "250-400", "400-450", "450-600", "600-1000", "1000-1500", "1500-3000", // SR_Lepjet_1V_24j 
                          "0-200", "200-250", "250-300", "300-350", "350-400", "400-600", "600-1000", "1000-3000"};  // SR_Lepjet_1V_5j


  TCanvas* c1 = new TCanvas("c1", "", 10000, 10000);
  c1->Divide(1,2);
  TPad *canvas_up = (TPad*)c1->GetListOfPrimitives()->FindObject("c1_1");
  TPad *canvas_dw = (TPad*)c1->GetListOfPrimitives()->FindObject("c1_2");
  double up_height     = 0.83; // please tune so that the upper figures size will meet your requirement
  double dw_correction = 0.98;//1.390 // please tune so that the smaller canvas size will work in your environment

  double dw_height    = (1. - up_height) * dw_correction;

  // set pad size
  canvas_up->SetPad(0., 1 - up_height, 1., 1.);
  canvas_dw->SetPad(0., 0., 1., dw_height);

  canvas_up->SetLogy();
  canvas_up->SetFrameFillColor(0);
  canvas_up->SetFillColor(0);
  canvas_dw->SetFillColor(0);
  canvas_dw->SetFrameFillColor(0);
  // set top margin 0 for bottom figure
  canvas_dw->SetTopMargin(0.03);//0.03
  canvas_dw->SetLeftMargin(0.1);
  canvas_dw->SetBottomMargin(0.3);
  /********************************************************/   
  canvas_up->cd();


  hs1_1->SetMaximum(1e5);
  hs1_1->SetMinimum(1e-1);
  hs1_1->Draw("hist");

  TLine* lines_1[7];
  TLatex* SR_names_Hadronic[7];

  for (int i = 0; i < 8; ++i){
      lines_1[i] = new TLine((i*8)+8,0,(i*8)+8,1e4);
      lines_1[i]->SetLineStyle(2);
      lines_1[i]->Draw("SAME");

      SR_names_Hadronic[i] = new TLatex((i*8)+4, 1e3, SigRegion[i].c_str());
      SR_names_Hadronic[i]->SetTextAlign(11);
      SR_names_Hadronic[i]->SetTextAngle(90);
      SR_names_Hadronic[i]->SetTextSize(0.015);
      SR_names_Hadronic[i]->SetTextFont(14);
      SR_names_Hadronic[i]->SetLineWidth(1);
      SR_names_Hadronic[i]->Draw("SAME");
  }

  histo_1[5]->Draw("sameHIST");
  histo_1[6]->Draw("sameHIST");
  histo_1[7]->Draw("sameHIST");

  total_1->Draw("SAME E2");

  //hs1_1->GetXaxis()->SetTitle("Bin Number");
  for(int i=1; i<=64; i++) hs1_1->GetXaxis()->SetBinLabel(i, MRR2Bins_1[i-1].c_str());
  hs1_1->GetXaxis()->SetLabelSize(0.03);
  hs1_1->GetYaxis()->SetTitle("Counts");

  string text = "CMS #scale[0.7]{#font[52]{Work in progress Run2}}";
  TLatex* cms_lat = new TLatex(1, 3e5, text.c_str());
  cms_lat->SetLineWidth(2);
  cms_lat->Draw();

  string text_1 = "#scale[0.7]{#font[52]{137 fb^{-1} (13 TeV)}}";
  TLatex* era_lat = new TLatex(64*0.95,3e5, text_1.c_str());
  era_lat->SetTextAlign(36);
  era_lat->SetLineWidth(2);
  era_lat->Draw();

  string NM1 = "#scale[0.7]{#font[52]{Hadronic channels, }}";
  TLatex* name_1 = new TLatex(8, 0.9e5, NM1.c_str());
  name_1->SetLineWidth(2);
  name_1->SetTextColor(kRed);
  name_1->Draw();

  TLegend* leg = new TLegend(0.55,0.80,0.9,0.9);
  char legentry[6];

  leg->SetNColumns(4);
  leg->SetTextSize(0.02);

  leg->AddEntry(histo_1[0],  "Multijet", "f");
  leg->AddEntry(histo_1[1],  "t#bar{t} + single top", "f");
  leg->AddEntry(histo_1[2],  "W(#rightarrowl#nu)", "f");
  leg->AddEntry(histo_1[3],  "Z(#rightarrow#nu#nu)", "f");
  leg->AddEntry(histo_1[4],  "VV(V) + t#bar{t}(X)", "f");

  leg->AddEntry(histo_1[5], "T5ttcc", "l");
  leg->AddEntry(histo_1[6], "TChiWZ", "l");
  leg->AddEntry(histo_1[7], "TChiWH", "l");

  leg->SetFillColor(0);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->Draw();

  canvas_dw->cd();                                                                                                                                                                                                                          
  gPad->SetGridy();
  TH1D* dividend1 = (TH1D*)total_1->Clone();
  for(int i=1;i<=total_1->GetNbinsX();i++){
    dividend1->SetBinContent(i,1);
    if(total_1->GetBinContent(i)==0) dividend1->SetBinError(i,0);
    else dividend1->SetBinError(i,total_1->GetBinError(i)/total_1->GetBinContent(i));
  }
  dividend1->SetFillColor(12);
  dividend1->SetFillStyle(3004);
  dividend1->SetMarkerStyle(1);
  dividend1->GetYaxis()->SetTitle("");
  dividend1->GetXaxis()->SetTitle("M_{R}*R^{2} (GeV)");
  dividend1->GetXaxis()->SetTitleOffset(0.45);
  dividend1->GetXaxis()->SetTitleSize(0.15);
  dividend1->GetYaxis()->SetLabelSize(0.12);

  dividend1->Draw("E2");

  c1->SaveAs("MRR2_Hadronic_NewBin_4.png"); 
  c1->Close();

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                    // HADRONIC HIGGS SIGNAL REGION   //
                                   //                                //

  TCanvas* c2 = new TCanvas("c2", "", 10000, 10000);
  c2->Divide(1,2);
  TPad *canvas_up_2 = (TPad*)c2->GetListOfPrimitives()->FindObject("c2_1");
  TPad *canvas_dw_2 = (TPad*)c2->GetListOfPrimitives()->FindObject("c2_2");
  
  // set pad size
  canvas_up_2->SetPad(0., 1 - up_height, 1., 1.);
  canvas_dw_2->SetPad(0., 0., 1., dw_height);

  canvas_up_2->SetLogy();
  canvas_up_2->SetFrameFillColor(0);
  canvas_up_2->SetFillColor(0);
  canvas_dw_2->SetFillColor(0);
  canvas_dw_2->SetFrameFillColor(0);
  // set top margin 0 for bottom figure
  canvas_dw_2->SetTopMargin(0.03);//0.03
  canvas_dw_2->SetLeftMargin(0.1);
  canvas_dw_2->SetBottomMargin(0.3);
  /***************************************************************/   
  canvas_up_2->cd();
  hs1_2->SetMaximum(1e5);
  hs1_2->SetMinimum(1e-1);
  hs1_2->Draw("hist");

  TLine* lines_2[11];
  TLatex* SR_names_Higgs[11];

  for (int i = 8; i < 20; ++i){
      lines_2[i] = new TLine(((i-8)*8)+8,0,((i-8)*8)+8,1e4);
      lines_2[i]->SetLineStyle(2);
      lines_2[i]->Draw("SAME");

      SR_names_Higgs[i] = new TLatex(((i-8)*8)+4, 1e3, SigRegion[i].c_str());
      SR_names_Higgs[i]->SetTextAlign(11);
      SR_names_Higgs[i]->SetTextAngle(90);
      SR_names_Higgs[i]->SetTextSize(0.015);
      SR_names_Higgs[i]->SetTextFont(14);
      SR_names_Higgs[i]->SetLineWidth(1);
      SR_names_Higgs[i]->Draw("SAME");
  }

  histo_2[5]->Draw("sameHIST");
  histo_2[6]->Draw("sameHIST");
  histo_2[7]->Draw("sameHIST");
  total_2->Draw("SAME E2");

  for(int i=1; i<=96; i++) hs1_2->GetXaxis()->SetBinLabel(i, MRR2Bins_2[i-1].c_str());
  hs1_2->GetXaxis()->SetLabelSize(0.03);
  hs1_2->GetYaxis()->SetTitle("Counts");

  string text_2 = "CMS #scale[0.7]{#font[52]{Work in progress Run2}}";
  TLatex* cms_lat_2 = new TLatex(1, 3e5, text_2.c_str());
  cms_lat_2->SetLineWidth(2);
  cms_lat_2->Draw();

  string text_22 = "#scale[0.7]{#font[52]{137 fb^{-1} (13 TeV)}}";
  TLatex* era_lat_2 = new TLatex(96*0.95,3e5, text_22.c_str());
  era_lat_2->SetTextAlign(36);
  era_lat_2->SetLineWidth(2);
  era_lat_2->Draw();

  string NM2 = "#scale[0.7]{#font[52]{Higgs channels }}";
  TLatex* name_2 = new TLatex(8, 0.9e5, NM2.c_str());
  name_2->SetLineWidth(2);
  name_2->SetTextColor(kRed);
  name_2->Draw();

  TLegend* leg_2 = new TLegend(0.55,0.80,0.9,0.9);
  char leg_2entry[6];

  leg_2->SetNColumns(4);
  leg_2->SetTextSize(0.02);

  leg_2->AddEntry(histo_2[0],  "Multijet", "f");
  leg_2->AddEntry(histo_2[1],  "t#bar{t} + single top", "f");
  leg_2->AddEntry(histo_2[2],  "W(#rightarrowl#nu)", "f");
  leg_2->AddEntry(histo_2[3],  "Z(#rightarrow#nu#nu)", "f");
  leg_2->AddEntry(histo_2[4],  "VV(V) + t#bar{t}(X)", "f");

  leg_2->AddEntry(histo_2[5], "T5ttcc", "l");
  leg_2->AddEntry(histo_2[6], "TChiWZ", "l");
  leg_2->AddEntry(histo_2[7], "TChiWH", "l");

  leg_2->SetFillColor(0);
  leg_2->SetFillStyle(0);
  leg_2->SetBorderSize(0);
  leg_2->Draw();

  canvas_dw_2->cd();                                                                                                                                                                                                                          
  gPad->SetGridy();
  TH1D* dividend2 = (TH1D*)total_2->Clone();
  for(int i=1;i<=total_2->GetNbinsX();i++){
    dividend2->SetBinContent(i,1);
    if(total_2->GetBinContent(i)==0) dividend2->SetBinError(i,0);
    else dividend2->SetBinError(i,total_2->GetBinError(i)/total_2->GetBinContent(i));
  }
  dividend2->SetFillColor(12);
  dividend2->SetFillStyle(3004);
  dividend2->SetMarkerStyle(1);
  dividend2->GetYaxis()->SetTitle("");
  dividend2->GetXaxis()->SetTitle("M_{R}*R^{2} (GeV)");
  dividend2->GetXaxis()->SetTitleOffset(0.45);
  dividend2->GetXaxis()->SetTitleSize(0.15);
  dividend2->GetYaxis()->SetLabelSize(0.12);

  dividend2->Draw("E2");

  c2->SaveAs("MRR2_HiggsSR_NewBin_4.png");
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                    // LEPTONIC SIGNAL REGION   //
                                   //                                //

  TCanvas* c3 = new TCanvas("c3", "", 10000, 10000);
  c3->Divide(1,2);
  TPad *canvas_up_3 = (TPad*)c3->GetListOfPrimitives()->FindObject("c3_1");
  TPad *canvas_dw_3 = (TPad*)c3->GetListOfPrimitives()->FindObject("c3_2");
  
  // set pad size
  canvas_up_3->SetPad(0., 1 - up_height, 1., 1.);
  canvas_dw_3->SetPad(0., 0., 1., dw_height);

  canvas_up_3->SetLogy();
  canvas_up_3->SetFrameFillColor(0);
  canvas_up_3->SetFillColor(0);
  canvas_dw_3->SetFillColor(0);
  canvas_dw_3->SetFrameFillColor(0);
  // set top margin 0 for bottom figure
  canvas_dw_3->SetTopMargin(0.03);//0.03
  canvas_dw_3->SetLeftMargin(0.1);
  canvas_dw_3->SetBottomMargin(0.3);
  /***************************************************************/   
  canvas_up_3->cd();
  hs1_3->SetMaximum(1e5);
  hs1_3->SetMinimum(1e-1);
  hs1_3->Draw("hist");

  TLine* lines_3[8];
  TLatex* SR_names_Leptonic[8];

  for (int i = 20; i < 29; ++i){
      lines_3[i] = new TLine(((i-20)*8)+8,0,((i-20)*8)+8,1e4);
      lines_3[i]->SetLineStyle(2);
      lines_3[i]->Draw("SAME");

      SR_names_Leptonic[i] = new TLatex(((i-20)*8)+4, 1e3, SigRegion[i].c_str());
      SR_names_Leptonic[i]->SetTextAlign(11);
      SR_names_Leptonic[i]->SetTextAngle(90);
      SR_names_Leptonic[i]->SetTextSize(0.015);
      SR_names_Leptonic[i]->SetTextFont(14);
      SR_names_Leptonic[i]->SetLineWidth(1);
      SR_names_Leptonic[i]->Draw("SAME");
  }

  histo_3[5]->Draw("sameHIST");
  histo_3[6]->Draw("sameHIST");
  histo_3[7]->Draw("sameHIST");
  total_3->Draw("SAME E2");

  for(int i=1; i<=72; i++) hs1_3->GetXaxis()->SetBinLabel(i, MRR2Bins_3[i-1].c_str());
  hs1_3->GetXaxis()->SetLabelSize(0.03);
  hs1_3->GetYaxis()->SetTitle("Counts");

  string text_3 = "CMS #scale[0.7]{#font[52]{Work in progress Run2}}";
  TLatex* cms_lat_3 = new TLatex(1, 3e5, text_3.c_str());
  cms_lat_3->SetLineWidth(2);
  cms_lat_3->Draw();

  string text_33 = "#scale[0.7]{#font[52]{137 fb^{-1} (13 TeV)}}";
  TLatex* era_lat_3 = new TLatex(72*0.95,3e5, text_33.c_str());
  era_lat_3->SetTextAlign(36);
  era_lat_3->SetLineWidth(2);
  era_lat_3->Draw();

  string NM3 = "#scale[0.7]{#font[52]{Leptonic channels }}";
  TLatex* name_3 = new TLatex(8, 0.9e5, NM3.c_str());
  name_3->SetLineWidth(2);
  name_3->SetTextColor(kRed);
  name_3->Draw();

  TLegend* leg_3 = new TLegend(0.55,0.80,0.9,0.9);
  char leg_3entry[6];

  leg_3->SetNColumns(4);
  leg_3->SetTextSize(0.02);

  leg_3->AddEntry(histo_2[0],  "Multijet", "f");
  leg_3->AddEntry(histo_2[1],  "t#bar{t} + single top", "f");
  leg_3->AddEntry(histo_2[2],  "W(#rightarrowl#nu)", "f");
  leg_3->AddEntry(histo_2[3],  "Z(#rightarrow#nu#nu)", "f");
  leg_3->AddEntry(histo_2[4],  "VV(V) + t#bar{t}(X)", "f");

  leg_3->AddEntry(histo_2[5], "T5ttcc", "l");
  leg_3->AddEntry(histo_2[6], "TChiWZ", "l");
  leg_3->AddEntry(histo_2[7], "TChiWH", "l");

  leg_3->SetFillColor(0);
  leg_3->SetFillStyle(0);
  leg_3->SetBorderSize(0);
  leg_3->Draw();

  canvas_dw_3->cd();                                                                                                                                                                                                                          
  gPad->SetGridy();
  TH1D* dividend3 = (TH1D*)total_3->Clone();
  for(int i=1;i<=total_3->GetNbinsX();i++){
    dividend3->SetBinContent(i,1);
    if(total_3->GetBinContent(i)==0) dividend3->SetBinError(i,0);
    else dividend3->SetBinError(i,total_3->GetBinError(i)/total_3->GetBinContent(i));
  }
  dividend3->SetFillColor(12);
  dividend3->SetFillStyle(3004);
  dividend3->SetMarkerStyle(1);
  dividend3->GetYaxis()->SetTitle("");
  dividend3->GetXaxis()->SetTitle("M_{R}*R^{2} (GeV)");
  dividend3->GetXaxis()->SetTitleOffset(0.45);
  dividend3->GetXaxis()->SetTitleSize(0.15);
  dividend3->GetYaxis()->SetLabelSize(0.12);

  dividend3->Draw("E2");

  c3->SaveAs("MRR2_Leptonic_NewBin_4.png"); 

}

void Unrolled_SR(){
  UnrolledPlots();
}
