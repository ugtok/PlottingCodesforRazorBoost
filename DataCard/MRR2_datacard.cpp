#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TF1.h"
#include <TH1D.h>
#include <TH2D.h>
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
#include <TLegend.h>
#include <TLatex.h>
#include <THStack.h>
using namespace std;

void UnrolledPlots(string period, TString sample){


  // 23 systematics variations in total
  string Systematic[] = {"_nom", "_topptUp", "_topptDown",  "_isrUp", "_isrDown", "_pileupUp", "_pileupDown", "_L1PreFiringUp", "_L1PreFiringDown", "_alphasUp", "_alphasDown", "_scaleUp", "_scaleDown", "_lostlepUp", "_lostlepDown", "_triggerUp", "_triggerDown", "_jesUp", "_jesDown", "_jerUp", "_jerDown", "_metUp", "_metDown"}; 
  int sizeSytematics = sizeof(Systematic)/sizeof(Systematic[0]);

  // 29 Signal Regions in total
  string SigRegion[] = {"SR_Had_1htop", "SR_Had_2htop", "SR_Had_V_b_45j", "SR_Had_V_b_6j", "SR_Had_1V_0b_34j", "SR_Had_1V_0b_5j", "SR_Had_2V_0b_24j", "SR_Had_2V_0b_5j", "SR_Had_H_b_45j", "SR_Had_H_b_6j", "SR_Had_2H_b_6j", "SR_Had_HV_b_6j", "SR_Had_1H_0b_34j", "SR_Had_1H_0b_5j", "SR_Had_2H_0b_34j", "SR_Had_2H_0b_5j", "SR_Had_HV_0b_24j", "SR_Had_HV_0b_5j", "SR_Lep_1htop", "SR_Lep_V_b", "SR_Lep_V_0b", "SR_Lep_H_b", "SR_Lep_H_0b", "SR_Leptop_0htop", "SR_Leptop_1htop", "SR_Lepjet_0V_24j", "SR_Lepjet_0V_5j", "SR_Lepjet_1V_24j", "SR_Lepjet_1V_5j"};
  int sizeRegions = sizeof(SigRegion)/sizeof(SigRegion[0]);
  cout<< " # of Signal Regions ----->  " << sizeRegions <<endl;

  string MassPoints[994];
  string line;
  int loop = 0; 

  ifstream textfile ("massbins_T5ttcc.txt");

  if(textfile.is_open()){

      while (!textfile.eof()){    // Read from massbins_T5ttcc.txt text file into array of strings.

          getline(textfile,line);
          MassPoints[loop] = line;
          loop++;
      }
  }

int sizeMassPoints = sizeof(MassPoints)/sizeof(MassPoints[0]);
cout<< " # of MassPoints 1 ------>  " <<MassPoints[0]<<endl;

  TFile* file0 = TFile::Open(sample);
  TFile* file1 = TFile::Open("run_2021_10_26_syst.root");

  //TH2D* data_2D[sizeRegions];
  //TH2D* Top_2D[sizeRegions];
  TH2D* ZtoNu_2D[sizeRegions];
  TH2D* WtoL_2D[sizeRegions];
  TH2D* MultiBoson_2D[sizeRegions];
  //TH2D* Multijet_2D[sizeRegions];
  //TH2D* GJet_2D[sizeRegions];
  TH2D* TPow_2D[sizeRegions];
  //TH2D* DY_2D[sizeRegions];
  TH2D* Higgs_2D[sizeRegions];
  TH2D* Sig_2D[sizeMassPoints][sizeRegions];

  file0->cd();
  for (int i = 0; i < sizeRegions; ++i)
  {
      cout<<" i " << i << "   "<<SigRegion[i]<<endl;
      //data_2D[i]       = (TH2D*)file0->Get(Form("Counts_vs_MRR2Bins/Syst_vs_MRR2Bins/Data_%s_%s", period.c_str(), SigRegion[i].c_str()));
      //Top_2D[i]        = (TH2D*)file1->Get(Form("Counts_vs_MRR2Bins/Syst_vs_MRR2Bins/Top_%s_%s", period.c_str(), SigRegion[i].c_str()));
      ZtoNu_2D[i]      = (TH2D*)file1->Get(Form("Counts_vs_MRR2Bins/Syst_vs_MRR2Bins/ZToNuNu_%s_%s", period.c_str(), SigRegion[i].c_str()));
      WtoL_2D[i]       = (TH2D*)file1->Get(Form("Counts_vs_MRR2Bins/Syst_vs_MRR2Bins/WToLNu_%s_%s", period.c_str(), SigRegion[i].c_str()));
      MultiBoson_2D[i] = (TH2D*)file1->Get(Form("Counts_vs_MRR2Bins/Syst_vs_MRR2Bins/Multiboson_%s_%s", period.c_str(), SigRegion[i].c_str()));
      //Multijet_2D[i]   = (TH2D*)file1->Get(Form("Counts_vs_MRR2Bins/Syst_vs_MRR2Bins/Multijet_%s_%s", period.c_str(), SigRegion[i].c_str()));
      //GJet_2D[i]       = (TH2D*)file1->Get(Form("Counts_vs_MRR2Bins/Syst_vs_MRR2Bins/GJets_%s_%s", period.c_str(), SigRegion[i].c_str()));
      TPow_2D[i]       = (TH2D*)file1->Get(Form("Counts_vs_MRR2Bins/Syst_vs_MRR2Bins/TT_powheg_pythia8_%s_%s", period.c_str(), SigRegion[i].c_str()));
      //DY_2D[i]         = (TH2D*)file1->Get(Form("Counts_vs_MRR2Bins/Syst_vs_MRR2Bins/DYToLL_%s_%s", period.c_str(), SigRegion[i].c_str()));
      Higgs_2D[i]      = (TH2D*)file1->Get(Form("Counts_vs_MRR2Bins/Syst_vs_MRR2Bins/Higgs_%s_%s", period.c_str(), SigRegion[i].c_str()));      
      for (int j=0; j < sizeMassPoints; j++) {
        //cout<<j<<endl;
        Sig_2D[i][j] = (TH2D*)file0->Get(Form("Signal/SMS-T5ttcc_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_%s_%s", SigRegion[i].c_str(), MassPoints[j].c_str()));
      }
  }

  int n_var = (Sig_2D[1][1]->GetNbinsY()-1)/2; //number of variations*2 // number of syst =23, n_var=11, nbiny = 23 , nbinx = 6

  //cout<< " # of Systematic variations --> "<<Top_2D[12]->GetNbinsY()<<endl;

  //TH1D* data_1D[sizeRegions];
  //TH1D* Top_1D[sizeRegions];
  TH1D* ZtoNu_1D[sizeRegions];
  TH1D* WtoL_1D[sizeRegions];
  TH1D* MultiBoson_1D[sizeRegions];
  //TH1D* Multijet_1D[sizeRegions];
  //TH1D* GJet_1D[sizeRegions];
  TH1D* TPow_1D[sizeRegions];
  //TH1D* DY_1D[sizeRegions];
  TH1D* Higgs_1D[sizeRegions];
  TH1D* Sig_1D[sizeRegions][sizeMassPoints];

for (int i = 0; i < sizeRegions; ++i){
  for (int j = 0; j < sizeMassPoints; ++j){
     
    TString name_Sig = Sig_2D[i][j]->GetName();
    Sig_1D[i][j]     = new TH1D(Form(name_Sig+"_%d"+"_%s",i, MassPoints[j].c_str()), "", 138,0,138);

  }
}

  for(int u=0; u<sizeRegions; u++){
    //TString name_data       = data_2D[k]->GetName();
    //TString name_Top        = Top_2D[u]->GetName();
    TString name_ZtoNu      = ZtoNu_2D[u]->GetName();
    TString name_WtoL       = WtoL_2D[u]->GetName();
    TString name_MultiBoson = MultiBoson_2D[u]->GetName();
    //TString name_Multijet   = Multijet_2D[u]->GetName();
    //TString name_GJet       = GJet_2D[u]->GetName();
    TString name_TPow       = TPow_2D[u]->GetName();
    //TString name_DY         = DY_2D[u]->GetName();
    TString name_Higgs      = Higgs_2D[u]->GetName();

    //data_1D[u]        = new TH1D(Form(name_data+"_%d",u), "", 138,0,138);
    //Top_1D[u]         = new TH1D(Form("Bkg_Top_%d",u), "", 138,0,138);
    ZtoNu_1D[u]       = new TH1D(Form("Bkg_ZtoNu_%d",u), "", 138,0,138);
    WtoL_1D[u]        = new TH1D(Form("Bkg_WtoL_%d",u), "", 138,0,138);
    MultiBoson_1D[u]  = new TH1D(Form("Bkg_MultiBoson_%d",u), "", 138,0,138);
    //Multijet_1D[u]    = new TH1D(Form("Bkg_Multijet_%d",u), "", 138,0,138);
    //GJet_1D[u]        = new TH1D(Form("Bkg_GJet_%d",u), "", 138,0,138);
    TPow_1D[u]        = new TH1D(Form("Bkg_TPow_%d",u), "", 138,0,138);
    //DY_1D[u]          = new TH1D(Form("Bkg_DY_%d",u), "", 138,0,138);
    Higgs_1D[u]       = new TH1D(Form("Bkg_Higgs_%d",u), "", 138,0,138);

  }  

  for(int k=0;k<sizeRegions; k++){  
    for (int m = 0; m < sizeMassPoints; ++m){
    // 2D to 1D
    for(int i=1;i<=Sig_2D[0][0]->GetNbinsY();i++){       // Number of Systematic Var. on Y axis :    23
      for(int j=1;j<=Sig_2D[0][0]->GetNbinsX();j++){     // Number of MR*R2 Bins on X-axis      :     6


        Sig_1D[k][m]->SetBinContent(((i-1)*6)+j,Sig_2D[k][m]->GetBinContent(j,i));  
        Sig_1D[k][m]->SetBinError(((i-1)*6)+j,Sig_2D[k][m]->GetBinError(j,i));

        //data_1D[k]->SetBinContent(((i-1)*6)+j,data_2D[k]->GetBinContent(j,i));  
        //data_1D[k]->SetBinError(((i-1)*6)+j,data_2D[k]->GetBinError(j,i));

        //Top_1D[k]->SetBinContent(((i-1)*6)+j,Top_2D[k]->GetBinContent(j,i));  
        //Top_1D[k]->SetBinError(((i-1)*6)+j,Top_2D[k]->GetBinError(j,i));

        ZtoNu_1D[k]->SetBinContent(((i-1)*6)+j,ZtoNu_2D[k]->GetBinContent(j,i));  
        ZtoNu_1D[k]->SetBinError(((i-1)*6)+j,ZtoNu_2D[k]->GetBinError(j,i));

        WtoL_1D[k]->SetBinContent(((i-1)*6)+j,WtoL_2D[k]->GetBinContent(j,i));  
        WtoL_1D[k]->SetBinError(((i-1)*6)+j,WtoL_2D[k]->GetBinError(j,i));

        MultiBoson_1D[k]->SetBinContent(((i-1)*6)+j,MultiBoson_2D[k]->GetBinContent(j,i));  
        MultiBoson_1D[k]->SetBinError(((i-1)*6)+j,MultiBoson_2D[k]->GetBinError(j,i));

        //Multijet_1D[k]->SetBinContent(((i-1)*6)+j,Multijet_2D[k]->GetBinContent(j,i));  
        //Multijet_1D[k]->SetBinError(((i-1)*6)+j,Multijet_2D[k]->GetBinError(j,i));

        //GJet_1D[k]->SetBinContent(((i-1)*6)+j,GJet_2D[k]->GetBinContent(j,i));  
        //GJet_1D[k]->SetBinError(((i-1)*6)+j,GJet_2D[k]->GetBinError(j,i));

        TPow_1D[k]->SetBinContent(((i-1)*6)+j,TPow_2D[k]->GetBinContent(j,i));  
        TPow_1D[k]->SetBinError(((i-1)*6)+j,TPow_2D[k]->GetBinError(j,i));

        //DY_1D[k]->SetBinContent(((i-1)*6)+j,DY_2D[k]->GetBinContent(j,i));  
        //DY_1D[k]->SetBinError(((i-1)*6)+j,DY_2D[k]->GetBinError(j,i));

        Higgs_1D[k]->SetBinContent(((i-1)*6)+j,Higgs_2D[k]->GetBinContent(j,i));  
        Higgs_1D[k]->SetBinError(((i-1)*6)+j,Higgs_2D[k]->GetBinError(j,i));

      }
    }
    }
  }

// 1D plots unrolled for each signal region on the MR*R2 bins - 23 1D plots for each MC samples, 23*994 1D plots for the signal.

  //TH1F* hist_data[2*n_var+1];
  //TH1F* hist_Top[2*n_var+1];
  TH1F* hist_ZtoNu[2*n_var+1];
  TH1F* hist_WtoL[2*n_var+1];
  TH1F* hist_MultiBoson[2*n_var+1];
  //TH1F* hist_Multijet[2*n_var+1];
  //TH1F* hist_GJet[2*n_var+1];
  TH1F* hist_TPow[2*n_var+1];
  //TH1F* hist_DY[2*n_var+1];
  TH1F* hist_Higgs[2*n_var+1];
  TH1F* hist_Sig[2*n_var+1][sizeMassPoints];

for (int i=0; i<2*n_var+1; i++) { //23 number of systematic variations,

    //hist_data[i]        = new TH1F(Form("data_%d",i) , "", 174,0,174); 
    //hist_Top[i]         = new TH1F(Form("Top_%d",i) , "", 174,0,174);
    hist_ZtoNu[i]       = new TH1F(Form("ZtoNu_%d",i) , "", 174,0,174);
    hist_WtoL[i]        = new TH1F(Form("WtoL_%d",i) , "", 174,0,174);
    hist_MultiBoson[i]  = new TH1F(Form("MultiBoson_%d",i) , "", 174,0,174);
    //hist_Multijet[i]    = new TH1F(Form("Multijet_%d",i) , "", 174,0,174);
    //hist_GJet[i]        = new TH1F(Form("GJet_%d",i) , "", 174,0,174);
    hist_TPow[i]        = new TH1F(Form("TPow_%d",i) , "", 174,0,174);
    //hist_DY[i]          = new TH1F(Form("DY_%d",i) , "", 174,0,174);
    hist_Higgs[i]       = new TH1F(Form("Higgs_%d",i) , "", 174,0,174);
    for (int j=0; j<sizeMassPoints; j++) hist_Sig[i][j] = new TH1F(Form("T5ttcc%s_MassPoint%s",Systematic[i].c_str(),MassPoints[j].c_str()), "", 174,0,174);

}

for (int i = 1; i <=2*n_var+1 ; ++i){      // Loop over # of Systematics variations ( 23 )
  for (int j = 1; j <=sizeRegions; ++j){   // Loop over # of Signal Regions         ( 29 )
    for (int m = 0; m < sizeMassPoints; ++m){

      for (int k = 0; k < 6; ++k){          // Loop over # of MR*R2 bins             (  6 )
          
          //hist_data[i-1]->SetBinContent((((j-1)*6)+k),data_1D[j-1]->GetBinContent(((i-1)*6)+k));
          //hist_data[i-1]->SetBinError(((j-1)*6)+k,data_1D[j-1]->GetBinError(((i-1)*6)+k));

          //hist_Top[i-1]->SetBinContent((((j-1)*6)+k),Top_1D[j-1]->GetBinContent(((i-1)*6)+k));
          //hist_Top[i-1]->SetBinError(((j-1)*6)+k,Top_1D[j-1]->GetBinError(((i-1)*6)+k));

          hist_ZtoNu[i-1]->SetBinContent((((j-1)*6)+k),ZtoNu_1D[j-1]->GetBinContent(((i-1)*6)+k));
          hist_ZtoNu[i-1]->SetBinError(((j-1)*6)+k,ZtoNu_1D[j-1]->GetBinError(((i-1)*6)+k));

          hist_WtoL[i-1]->SetBinContent((((j-1)*6)+k),WtoL_1D[j-1]->GetBinContent(((i-1)*6)+k));
          hist_WtoL[i-1]->SetBinError(((j-1)*6)+k,WtoL_1D[j-1]->GetBinError(((i-1)*6)+k));

          hist_MultiBoson[i-1]->SetBinContent((((j-1)*6)+k),MultiBoson_1D[j-1]->GetBinContent(((i-1)*6)+k));
          hist_MultiBoson[i-1]->SetBinError(((j-1)*6)+k,MultiBoson_1D[j-1]->GetBinError(((i-1)*6)+k));

          //hist_Multijet[i-1]->SetBinContent((((j-1)*6)+k),Multijet_1D[j-1]->GetBinContent(((i-1)*6)+k));
          //hist_Multijet[i-1]->SetBinError(((j-1)*6)+k,Multijet_1D[j-1]->GetBinError(((i-1)*6)+k));

          //hist_GJet[i-1]->SetBinContent((((j-1)*6)+k),GJet_1D[j-1]->GetBinContent(((i-1)*6)+k));
          //hist_GJet[i-1]->SetBinError(((j-1)*6)+k,GJet_1D[j-1]->GetBinError(((i-1)*6)+k));

          hist_TPow[i-1]->SetBinContent((((j-1)*6)+k),TPow_1D[j-1]->GetBinContent(((i-1)*6)+k));
          hist_TPow[i-1]->SetBinError(((j-1)*6)+k,TPow_1D[j-1]->GetBinError(((i-1)*6)+k));

          //hist_DY[i-1]->SetBinContent((((j-1)*6)+k),DY_1D[j-1]->GetBinContent(((i-1)*6)+k));
          //hist_DY[i-1]->SetBinError(((j-1)*6)+k,DY_1D[j-1]->GetBinError(((i-1)*6)+k));

          hist_Higgs[i-1]->SetBinContent((((j-1)*6)+k),Higgs_1D[j-1]->GetBinContent(((i-1)*6)+k));
          hist_Higgs[i-1]->SetBinError(((j-1)*6)+k,Higgs_1D[j-1]->GetBinError(((i-1)*6)+k));

          hist_Sig[i-1][m]->SetBinContent((((j-1)*6)+k),Sig_1D[j-1][m]->GetBinContent(((i-1)*6)+k));
          hist_Sig[i-1][m]->SetBinError(((j-1)*6)+k,Sig_1D[j-1][m]->GetBinError(((i-1)*6)+k));

      }
    }  
  }
}

TFile* outFile = new TFile("DataCard_T5ttcc.root", "recreate"); // For only one simplified model: T5ttcc (can change).
TDirectory* d1 = outFile->mkdir("Multiboson");
TDirectory* d2 = outFile->mkdir("Higgs");
TDirectory* d3 = outFile->mkdir("ZToNuNu");
TDirectory* d4 = outFile->mkdir("WToLNu");
TDirectory* d5 = outFile->mkdir("TTPowheg");
TDirectory* d6 = outFile->mkdir("Signal");
   
  d1->cd();
  for (int i = 0; i <2*n_var+1; ++i) hist_MultiBoson[i]->Write();

  d2->cd();
  for (int i = 0; i <2*n_var+1; ++i) hist_Higgs[i]->Write();

  d3->cd();
  for (int i = 0; i <2*n_var+1; ++i) hist_ZtoNu[i]->Write();

  d4->cd();
  for (int i = 0; i <2*n_var+1; ++i) hist_WtoL[i]->Write();

  d5->cd();
  for (int i = 0; i <2*n_var+1; ++i) hist_TPow[i]->Write();

  d6->cd();
  for (int i = 0; i <2*n_var+1; ++i) {
    for (int j=0; j<sizeMassPoints; j++) hist_Sig[i][j]->Write();
  }

}

void MRR2_datacard(){
  UnrolledPlots("2016", "run_2021_10_22_syst.root");
  //UnrolledPlots("2017", "");
  //UnrolledPlots("2018", "");
}
