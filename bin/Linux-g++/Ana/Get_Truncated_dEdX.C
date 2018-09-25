void Get_Truncated_dEdX()
{
  const int MomentumNum = 22;
  const int ParticleNum = 1;
  
  string Tag_B = "0.5T";
  string Tag_StepLength = "0.5mm";
  string Length_Z = "Z_12mm";
  
  string ParticleName = "3H";//"pi-","pi+","proton","2H","3H","3He","4He"};
  double Z = 1;
//  double ParticleMomentum_Value[] = {30,40,50,100,125,150,175,200,225,250,275,300,325,350,375,400,425,450,475,500}; //MomentumNum: 20, corresponding pi-
//  double ParticleMomentum_Value[] = {100,150,200,250,300,350,400,450,500,550,600,650,700,750,800,900,1000,1200,1400,1600,1800,2000}; //MomentumNum: 22 corresponding pi+
//  double ParticleMomentum_Value[] = {300,350,400,450,500,550,600,650,700,750,800,850,900,950,1000,1100,1200,1300,1400,1600,1800,2000}; //MomentumNum: 22 corresponding proton
  double ParticleMomentum_Value[] = {450,475,500,550,600,650,700,750,800,850,900,950,1000,1100,1200,1300,1400,1600,1800,2000,2500,3000}; //MomentumNum: 22 corresponding 2H
//  double ParticleMomentum_Value[] = {1000,1100,1200,1300,1400,1500,1600,1700,1800,1900,2000,2200,2400,2600,2800,3200,3400,3600,3800,4000};//MomentumNum: 20 corresponding 3H
//  double ParticleMomentum_Value[] = {1400,1500,1600,1700,1800,1900,2000,2100,2200,2300,2400,2500,2600,2700,2800,3200,3400,3600,3800,4000};//MomentumNum: 20 corresponding He
  double ParticleMomentum_PZ_Value[MomentumNum];
  
  string ParticleMomentum[MomentumNum];
  
  double Truncated_Value[MomentumNum] = {0};
  TGraph* gr1_TruncatedValue = 0;
  
  string FileName_TruncatedAvg_Results = "f1_TruncatedAvg_Results.root";
  
  int SegmentNum = 80; //Here is the Segment Num.
  double KeepPercent = 0.7; //Here is the truncated fraction: [0,0.7] is the default setting.
  
  char NameTem[200];
  for(int i=0;i<MomentumNum;i++)
  {
    sprintf(NameTem,"Momentum%dMeV",ParticleMomentum_Value[i]);
    ParticleMomentum[i] = NameTem;
    ParticleMomentum_PZ_Value[i] = ParticleMomentum_Value[i]/Z;
  }
  
  Get_dEdX* Analyzer = new Get_dEdX();
  Analyzer->SetRecordFile(FileName_TruncatedAvg_Results);
  
  for(int j=0;j<MomentumNum;j++)
  {
    Analyzer->Initial(ParticleName, ParticleMomentum[j].c_str(), Tag_B, Tag_StepLength, Length_Z); //Here will produce the data file name and used to be analyzed.
    Analyzer->Set_TrackParas(SegmentNum, KeepPercent);
    Truncated_Value[j] = Analyzer->Ana_Truncated_dEdX();
  }
  
  TCanvas* c1_truncated_Mean = new TCanvas("c1_truncated_Mean","c1_truncated_Mean",1);
  gr1_TruncatedValue = new TGraph(MomentumNum,ParticleMomentum_PZ_Value,Truncated_Value);
  gr1_TruncatedValue->Draw("AC*");
  
  TFile* f1_TruncatedAvg_Results = new TFile(FileName_TruncatedAvg_Results.c_str(),"update");
  sprintf(NameTem,"gr1_dEdX_TruncatedAvg_%s_%s_%s_%s",ParticleName.c_str(),Tag_B.c_str(),Tag_StepLength.c_str(),Length_Z.c_str());
  gr1_TruncatedValue->Write(NameTem,TObject::kOverwrite);
  f1_TruncatedAvg_Results->Close();
}
