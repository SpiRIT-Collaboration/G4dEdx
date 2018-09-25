#include "Get_dEdX.hh"
ClassImp(Get_dEdX);

Get_dEdX::Get_dEdX()
{;}

Get_dEdX::~Get_dEdX()
{;}

void Get_dEdX::Initial(string ParticleName, string Momentum, string Magnetic, string StepLength, string Length_Z)
{
  Tag_Particle = ParticleName;
  Tag_E = Momentum;
  Tag_B = Magnetic;
  Tag_StepLength = StepLength;
  TPC_Length_Z = Length_Z;
}

void Get_dEdX::Set_TrackParas(int SegmentNum_tem, double LowerKeepPercent_tem, double KeepPercent_tem)
{
  SegmentNum = SegmentNum_tem;
  LowerKeepPercent = LowerKeepPercent_tem;
  KeepPercent = KeepPercent_tem;
}

double Get_dEdX::Ana_Truncated_dEdX()
{
  char NameTem[200];
  sprintf(NameTem,"./SimData/%s_%s_%s_%s_%s.root",Tag_Particle.c_str(),Tag_E.c_str(),Tag_B.c_str(),Tag_StepLength.c_str(),TPC_Length_Z.c_str());
  cout<<" Analyzing "<<NameTem<<endl;
  
  TFile* f1_data = new TFile(NameTem);
  TTree* t1_data = (TTree*)f1_data->Get("t1");
  
  int HitsNum;
  double Edep_Ionization[10000];
  double LostE[10000];
  double StepLength[10000];
  int TrackID[10000];
  double PosX[10000];
  double PosY[10000];
  double PosZ[10000];
  
  t1_data->SetBranchAddress("HitsNum",&HitsNum);
//  t1_data->SetBranchAddress("PosX",PosX);
//  t1_data->SetBranchAddress("PosY",PosY);
//  t1_data->SetBranchAddress("PosZ",PosZ);
//  t1_data->SetBranchAddress("Edep_Ionization",Edep_Ionization);
  t1_data->SetBranchAddress("LostE",LostE);
  t1_data->SetBranchAddress("StepLength",StepLength);
  t1_data->SetBranchAddress("TrackID",TrackID);
  
  int EvtNum = t1_data->GetEntries();
  cout<<"Track Num: "<<EvtNum/SegmentNum<<endl;
  
  const int TrackNum = EvtNum/SegmentNum;
  double *Truncated_Value = new double[TrackNum];
  for (int i = 0; i < TrackNum; i++)
    Truncated_Value[i] = 0;
  double Avg_TruncatedValue = 0;
  
  for(int i=0;i<EvtNum/SegmentNum;i++)
  {
    if((i)%1000==0) { cout<<"Evt:"<<i<<endl; }
    double *SegmentEdep = new double[SegmentNum];
    for (int i = 0; i < SegmentNum; i++)
      SegmentEdep[i] = 0;
    for(int j=0;j<SegmentNum;j++)
    {
      t1_data->GetEntry(i+j);
      double SegmentEdep_Tem = 0;
      for(int k=0;k<HitsNum;k++)
      {
        if(TrackID[k]==1)
        {
          SegmentEdep_Tem += LostE[k];
        }
      }
      SegmentEdep[j] = SegmentEdep_Tem;
    }
    double Edep_tem = Cal_Truncated_Mean(SegmentNum,SegmentEdep);
    Truncated_Value[i] = Edep_tem*1000.0/1.2;
    Avg_TruncatedValue += Truncated_Value[i];
  }
  
  Avg_TruncatedValue = Avg_TruncatedValue/TrackNum;
  
  sprintf(NameTem,"h1_dEdX_TruncatedAvgDis_%s_%s_%s_%s_%s_SegmentNum%d_KeepPercent%.2f",Tag_Particle.c_str(),Tag_E.c_str(),Tag_B.c_str(),Tag_StepLength.c_str(),TPC_Length_Z.c_str(),SegmentNum,KeepPercent);
  TH1D* h1_dEdX_AvgDis = new TH1D(NameTem,NameTem,100,0.5*Avg_TruncatedValue,1.5*Avg_TruncatedValue);// unit:keV/cm
  for(int i=0;i<TrackNum;i++)
  {
    h1_dEdX_AvgDis->Fill(Truncated_Value[i]);
  }
  
/*
  sprintf(NameTem,"c1_dEdX_AvgDis_%s_%s_%s_%s_%s_SegmentNum%d",Tag_Particle.c_str(),Tag_E.c_str(),Tag_B.c_str(),Tag_StepLength.c_str(),TPC_Length_Z.c_str(),SegmentNum);
  TCanvas* c1_dEdX_AvgDis = new TCanvas(NameTem,NameTem,1);
  c1_dEdX_AvgDis->cd();
  h1_dEdX_AvgDis->Draw();
*/
  TFile* f1_Results = new TFile(RecorderFileName.c_str(),"update");
  f1_Results->cd();
  h1_dEdX_AvgDis->Write("",TObject::kOverwrite);
  cout<<" Writing "<<h1_dEdX_AvgDis->GetName()<<" into "<<f1_Results->GetName()<<endl;
  f1_Results->Close();
  f1_data->Close();
  
return Avg_TruncatedValue;
}

