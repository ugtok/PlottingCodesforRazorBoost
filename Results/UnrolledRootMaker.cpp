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
  TFile* file5 = TFile::Open(dir+"other.root");
  TFile* file6 = TFile::Open(dir+"TotMC.root");
  TFile* file7 = TFile::Open(dir+"T2bW.root");
  TFile* file8 = TFile::Open(dir+"T5ttcc.root");

  string Systematic[] = {    "",
                        "_topptUp", 
                        "_topptDown", 
                        "_isrUp", 
                        "_isrDown", 
                        "_pileupUp", 
                        "_pileupDown", 
                        "_L1PreFiringUp", 
                        "_L1PreFiringDown", 
                        "_alphasUp", 
                        "_alphasDown", 
                        "_scaleUp", 
                        "_scaleDown", 
                        "_lostlepUp", 
                        "_lostlepDown", 
                        "_triggerUp", 
                        "_triggerDown", 
                        "_jesUp", 
                        "_jesDown", 
                        "_jerUp", 
                        "_jerDown", 
                        "_metUp", 
                        "_metDown",
                        "_RescaleAK8Up",
                        "_RescaleAK8Down",
                        "_BoostTagUp",
                        "_BoostTagDown",
                        "_BoostTag_FastsimUp",
                        "_BoostTag_FastsimDown",
                        "_BoostmisTagUp",
                        "_BoostmisTagDown",
                        "_BoostmisTag_FastsimUp",
                        "_BoostmisTag_FastsimDown",
                        "_massTagUp",
                        "_massTagDown",
                        "_EleRecoUp",
                        "_EleRecoDown",
                        "_EleIDUp",
                        "_EleIDDown",
                        "_EleIsoUp",
                        "_EleIsoDown",
                        "_EleFastsimUp",
                        "_EleFastsimDown",
                        "_MuonTrackUp",
                        "_MuonTrackDown",
                        "_MuonFullsimUp",
                        "_MuonFullsimDown",
                        "_MuonFastsimUp",
                        "_MuonFastsimDown",
                        "_BTagUp",
                        "_BTagDown",
                        "_BTagFastsimUp",
                        "_BTagFastsimDown",
                        "_cf_QUp",
                        "_cf_QDown",
                        "_cf_TUp",
                        "_cf_TDown",
                        "_cf_WUp",
                        "_cf_WDown",
                        "_cf_ZUp",
                        "_cf_ZDown",
                        "_cf_LUp",
                        "_cf_LDown",
                        "_cf_njet_QUp",
                        "_cf_njet_QDown",
                        "_cf_njet_TUp",
                        "_cf_njet_TDown",
                        "_cf_njet_WUp",
                        "_cf_njet_WDown",
                        "_cf_njet_ZGUp",
                        "_cf_njet_ZGDown",
                        "_cf_njet_ZLUp",
                        "_cf_njet_ZLDown",
                        "_cf_NonIso_TUp",
                        "_cf_NonIso_TDown",
                        "_cf_NonIso_WUp",
                        "_cf_NonIso_WDown",
                        "_cf_NonIso_njet_TUp",
                        "_cf_NonIso_njet_TDown",
                        "_cf_NonIso_njet_WUp",
                        "_cf_NonIso_njet_WDown"
                                                };

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

TH2D* htemp[29][8];
TH1D* histo_1D[29][81][8];

histo_1D[0][0][0] = new TH1D("First", ";Bin;Counts", 3000, 0, 3000);   // 8

