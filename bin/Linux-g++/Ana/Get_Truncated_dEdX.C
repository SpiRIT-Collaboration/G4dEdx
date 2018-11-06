void Get_Truncated_dEdX()
{
  string Tag_B = "0.5T";
  string Tag_StepLength = "0.5mm";
  string Length_Z = "Z_12mm";
  
  string ParticleName = "pi-"; //"pi-","pi+","proton","2H","3H","3He","4He"}

  double Z = 1;
  if (ParticleName == "pi-")
    Z = -1;
  else if (ParticleName == "3He" || ParticleName == "4He")
    Z = 2;

  auto filesString = gSystem -> GetFromPipe(Form("ls SimData/%s* | sed -e s/.*Momentum// -e s/MeV.*//", ParticleName.c_str()));
  filesString.ReplaceAll('\n', " ");
  auto listFiles = filesString.Tokenize(" ");

  int MomentumNum = listFiles -> GetEntries();
  vector<Int_t> ParticleMomentum_Value;
  for (auto i = 0; i < MomentumNum; i++) {
    auto tempName = ((TObjString *) listFiles -> At(i)) -> String();
    auto momVal = tempName.Atoi();

    ParticleMomentum_Value.push_back(momVal);
  }

  sort(ParticleMomentum_Value.begin(), ParticleMomentum_Value.end());

  double *ParticleMomentum_PZ_Value = new double[MomentumNum];
  
  string *ParticleMomentum = new string[MomentumNum];
  
  double *Truncated_Value = new double[MomentumNum];
  for (auto i = 0; i < MomentumNum; i++)
    Truncated_Value[i] = 0;

  TGraph* gr1_TruncatedValue = 0;
  
  string FileName_TruncatedAvg_Results = "f1_TruncatedAvg_Results.root";
  
  int SegmentNum = 80; //Here is the Segment Num.
  double LowerKeepPercent = 0.1; //Here is the truncated fraction: [0,0.7] is the default setting.
  double KeepPercent = 0.7; //Here is the truncated fraction: [0,0.7] is the default setting.
  
  char NameTem[200];
  for(int i=0;i<MomentumNum;i++)
  {
    sprintf(NameTem,"Momentum%dMeV",ParticleMomentum_Value[i]);
    ParticleMomentum[i] = NameTem;
    ParticleMomentum_PZ_Value[i] = (double)ParticleMomentum_Value[i]/Z;
  }
  
  Get_dEdX* Analyzer = new Get_dEdX();
  Analyzer->SetRecordFile(FileName_TruncatedAvg_Results);
  
  for(int j=0;j<MomentumNum;j++)
  {
    Analyzer->Initial(ParticleName, ParticleMomentum[j].c_str(), Tag_B, Tag_StepLength, Length_Z); //Here will produce the data file name and used to be analyzed.
    Analyzer->Set_TrackParas(SegmentNum, LowerKeepPercent, KeepPercent);
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
