using namespace std;

void UnrolledPlots(){

  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  TH1::SetDefaultSumw2();

  TString dir = " /Users/ufuktok/Downloads/Datacard/run_Haziran_11/"; 


  TFile* file1 = TFile::Open(dir+"Multijet.root");
  TFile* file2 = TFile::Open(dir+"Top.root");
  TFile* file3 = TFile::Open(dir+"WJet.root");
  TFile* file4 = TFile::Open(dir+"ZJet.root");
  TFile* file5 = TFile::Open(dir+"Multiboson.root");
  TFile* file6 = TFile::Open(dir+"T5ttcc.root");
  TFile* file7 = TFile::Open(dir+"T2bW.root");
  TFile* file8 = TFile::Open(dir+"T2bt.root");

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

TH2D* htemp[8];
TH1D* histo_1D[12][8];

histo_1D[0][0] = new TH1D("First", ";Bin;Counts", 3000, 0, 3000);   // 8

  for(int i=0;i<12;i++) {

    for (int j=0;j<8;j++) histo_1D[i][j]=(TH1D*)histo_1D[0][0]->Clone();
  }

  double error_1, error_2, error_3, error_4, error_5, error_6, error_7, error_8;

  for (int i=8; i<20;i++){         //  Hadronic SR
 
    htemp[0] = (TH2D*)file1->Get(Form("Background/MRR2_bkg_%s", SigRegion[i].c_str()));   // Multijet
    htemp[1] = (TH2D*)file2->Get(Form("Background/MRR2_bkg_%s", SigRegion[i].c_str()));   // Top
    htemp[2] = (TH2D*)file3->Get(Form("Background/MRR2_bkg_%s", SigRegion[i].c_str()));   // WJet
    htemp[3] = (TH2D*)file4->Get(Form("Background/MRR2_bkg_%s", SigRegion[i].c_str()));   // ZJet
    htemp[4] = (TH2D*)file5->Get(Form("Background/MRR2_bkg_%s", SigRegion[i].c_str()));   // Multiboson    
    htemp[5] = (TH2D*)file6->Get(Form("Signal/MRR2_S_signal_%s__1500_400", SigRegion[i].c_str())); // Signal_1
    htemp[6] = (TH2D*)file7->Get(Form("Signal/MRR2_S_signal_%s__700_200", SigRegion[i].c_str()));  // Signal_2
    htemp[7] = (TH2D*)file8->Get(Form("Signal/MRR2_S_signal_%s__700_200", SigRegion[i].c_str()));  // Signal_3

    cout<<" # of Bins MR*R2  " <<htemp[0]->GetNbinsX()<<endl;

    for (int x = 1; x <=htemp[0]->GetNbinsX() ; ++x)
    {
      error_1 = 0;
      error_2 = 0;
      error_3 = 0;
      error_4 = 0;
      error_5 = 0;
      error_6 = 0;
      error_7 = 0;
      error_8 = 0;

      histo_1D[i-8][0]->SetBinContent(x, htemp[0]->GetBinContent(x,1)); //Multijet
      histo_1D[i-8][1]->SetBinContent(x, htemp[1]->GetBinContent(x,1)); //Top
      histo_1D[i-8][2]->SetBinContent(x, htemp[2]->GetBinContent(x,1)); //WJet
      histo_1D[i-8][3]->SetBinContent(x, htemp[3]->GetBinContent(x,1)); //ZJet
      histo_1D[i-8][4]->SetBinContent(x, htemp[4]->GetBinContent(x,1)); //Multiboson
      histo_1D[i-8][5]->SetBinContent(x, htemp[5]->GetBinContent(x,1)); //T5ttcc
      histo_1D[i-8][6]->SetBinContent(x, htemp[6]->GetBinContent(x,1)); //T2bW
      histo_1D[i-8][7]->SetBinContent(x, htemp[7]->GetBinContent(x,1)); //T2bt

      error_1 += (htemp[0]->GetBinError(x,1)*htemp[0]->GetBinError(x,1));
      error_2 += (htemp[1]->GetBinError(x,1)*htemp[1]->GetBinError(x,1));
      error_3 += (htemp[2]->GetBinError(x,1)*htemp[2]->GetBinError(x,1));
      error_4 += (htemp[3]->GetBinError(x,1)*htemp[3]->GetBinError(x,1));
      error_5 += (htemp[4]->GetBinError(x,1)*htemp[4]->GetBinError(x,1));
      error_6 += (htemp[5]->GetBinError(x,1)*htemp[5]->GetBinError(x,1));
      error_7 += (htemp[6]->GetBinError(x,1)*htemp[6]->GetBinError(x,1));
      error_8 += (htemp[7]->GetBinError(x,1)*htemp[7]->GetBinError(x,1));

      for(int y=2;y<=81;y++) {                                                            

        if(htemp[0]->GetBinContent(x,1)-htemp[0]->GetBinContent(x,y) > 0) error_1 += (htemp[0]->GetBinContent(x,1)-htemp[0]->GetBinContent(x,y))*(htemp[0]->GetBinContent(x,1)-htemp[0]->GetBinContent(x,y));
        if(htemp[1]->GetBinContent(x,1)-htemp[1]->GetBinContent(x,y) > 0) error_2 += (htemp[1]->GetBinContent(x,1)-htemp[1]->GetBinContent(x,y))*(htemp[1]->GetBinContent(x,1)-htemp[1]->GetBinContent(x,y));
        if(htemp[2]->GetBinContent(x,1)-htemp[2]->GetBinContent(x,y) > 0) error_3 += (htemp[2]->GetBinContent(x,1)-htemp[2]->GetBinContent(x,y))*(htemp[2]->GetBinContent(x,1)-htemp[2]->GetBinContent(x,y));
        if(htemp[3]->GetBinContent(x,1)-htemp[3]->GetBinContent(x,y) > 0) error_4 += (htemp[3]->GetBinContent(x,1)-htemp[3]->GetBinContent(x,y))*(htemp[3]->GetBinContent(x,1)-htemp[3]->GetBinContent(x,y));
        if(htemp[4]->GetBinContent(x,1)-htemp[4]->GetBinContent(x,y) > 0) error_5 += (htemp[4]->GetBinContent(x,1)-htemp[4]->GetBinContent(x,y))*(htemp[4]->GetBinContent(x,1)-htemp[4]->GetBinContent(x,y));
        if(htemp[5]->GetBinContent(x,1)-htemp[5]->GetBinContent(x,y) > 0) error_6 += (htemp[5]->GetBinContent(x,1)-htemp[5]->GetBinContent(x,y))*(htemp[5]->GetBinContent(x,1)-htemp[5]->GetBinContent(x,y));
        if(htemp[6]->GetBinContent(x,1)-htemp[6]->GetBinContent(x,y) > 0) error_7 += (htemp[6]->GetBinContent(x,1)-htemp[6]->GetBinContent(x,y))*(htemp[6]->GetBinContent(x,1)-htemp[6]->GetBinContent(x,y));
        if(htemp[7]->GetBinContent(x,1)-htemp[7]->GetBinContent(x,y) > 0) error_8 += (htemp[7]->GetBinContent(x,1)-htemp[7]->GetBinContent(x,y))*(htemp[7]->GetBinContent(x,1)-htemp[7]->GetBinContent(x,y));  
      }

      histo_1D[i-8][0]->SetBinError(x, sqrt(error_1));
      histo_1D[i-8][1]->SetBinError(x, sqrt(error_2));
      histo_1D[i-8][2]->SetBinError(x, sqrt(error_3));
      histo_1D[i-8][3]->SetBinError(x, sqrt(error_4));
      histo_1D[i-8][4]->SetBinError(x, sqrt(error_5));
      histo_1D[i-8][5]->SetBinError(x, sqrt(error_6));
      histo_1D[i-8][6]->SetBinError(x, sqrt(error_7));
      histo_1D[i-8][7]->SetBinError(x, sqrt(error_8));

      //cout<<" error_1  " << error_4 << endl;

    }  
  }


// ####################### Bin Edges as a Variable - The goal is to maximize the signal-background ratio on each bins. 
// ####################### Find the optimized bin width for each SR.
// ####################### X1 - X2 : First bin width, 
// ####################### X2 - X3 : Second bin width, 
// #######################    .  
// #######################    .  
// #######################    .  
// ####################### X7 - X8 : Last bin width. 8 bins in total for each SR (could be chanced).

//Errors of the bins
Double_t ERR_[8][8][12]; // Err(i,j,k) --> i: Bin Counts, j: Process (Multijet, Top, etc.), k: SRs

//Integral of the bins
Double_t INT_[8][8][12]; // INT(i,j,k) --> i: Bin Counts, j: Process (Multijet, Top, etc.), k: SRs

int SR_1[9]  = {0, 200, 250, 350, 450, 500, 600, 800, 3000}; // SR_Had_H_b_45j
int SR_2[9]  = {0, 200, 300, 350, 400, 500, 600, 800, 3000}; // SR_Had_H_b_6j
int SR_3[9]  = {0, 200, 250, 300, 350, 400, 450, 600, 3000};  // SR_Had_2H_b_6j
int SR_4[9]  = {0, 200, 250, 350, 400, 450, 500, 600, 3000};  // SR_Had_HV_b_6j
int SR_5[9]  = {0, 200, 300, 350, 450, 650, 850, 1000, 3000}; // SR_Had_1H_0b_34j
int SR_6[9]  = {0, 200, 300, 350, 400, 500, 600, 800, 3000}; // SR_Had_1H_0b_5j
int SR_7[9]  = {0, 250, 300, 350, 400, 450, 800, 1000, 3000}; // SR_Had_2H_0b_34j
int SR_8[9]  = {0, 250, 300, 350, 400, 450, 800, 1000, 3000}; // SR_Had_2H_0b_5j
int SR_9[9]  = {0, 200, 250, 300, 350, 400, 800, 1500, 3000}; // SR_Had_HV_0b_24j
int SR_10[9] = {0, 200, 250, 300, 350, 450, 800, 1000, 3000}; // SR_Had_HV_0b_5j
int SR_11[9] = {0, 250, 300, 350, 400, 450, 500, 800, 3000}; // SR_Lep_H_b
int SR_12[9] = {0, 200, 250, 300, 350, 400, 500, 600, 3000}; // SR_Lep_H_0b

TH1D* hist_bins[12][8];  //// OPTIMIZATION STEP (96 1D plots with selected bin edges and bin numbers.)

hist_bins[0][0] = new TH1D("First", ";Bin;Counts", 8, 0, 8);   // 8 
  
  for(int i=0;i<12;i++) {

    for (int j=0;j<8;j++) hist_bins[i][j]=(TH1D*)hist_bins[0][0]->Clone();
  }

for (int j = 0; j < 8; ++j){

  for (int i = 0; i < 8; ++i){
    
    INT_[i][j][0] = histo_1D[0][j]->IntegralAndError(SR_1[i], SR_1[i+1], ERR_[i][j][0]);
    INT_[i][j][1] = histo_1D[1][j]->IntegralAndError(SR_2[i], SR_2[i+1], ERR_[i][j][1]);
    INT_[i][j][2] = histo_1D[2][j]->IntegralAndError(SR_3[i], SR_3[i+1], ERR_[i][j][2]);
    INT_[i][j][3] = histo_1D[3][j]->IntegralAndError(SR_4[i], SR_4[i+1], ERR_[i][j][3]);
    INT_[i][j][4] = histo_1D[4][j]->IntegralAndError(SR_5[i], SR_5[i+1], ERR_[i][j][4]);
    INT_[i][j][5] = histo_1D[5][j]->IntegralAndError(SR_6[i], SR_6[i+1], ERR_[i][j][5]);
    INT_[i][j][6] = histo_1D[6][j]->IntegralAndError(SR_7[i], SR_7[i+1], ERR_[i][j][6]);
    INT_[i][j][7] = histo_1D[7][j]->IntegralAndError(SR_8[i], SR_8[i+1], ERR_[i][j][7]);
    INT_[i][j][8] = histo_1D[8][j]->IntegralAndError(SR_9[i], SR_9[i+1], ERR_[i][j][8]);
    INT_[i][j][9] = histo_1D[9][j]->IntegralAndError(SR_10[i], SR_10[i+1], ERR_[i][j][9]);
    INT_[i][j][10] = histo_1D[10][j]->IntegralAndError(SR_11[i], SR_11[i+1], ERR_[i][j][10]);
    INT_[i][j][11] = histo_1D[11][j]->IntegralAndError(SR_12[i], SR_12[i+1], ERR_[i][j][11]);

    hist_bins[0][j]->SetBinContent(i+1,INT_[i][j][0]);
    hist_bins[1][j]->SetBinContent(i+1,INT_[i][j][1]);
    hist_bins[2][j]->SetBinContent(i+1,INT_[i][j][2]);
    hist_bins[3][j]->SetBinContent(i+1,INT_[i][j][3]);
    hist_bins[4][j]->SetBinContent(i+1,INT_[i][j][4]);
    hist_bins[5][j]->SetBinContent(i+1,INT_[i][j][5]);
    hist_bins[6][j]->SetBinContent(i+1,INT_[i][j][6]);
    hist_bins[7][j]->SetBinContent(i+1,INT_[i][j][7]);
    hist_bins[8][j]->SetBinContent(i+1,INT_[i][j][8]);
    hist_bins[9][j]->SetBinContent(i+1,INT_[i][j][9]);
    hist_bins[10][j]->SetBinContent(i+1,INT_[i][j][10]);
    hist_bins[11][j]->SetBinContent(i+1,INT_[i][j][11]);

    hist_bins[0][j]->SetBinError(i+1,ERR_[i][j][0]);
    hist_bins[1][j]->SetBinError(i+1,ERR_[i][j][1]);
    hist_bins[2][j]->SetBinError(i+1,ERR_[i][j][2]);
    hist_bins[3][j]->SetBinError(i+1,ERR_[i][j][3]);
    hist_bins[4][j]->SetBinError(i+1,ERR_[i][j][4]);
    hist_bins[5][j]->SetBinError(i+1,ERR_[i][j][5]);
    hist_bins[6][j]->SetBinError(i+1,ERR_[i][j][6]);
    hist_bins[7][j]->SetBinError(i+1,ERR_[i][j][7]);
    hist_bins[8][j]->SetBinError(i+1,ERR_[i][j][8]);
    hist_bins[9][j]->SetBinError(i+1,ERR_[i][j][9]);
    hist_bins[10][j]->SetBinError(i+1,ERR_[i][j][10]);
    hist_bins[11][j]->SetBinError(i+1,ERR_[i][j][11]);

  }
}

TH1D* histo_1[8];

histo_1[0] = new TH1D("First", ";Bin;Counts", 96, 0, 96);   // 8
  
  for(int k=0;k<8;k++) {
    histo_1[k]=(TH1D*)histo_1[0]->Clone();
  }

for (int i = 0; i<12; ++i){
  for (int j = 1; j<=8; ++j){
    histo_1[0]->SetBinContent(i*8+j, hist_bins[i][0]->GetBinContent(j));    
    histo_1[1]->SetBinContent(i*8+j, hist_bins[i][1]->GetBinContent(j));
    histo_1[2]->SetBinContent(i*8+j, hist_bins[i][2]->GetBinContent(j));
    histo_1[3]->SetBinContent(i*8+j, hist_bins[i][3]->GetBinContent(j));
    histo_1[4]->SetBinContent(i*8+j, hist_bins[i][4]->GetBinContent(j));
    histo_1[5]->SetBinContent(i*8+j, hist_bins[i][5]->GetBinContent(j));
    histo_1[6]->SetBinContent(i*8+j, hist_bins[i][6]->GetBinContent(j));
    histo_1[7]->SetBinContent(i*8+j, hist_bins[i][7]->GetBinContent(j));

    histo_1[0]->SetBinError(i*8+j, hist_bins[i][0]->GetBinError(j));    
    histo_1[1]->SetBinError(i*8+j, hist_bins[i][1]->GetBinError(j));
    histo_1[2]->SetBinError(i*8+j, hist_bins[i][2]->GetBinError(j));
    histo_1[3]->SetBinError(i*8+j, hist_bins[i][3]->GetBinError(j));
    histo_1[4]->SetBinError(i*8+j, hist_bins[i][4]->GetBinError(j));
    histo_1[5]->SetBinError(i*8+j, hist_bins[i][5]->GetBinError(j));
    histo_1[6]->SetBinError(i*8+j, hist_bins[i][6]->GetBinError(j));
    histo_1[7]->SetBinError(i*8+j, hist_bins[i][7]->GetBinError(j));
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

string MRR2Bins_1[96] = {"0-200", "200-250", "250-350", "350-450", "450-500", "500-600", "600-800", "800-3000",   // SR_Had_H_b_45j
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

  TLine* lines_1[11];
  TLatex* SR_names_Higgs[11];

  for (int i = 8; i < 20; ++i){
      lines_1[i] = new TLine(((i-8)*8)+8,0,((i-8)*8)+8,1e4);
      lines_1[i]->SetLineStyle(2);
      lines_1[i]->Draw("SAME");

      SR_names_Higgs[i] = new TLatex(((i-8)*8)+4, 1e3, SigRegion[i].c_str());
      SR_names_Higgs[i]->SetTextAlign(11);
      SR_names_Higgs[i]->SetTextAngle(90);
      SR_names_Higgs[i]->SetTextSize(0.015);
      SR_names_Higgs[i]->SetTextFont(14);
      SR_names_Higgs[i]->SetLineWidth(1);
      SR_names_Higgs[i]->Draw("SAME");
  }

  histo_1[5]->Draw("sameHIST");
  histo_1[6]->Draw("sameHIST");
  histo_1[7]->Draw("sameHIST");

  total_1->Draw("SAME E2");

  //hs1_1->GetXaxis()->SetTitle("Bin Number");
  for(int i=1; i<=96; i++) hs1_1->GetXaxis()->SetBinLabel(i, MRR2Bins_1[i-1].c_str());
  hs1_1->GetXaxis()->SetLabelSize(0.03);
  hs1_1->GetYaxis()->SetTitle("Counts");

  string text = "CMS #scale[0.7]{#font[52]{Work in progress Run2}}";
  TLatex* cms_lat = new TLatex(1, 3e5, text.c_str());
  cms_lat->SetLineWidth(2);
  cms_lat->Draw();

  string text_1 = "#scale[0.7]{#font[52]{137 fb^{-1} (13 TeV)}}";
  TLatex* era_lat = new TLatex(96*0.95,3e5, text_1.c_str());
  era_lat->SetTextAlign(36);
  era_lat->SetLineWidth(2);
  era_lat->Draw();

  string NM1 = "#scale[0.7]{#font[52]{Higgs channels }}";
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

  c1->SaveAs("MRR2_Higgsic_OptedBins.png"); 
  c1->Close();

}

void BinOptimizationStudy_Higgs(){
  UnrolledPlots();
}