for(int i=0;i<29;i++) {
  for (int j=0;j<81;j++){ 
     for (int k=0;k<8;k++) histo_1D[i][j][k]=(TH1D*)histo_1D[0][0][0]->Clone();
  }
}


  for (int i=0; i<29;i++){         //  Hadronic SR
 
    htemp[i][0] = (TH2D*)file1->Get(Form("Background/MRR2_bkg_%s", SigRegion[i].c_str()));             // Multijet
    htemp[i][1] = (TH2D*)file2->Get(Form("Background/MRR2_bkg_%s", SigRegion[i].c_str()));             // Top
    htemp[i][2] = (TH2D*)file3->Get(Form("Background/MRR2_bkg_%s", SigRegion[i].c_str()));             // WJet
    htemp[i][3] = (TH2D*)file4->Get(Form("Background/MRR2_bkg_%s", SigRegion[i].c_str()));             // ZJet
    htemp[i][4] = (TH2D*)file5->Get(Form("Background/MRR2_bkg_%s", SigRegion[i].c_str()));             // other BG   
    htemp[i][5] = (TH2D*)file6->Get(Form("Background/MRR2_bkg_%s", SigRegion[i].c_str()));              // TotMC
    htemp[i][6] = (TH2D*)file7->Get(Form("Signal/MRR2_S_signal_%s__700_200", SigRegion[i].c_str()));   // T2bW
    htemp[i][7] = (TH2D*)file8->Get(Form("Signal/MRR2_S_signal_%s__1500_400", SigRegion[i].c_str()));   // T5ttcc

    cout<<" # of Bins MR*R2  " <<htemp[0][0]->GetNbinsX()<<endl;

    for (int y=0; y<81; y++) {

      for (int x = 1; x <=htemp[0][0]->GetNbinsX() ; ++x){

        histo_1D[i][y][0]->SetBinContent(x, htemp[i][0]->GetBinContent(x,y+1)); //Multijet
        histo_1D[i][y][1]->SetBinContent(x, htemp[i][1]->GetBinContent(x,y+1)); //Top
        histo_1D[i][y][2]->SetBinContent(x, htemp[i][2]->GetBinContent(x,y+1)); //WJet
        histo_1D[i][y][3]->SetBinContent(x, htemp[i][3]->GetBinContent(x,y+1)); //ZJet
        histo_1D[i][y][4]->SetBinContent(x, htemp[i][4]->GetBinContent(x,y+1)); //other BG
        histo_1D[i][y][5]->SetBinContent(x, htemp[i][5]->GetBinContent(x,y+1)); //TotMC
        histo_1D[i][y][6]->SetBinContent(x, htemp[i][6]->GetBinContent(x,y+1)); //T2bW
        histo_1D[i][y][7]->SetBinContent(x, htemp[i][7]->GetBinContent(x,y+1)); //T5ttcc


        histo_1D[i][y][0]->SetBinError(x, htemp[i][0]->GetBinError(x,y+1));
        histo_1D[i][y][1]->SetBinError(x, htemp[i][1]->GetBinError(x,y+1));
        histo_1D[i][y][2]->SetBinError(x, htemp[i][2]->GetBinError(x,y+1));
        histo_1D[i][y][3]->SetBinError(x, htemp[i][3]->GetBinError(x,y+1));
        histo_1D[i][y][4]->SetBinError(x, htemp[i][4]->GetBinError(x,y+1));
        histo_1D[i][y][5]->SetBinError(x, htemp[i][5]->GetBinError(x,y+1));
        histo_1D[i][y][6]->SetBinError(x, htemp[i][6]->GetBinError(x,y+1));
        histo_1D[i][y][7]->SetBinError(x, htemp[i][7]->GetBinError(x,y+1));

      }  
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
Double_t ERR_[8][8][29][81]; // Err(i,j,k,u) --> i: Bin Counts, j: Process (Multijet, Top, etc.), k: SRs, u: Systematics

//Integral of the bins
Double_t INT_[8][8][29][81]; // Int(i,j,k,u) --> i: Bin Counts, j: Process (Multijet, Top, etc.), k: SRs, u: Systematics

int SR_1[9] = {0, 200, 300, 400, 500, 750, 850, 1000, 3000}; // SR_Had_1htop
int SR_2[9] = {0, 200, 300, 400, 500, 600, 800, 1000, 3000}; // SR_Had_2htop
int SR_3[9] = {0, 200, 300, 350, 400, 500, 600, 800, 3000};  // SR_Had_V_b_45j
int SR_4[9] = {0, 200, 300, 350, 400, 500, 600, 800, 3000};  // SR_Had_V_b_6j
int SR_5[9] = {0, 200, 250, 300, 400, 500, 600, 1000, 3000}; // SR_Had_1V_0b_34j
int SR_6[9] = {0, 200, 250, 300, 400, 500, 600, 1000, 3000}; // SR_Had_1V_0b_5j
int SR_7[9] = {0, 200, 250, 300, 350, 500, 800, 1000, 3000}; // SR_Had_2V_0b_24j
int SR_8[9] = {0, 200, 250, 300, 350, 450, 800, 1000, 3000}; // SR_Had_2V_0b_5j

int SR_9[9]  = {0, 200, 250, 350, 450, 500, 600, 800, 3000}; // SR_Had_H_b_45j
int SR_10[9] = {0, 200, 300, 350, 400, 500, 600, 800, 3000}; // SR_Had_H_b_6j
int SR_11[9] = {0, 200, 250, 300, 350, 400, 450, 600, 3000};  // SR_Had_2H_b_6j
int SR_12[9] = {0, 200, 250, 350, 400, 450, 500, 600, 3000};  // SR_Had_HV_b_6j
int SR_13[9] = {0, 200, 300, 350, 450, 650, 850, 1000, 3000}; // SR_Had_1H_0b_34j
int SR_14[9] = {0, 200, 300, 350, 400, 500, 600, 800, 3000}; // SR_Had_1H_0b_5j
int SR_15[9] = {0, 250, 300, 350, 400, 450, 800, 1000, 3000}; // SR_Had_2H_0b_34j
int SR_16[9] = {0, 250, 300, 350, 400, 450, 800, 1000, 3000}; // SR_Had_2H_0b_5j
int SR_17[9] = {0, 200, 250, 300, 350, 400, 800, 1500, 3000}; // SR_Had_HV_0b_24j
int SR_18[9] = {0, 200, 250, 300, 350, 450, 800, 1000, 3000}; // SR_Had_HV_0b_5j
int SR_19[9] = {0, 250, 300, 350, 400, 450, 500, 800, 3000}; // SR_Lep_H_b
int SR_20[9] = {0, 200, 250, 300, 350, 400, 500, 600, 3000}; // SR_Lep_H_0b

int SR_21[9]  = {0, 200, 300, 400, 500, 600, 800, 1000, 3000};  // SR_Lep_1htop
int SR_22[9]  = {0, 200, 300, 350, 400, 500, 600, 1500, 3000};  // SR_Lep_V_b
int SR_23[9]  = {0, 200, 300, 350, 400, 500, 600, 700, 3000};  // SR_Lep_V_0b
int SR_24[9]  = {0, 200, 300, 400, 500, 600, 800, 1000, 3000};  // SR_Leptop_0htop
int SR_25[9]  = {0, 300, 500, 600, 700, 750, 800, 1000, 3000}; // SR_Leptop_1htop
int SR_26[9]  = {0, 200, 300, 400, 500, 600, 700, 1000, 3000};  // SR_Lepjet_0V_24j
int SR_27[9]  = {0, 200, 300, 400, 500, 600, 800, 1000, 3000}; // SR_Lepjet_0V_5j
int SR_28[9]  = {0, 200, 250, 400, 450, 600, 1000, 1500, 3000}; // SR_Lepjet_1V_24j
int SR_29[9]  = {0, 200, 250, 300, 350, 400, 600, 1000, 3000}; // SR_Lepjet_1V_5j

TH1D* hist_bins[29][81][8];  //// OPTIMIZATION STEP

hist_bins[0][0][0] = new TH1D("First", ";Bin;Counts", 8, 0, 8);   // 8 
  
  for(int i=0;i<29;i++) {

    for (int j=0;j<8;j++) {
      
      for (int u=0;u<81;u++) hist_bins[i][u][j]=(TH1D*)hist_bins[0][0][0]->Clone();
    }
  }

for (int u = 0; u < 81; ++u){


  for (int j = 0; j < 8; ++j){

    for (int i = 0; i < 8; ++i){
    
      INT_[i][j][0][u] = histo_1D[0][u][j]->IntegralAndError(SR_1[i], SR_1[i+1], ERR_[i][j][0][u]);
      INT_[i][j][1][u] = histo_1D[1][u][j]->IntegralAndError(SR_2[i], SR_2[i+1], ERR_[i][j][1][u]);
      INT_[i][j][2][u] = histo_1D[2][u][j]->IntegralAndError(SR_3[i], SR_3[i+1], ERR_[i][j][2][u]);
      INT_[i][j][3][u] = histo_1D[3][u][j]->IntegralAndError(SR_4[i], SR_4[i+1], ERR_[i][j][3][u]);
      INT_[i][j][4][u] = histo_1D[4][u][j]->IntegralAndError(SR_5[i], SR_5[i+1], ERR_[i][j][4][u]);
      INT_[i][j][5][u] = histo_1D[5][u][j]->IntegralAndError(SR_6[i], SR_6[i+1], ERR_[i][j][5][u]);
      INT_[i][j][6][u] = histo_1D[6][u][j]->IntegralAndError(SR_7[i], SR_7[i+1], ERR_[i][j][6][u]);
      INT_[i][j][7][u] = histo_1D[7][u][j]->IntegralAndError(SR_8[i], SR_8[i+1], ERR_[i][j][7][u]);
      INT_[i][j][8][u] = histo_1D[8][u][j]->IntegralAndError(SR_9[i], SR_9[i+1], ERR_[i][j][8][u]);
      INT_[i][j][9][u] = histo_1D[9][u][j]->IntegralAndError(SR_10[i], SR_10[i+1], ERR_[i][j][9][u]);
      INT_[i][j][10][u] = histo_1D[10][u][j]->IntegralAndError(SR_11[i], SR_11[i+1], ERR_[i][j][10][u]);
      INT_[i][j][11][u] = histo_1D[11][u][j]->IntegralAndError(SR_12[i], SR_12[i+1], ERR_[i][j][11][u]);
      INT_[i][j][12][u] = histo_1D[12][u][j]->IntegralAndError(SR_13[i], SR_13[i+1], ERR_[i][j][12][u]);
      INT_[i][j][13][u] = histo_1D[13][u][j]->IntegralAndError(SR_14[i], SR_14[i+1], ERR_[i][j][13][u]);
      INT_[i][j][14][u] = histo_1D[14][u][j]->IntegralAndError(SR_15[i], SR_15[i+1], ERR_[i][j][14][u]);
      INT_[i][j][15][u] = histo_1D[15][u][j]->IntegralAndError(SR_16[i], SR_16[i+1], ERR_[i][j][15][u]);
      INT_[i][j][16][u] = histo_1D[16][u][j]->IntegralAndError(SR_17[i], SR_17[i+1], ERR_[i][j][16][u]);
      INT_[i][j][17][u] = histo_1D[17][u][j]->IntegralAndError(SR_18[i], SR_18[i+1], ERR_[i][j][17][u]);
      INT_[i][j][18][u] = histo_1D[18][u][j]->IntegralAndError(SR_19[i], SR_19[i+1], ERR_[i][j][18][u]);
      INT_[i][j][19][u] = histo_1D[19][u][j]->IntegralAndError(SR_20[i], SR_20[i+1], ERR_[i][j][19][u]);
      INT_[i][j][20][u] = histo_1D[20][u][j]->IntegralAndError(SR_21[i], SR_21[i+1], ERR_[i][j][20][u]);
      INT_[i][j][21][u] = histo_1D[21][u][j]->IntegralAndError(SR_22[i], SR_22[i+1], ERR_[i][j][21][u]);
      INT_[i][j][22][u] = histo_1D[22][u][j]->IntegralAndError(SR_23[i], SR_23[i+1], ERR_[i][j][22][u]);
      INT_[i][j][23][u] = histo_1D[23][u][j]->IntegralAndError(SR_24[i], SR_24[i+1], ERR_[i][j][23][u]);
      INT_[i][j][24][u] = histo_1D[24][u][j]->IntegralAndError(SR_25[i], SR_25[i+1], ERR_[i][j][24][u]);
      INT_[i][j][25][u] = histo_1D[25][u][j]->IntegralAndError(SR_26[i], SR_26[i+1], ERR_[i][j][25][u]);
      INT_[i][j][26][u] = histo_1D[26][u][j]->IntegralAndError(SR_27[i], SR_27[i+1], ERR_[i][j][26][u]);
      INT_[i][j][27][u] = histo_1D[27][u][j]->IntegralAndError(SR_28[i], SR_28[i+1], ERR_[i][j][27][u]);
      INT_[i][j][28][u] = histo_1D[28][u][j]->IntegralAndError(SR_29[i], SR_29[i+1], ERR_[i][j][28][u]);


      hist_bins[0][u][j]->SetBinContent(i+1,INT_[i][j][0][u]);
      hist_bins[1][u][j]->SetBinContent(i+1,INT_[i][j][1][u]);
      hist_bins[2][u][j]->SetBinContent(i+1,INT_[i][j][2][u]);
      hist_bins[3][u][j]->SetBinContent(i+1,INT_[i][j][3][u]);
      hist_bins[4][u][j]->SetBinContent(i+1,INT_[i][j][4][u]);
      hist_bins[5][u][j]->SetBinContent(i+1,INT_[i][j][5][u]);
      hist_bins[6][u][j]->SetBinContent(i+1,INT_[i][j][6][u]);
      hist_bins[7][u][j]->SetBinContent(i+1,INT_[i][j][7][u]);
      hist_bins[8][u][j]->SetBinContent(i+1,INT_[i][j][8][u]);
      hist_bins[9][u][j]->SetBinContent(i+1,INT_[i][j][9][u]);
      hist_bins[10][u][j]->SetBinContent(i+1,INT_[i][j][10][u]);
      hist_bins[11][u][j]->SetBinContent(i+1,INT_[i][j][11][u]);
      hist_bins[12][u][j]->SetBinContent(i+1,INT_[i][j][12][u]);
      hist_bins[13][u][j]->SetBinContent(i+1,INT_[i][j][13][u]);
      hist_bins[14][u][j]->SetBinContent(i+1,INT_[i][j][14][u]);
      hist_bins[15][u][j]->SetBinContent(i+1,INT_[i][j][15][u]);
      hist_bins[16][u][j]->SetBinContent(i+1,INT_[i][j][16][u]);
      hist_bins[17][u][j]->SetBinContent(i+1,INT_[i][j][17][u]);
      hist_bins[18][u][j]->SetBinContent(i+1,INT_[i][j][18][u]);
      hist_bins[19][u][j]->SetBinContent(i+1,INT_[i][j][19][u]);
      hist_bins[20][u][j]->SetBinContent(i+1,INT_[i][j][20][u]);
      hist_bins[21][u][j]->SetBinContent(i+1,INT_[i][j][21][u]);
      hist_bins[22][u][j]->SetBinContent(i+1,INT_[i][j][22][u]);
      hist_bins[23][u][j]->SetBinContent(i+1,INT_[i][j][23][u]);
      hist_bins[24][u][j]->SetBinContent(i+1,INT_[i][j][24][u]);
      hist_bins[25][u][j]->SetBinContent(i+1,INT_[i][j][25][u]);
      hist_bins[26][u][j]->SetBinContent(i+1,INT_[i][j][26][u]);
      hist_bins[27][u][j]->SetBinContent(i+1,INT_[i][j][27][u]);
      hist_bins[28][u][j]->SetBinContent(i+1,INT_[i][j][28][u]);


      hist_bins[0][u][j]->SetBinError(i+1,ERR_[i][j][0][u]);
      hist_bins[1][u][j]->SetBinError(i+1,ERR_[i][j][1][u]);
      hist_bins[2][u][j]->SetBinError(i+1,ERR_[i][j][2][u]);
      hist_bins[3][u][j]->SetBinError(i+1,ERR_[i][j][3][u]);
      hist_bins[4][u][j]->SetBinError(i+1,ERR_[i][j][4][u]);
      hist_bins[5][u][j]->SetBinError(i+1,ERR_[i][j][5][u]);
      hist_bins[6][u][j]->SetBinError(i+1,ERR_[i][j][6][u]);
      hist_bins[7][u][j]->SetBinError(i+1,ERR_[i][j][7][u]);
      hist_bins[8][u][j]->SetBinError(i+1,ERR_[i][j][8][u]);
      hist_bins[9][u][j]->SetBinError(i+1,ERR_[i][j][9][u]);
      hist_bins[10][u][j]->SetBinError(i+1,ERR_[i][j][10][u]);
      hist_bins[11][u][j]->SetBinError(i+1,ERR_[i][j][11][u]);
      hist_bins[12][u][j]->SetBinError(i+1,ERR_[i][j][12][u]);
      hist_bins[13][u][j]->SetBinError(i+1,ERR_[i][j][13][u]);
      hist_bins[14][u][j]->SetBinError(i+1,ERR_[i][j][14][u]);
      hist_bins[15][u][j]->SetBinError(i+1,ERR_[i][j][15][u]);
      hist_bins[16][u][j]->SetBinError(i+1,ERR_[i][j][16][u]);
      hist_bins[17][u][j]->SetBinError(i+1,ERR_[i][j][17][u]);
      hist_bins[18][u][j]->SetBinError(i+1,ERR_[i][j][18][u]);
      hist_bins[19][u][j]->SetBinError(i+1,ERR_[i][j][19][u]);
      hist_bins[20][u][j]->SetBinError(i+1,ERR_[i][j][20][u]);
      hist_bins[21][u][j]->SetBinError(i+1,ERR_[i][j][21][u]);
      hist_bins[22][u][j]->SetBinError(i+1,ERR_[i][j][22][u]);
      hist_bins[23][u][j]->SetBinError(i+1,ERR_[i][j][23][u]);
      hist_bins[24][u][j]->SetBinError(i+1,ERR_[i][j][24][u]);
      hist_bins[25][u][j]->SetBinError(i+1,ERR_[i][j][25][u]);
      hist_bins[26][u][j]->SetBinError(i+1,ERR_[i][j][26][u]);
      hist_bins[27][u][j]->SetBinError(i+1,ERR_[i][j][27][u]);
      hist_bins[28][u][j]->SetBinError(i+1,ERR_[i][j][28][u]);

    }
  }
}

TH1D* histo_1[8][81];
for (int u = 0; u < 81; ++u){

    histo_1[0][u] = new TH1D(Form("MRR2_S_bkg_Multijet%s",Systematic[u].c_str()), "", 232, 0, 232);  
    histo_1[1][u] = new TH1D(Form("MRR2_S_bkg_Top%s",Systematic[u].c_str()), "", 232, 0, 232);
    histo_1[2][u] = new TH1D(Form("MRR2_S_bkg_WJet%s",Systematic[u].c_str()), "", 232, 0, 232);
    histo_1[3][u] = new TH1D(Form("MRR2_S_bkg_ZJet%s",Systematic[u].c_str()), "", 232, 0, 232);  
    histo_1[4][u] = new TH1D(Form("MRR2_S_bkg_other%s",Systematic[u].c_str()), "", 232, 0, 232);
    histo_1[5][u] = new TH1D(Form("MRR2_S_bkg_TotMC%s",Systematic[u].c_str()), "", 232, 0, 232);
    histo_1[6][u] = new TH1D(Form("MRR2_S_T2bW_700_200%s",Systematic[u].c_str()), "", 232, 0, 232);
    histo_1[7][u] = new TH1D(Form("MRR2_S_T5ttcc_1500_400%s",Systematic[u].c_str()), "", 232, 0, 232);

}

for (int u = 0; u < 81; ++u){

  for (int i = 0; i<29; ++i){
    for (int j = 1; j<=8; ++j){
      histo_1[0][u]->SetBinContent(i*8+j, hist_bins[i][u][0]->GetBinContent(j)); // Multijet
      histo_1[1][u]->SetBinContent(i*8+j, hist_bins[i][u][1]->GetBinContent(j)); // Top
      histo_1[2][u]->SetBinContent(i*8+j, hist_bins[i][u][2]->GetBinContent(j)); // WJet
      histo_1[3][u]->SetBinContent(i*8+j, hist_bins[i][u][3]->GetBinContent(j)); // ZJet
      histo_1[4][u]->SetBinContent(i*8+j, hist_bins[i][u][4]->GetBinContent(j)); // other BG 
      histo_1[5][u]->SetBinContent(i*8+j, hist_bins[i][u][5]->GetBinContent(j)); // TotMC
      histo_1[6][u]->SetBinContent(i*8+j, hist_bins[i][u][6]->GetBinContent(j)); // T2bW
      histo_1[7][u]->SetBinContent(i*8+j, hist_bins[i][u][7]->GetBinContent(j)); // T5ttcc

      histo_1[0][u]->SetBinError(i*8+j, hist_bins[i][u][0]->GetBinError(j));    
      histo_1[1][u]->SetBinError(i*8+j, hist_bins[i][u][1]->GetBinError(j));
      histo_1[2][u]->SetBinError(i*8+j, hist_bins[i][u][2]->GetBinError(j));
      histo_1[3][u]->SetBinError(i*8+j, hist_bins[i][u][3]->GetBinError(j));
      histo_1[4][u]->SetBinError(i*8+j, hist_bins[i][u][4]->GetBinError(j));
      histo_1[5][u]->SetBinError(i*8+j, hist_bins[i][u][5]->GetBinError(j));
      histo_1[6][u]->SetBinError(i*8+j, hist_bins[i][u][6]->GetBinError(j));
      histo_1[7][u]->SetBinError(i*8+j, hist_bins[i][u][7]->GetBinError(j));
    }
  }
}

TFile* outFile = new TFile("DataCard_Test.root", "recreate");
TDirectory* d1 = outFile->mkdir("Multijet");
TDirectory* d2 = outFile->mkdir("Top");
TDirectory* d3 = outFile->mkdir("WJet");
TDirectory* d4 = outFile->mkdir("ZJet");
TDirectory* d5 = outFile->mkdir("Other");
TDirectory* d6 = outFile->mkdir("TotMC");


  d1->cd();
  for (int i = 0; i <81; ++i) histo_1[0][i]->Write();
  d1->Close(); 

  d2->cd();
  for (int i = 0; i <81; ++i) histo_1[1][i]->Write();
  d2->Close();

  d3->cd();
  for (int i = 0; i <81; ++i) histo_1[2][i]->Write();
  d3->Close();

  d4->cd();
  for (int i = 0; i <81; ++i) histo_1[3][i]->Write();
  d4->Close();

  d5->cd();
  for (int i = 0; i <81; ++i) histo_1[4][i]->Write();
  d5->Close();

  d6->cd();
  for (int i = 0; i <81; ++i) histo_1[5][i]->Write();
  d6->Close();
    
  for (int i = 0; i <81; ++i) histo_1[6][i]->Write();
  for (int i = 0; i <81; ++i) histo_1[7][i]->Write();


}

void UnrolledRootMaker(){
  UnrolledPlots();
}