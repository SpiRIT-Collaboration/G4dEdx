void Get_MostProb_dEdX()
{
  const int MomentumNum = 20;
  const int ParticleNum = 1;
  
  string Tag_B = "0.5T";
  string Tag_StepLength = "0.5mm";
  string Length_Z = "Z_12mm";
  
  string ParticleName = "4He";//"proton","2H","3H","3He","4He"};
  double Z = 2;
//  double ParticleMomentum_Value[] = {200,250,300,350,400,450,500,550,600,650,700,750,800,900,1000,1200,1400,1600,1800,2000};
//  double ParticleMomentum_Value[] = {400,450,500,550,600,650,700,750,800,850,900,950,1000,1100,1200,1300,1400,1600,1800,2000};
//  double ParticleMomentum_Value[] = {500,550,600,650,700,750,800,850,900,950,1000,1100,1200,1300,1400,1600,1700,1800,1900,2000};
//  double ParticleMomentum_Value[] = {1000,1100,1200,1300,1400,1500,1600,1700,1800,1900,2000,2200,2400,2600,2800,3200,3400,3600,3800,4000};
  double ParticleMomentum_Value[] = {1400,1500,1600,1700,1800,1900,2000,2100,2200,2300,2400,2500,2600,2700,2800,3200,3400,3600,3800,4000};
  double ParticleMomentum_PZ_Value[MomentumNum];
  
  string ParticleMomentum[MomentumNum];
  
  double MostProb_Value[MomentumNum] = {0};
  TGraph* gr1_MostProb = 0;
  
  string FileName_MostProb_Results = "f1_MostProb_Results.root";
  
  char NameTem[200];
  for(int i=0;i<MomentumNum;i++)
  {
    sprintf(NameTem,"Momentum%dMeV",ParticleMomentum_Value[i]);
    ParticleMomentum[i] = NameTem;
    ParticleMomentum_PZ_Value[i] = ParticleMomentum_Value[i]/Z;
  }
  
  Get_dEdX* Analyzer = new Get_dEdX();
  Analyzer->SetRecordFile(FileName_MostProb_Results);
  
  for(int j=0;j<MomentumNum;j++)
  {
    Analyzer->Initial(ParticleName.c_str(), ParticleMomentum[j].c_str(), Tag_B, Tag_StepLength, Length_Z);
    MostProb_Value[j] = Analyzer->Ana_MostProb_dEdX();
  }
  
  TCanvas* c1_MostProb_Mean = new TCanvas("c1_MostProb_Mean","c1_MostProb_Mean",1);
  gr1_MostProb = new TGraph(MomentumNum,ParticleMomentum_PZ_Value,MostProb_Value);
  gr1_MostProb->Draw("AC*");
  
  TFile* f1_MostProb_Results = new TFile(FileName_MostProb_Results.c_str(),"update");
  sprintf(NameTem,"gr1_dEdX_MostProb_%s_%s_%s_%s",ParticleName.c_str(),Tag_B.c_str(),Tag_StepLength.c_str(),Length_Z.c_str());
  gr1_MostProb->Write(NameTem,TObject::kOverwrite);
  f1_MostProb_Results->Close();
}