double Get_dEdX::Ana_MostProb_dEdX()
{
  char NameTem[200];
  sprintf(NameTem,"./SimData/%s_%s_%s_%s_%s.root",Tag_Particle.c_str(),Tag_E.c_str(),Tag_B.c_str(),Tag_StepLength.c_str(),TPC_Length_Z.c_str());
  cout<<" Analyzing "<<NameTem<<endl;
    
  TFile* f1_data = new TFile(NameTem);
  TTree* t1_data = (TTree*)f1_data->Get("t1");
  
  sprintf(NameTem,"h1_dEdX_StragglingFunc_%s_%s_%s_%s_%s",Tag_Particle.c_str(),Tag_E.c_str(),Tag_B.c_str(),Tag_StepLength.c_str(),TPC_Length_Z.c_str());
  TH1D* h1_dEdX_StragglingFunc = new TH1D(NameTem,NameTem,500,0,100);// unit:keV/cm
  
  int HitsNum;
  double LostE[10000];
  double StepLength[10000];
  int TrackID[10000];
  
  t1_data->SetBranchAddress("HitsNum",&HitsNum);
  t1_data->SetBranchAddress("LostE",LostE);
  t1_data->SetBranchAddress("StepLength",StepLength);
  t1_data->SetBranchAddress("TrackID",TrackID);
  
  int EvtNum = t1_data->GetEntries();
  cout<<"Evt Num: "<<EvtNum<<endl;
  
  for(int i=0;i<EvtNum;i++)
  {
    int Proton_HitNum = 0;
    double TrackLength = 0;
    double LostEnergy = 0;
    
    if(i%10000==0) { cout<<"Evt:"<<i<<endl; }
    t1_data->GetEntry(i);
    
    for(int j=0;j<HitsNum;j++)
    {
      if(TrackID[j]==1)
      {
        LostEnergy += LostE[j];
        TrackLength += StepLength[j];
      }
    }
    h1_dEdX_StragglingFunc->Fill(LostEnergy/TrackLength*10000);
  }
  
//  sprintf(NameTem,"c1_dEdX_Straggling_%s_%s_%s_%s_%s",Tag_Particle.c_str(),Tag_E.c_str(),Tag_B.c_str(),Tag_StepLength.c_str(),TPC_Length_Z.c_str());
//  TCanvas* c1_dEdX_Straggling = new TCanvas(NameTem,NameTem,1);
//  h1_dEdX_StragglingFunc->Draw();
  double MaxmumBinContent = h1_dEdX_StragglingFunc->GetMaximum();
  h1_dEdX_StragglingFunc->Scale(1/MaxmumBinContent);
    
  double FWHM = Cal_FWHM(h1_dEdX_StragglingFunc);
  double X_MaxContent = h1_dEdX_StragglingFunc->GetBinCenter(h1_dEdX_StragglingFunc->GetMaximumBin());
  h1_dEdX_StragglingFunc->Fit("landau","","",X_MaxContent-0.4*FWHM,X_MaxContent+1.0*FWHM);
  TF1* f1_tem = (TF1*) h1_dEdX_StragglingFunc->GetFunction("landau");
  double MostProb_Value = f1_tem->GetParameter(1);
  
  TFile* f1_Results = new TFile(RecorderFileName.c_str(),"update");
  f1_Results->cd();
  h1_dEdX_StragglingFunc->Write("",TObject::kOverwrite);
  
  f1_Results->Close();
  f1_data->Close();
return MostProb_Value;
}

void Get_dEdX::SetRecordFile(string FileName_tem)
{
  RecorderFileName = FileName_tem;
}

double Get_dEdX::Cal_Truncated_Mean(int HitNum,double* dEdX_Array)
{
  double dEdX_tem = 0;

  for(int i=0;i<HitNum-1;i++)
  {
    for(int j=0;j<HitNum-i-1;j++)
    {
      if(dEdX_Array[j]>dEdX_Array[j+1])
      {
        dEdX_tem = dEdX_Array[j+1];
        dEdX_Array[j+1] = dEdX_Array[j];
        dEdX_Array[j] = dEdX_tem;
      }
    }
  }

  dEdX_tem = 0;
  
  for(int i=LowerKeepPercent*HitNum;i<HitNum*KeepPercent;i++)
  {
    dEdX_tem += dEdX_Array[i]; 
  }
return dEdX_tem/(HitNum*KeepPercent);
}

double Get_dEdX::Cal_FWHM(TH1D* h1)
{
  int bin1 = h1->FindFirstBinAbove(h1->GetMaximum()*0.5);
  int bin2 = h1->FindLastBinAbove(h1->GetMaximum()*0.5);
  double fwhm = -h1->GetBinCenter(bin1) + h1->GetBinCenter(bin2);

return fwhm;
}
