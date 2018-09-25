#ifndef Get_dEdX_h
#define Get_dEdX_h 1

#include "TObject.h"
#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "iostream"
#include "TMath.h"
#include "TTree.h"
#include "TF1.h"
#include "TCanvas.h"
#include "fstream"

using namespace std;
using namespace TMath;

class Get_dEdX : public TObject
{
public:
  Get_dEdX();
  ~Get_dEdX();

public:
  string Tag_Particle;
  string Tag_E;
  string Tag_B;
  string Tag_StepLength;
  string TPC_Length_Z;
  
  int SegmentNum;
  double KeepPercent;
  
  string RecorderFileName;
  void SetRecordFile(string FileName_tem);
  
  void Initial(string ParticleName, string Momentum, string Magnetic, string StepLength, string Length_Z);
  void Set_TrackParas(int SegmentNum_tem, double KeepPercent_tem);
  double Ana_Truncated_dEdX();
  double Ana_MostProb_dEdX();
  
  double Cal_Truncated_Mean(int HitNum,double* dEdX_Array);
  double Cal_FWHM(TH1D* h1);
  
  ClassDef(Get_dEdX,1)
};

#endif
