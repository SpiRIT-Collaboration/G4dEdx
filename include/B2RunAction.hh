#ifndef B2RunAction_h
#define B2RunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "iostream"

using namespace std;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class G4Run;

/// Run action class

class B2RunAction : public G4UserRunAction
{
  public:
    B2RunAction();
    virtual ~B2RunAction();

    virtual void BeginOfRunAction(const G4Run* run);
    virtual void EndOfRunAction(const G4Run* run);
    
public:
  int HitsNum;
  double Edep_Ionization[10000];
  double LostE[10000];
  double StepLength[10000];
  int TrackID[10000];
  double PosX[10000];
  double PosY[10000];
  double PosZ[10000];
  void FillData(int HitsNum_tem,double* Edep_tem,double* LostE_tem,double* StepLength_tem,int* ID_tem,double* PosX_tem,double* PosY_tem,double* PosZ_tem)
  { 
    HitsNum = HitsNum_tem;
    for(int i=0;i<HitsNum;i++)
    {
      Edep_Ionization[i] = Edep_tem[i];
      LostE[i] = LostE_tem[i];
      StepLength[i] = StepLength_tem[i];
      TrackID[i] = ID_tem[i];
      PosX[i] = PosX_tem[i];
      PosY[i] = PosY_tem[i];
      PosZ[i] = PosZ_tem[i];
    }
    t1_data->Fill(); 
  }
  
public:
  TFile* f1_data;
  TTree* t1_data;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
