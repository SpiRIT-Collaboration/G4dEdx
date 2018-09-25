#include "B2RunAction.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "Config.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B2RunAction::B2RunAction()
 : G4UserRunAction()
{ 
  // set printing event number per each 100 events
  G4RunManager::GetRunManager()->SetPrintProgress(1000);
//  f1_data = 0;
//  t1_data = 0;
  HitsNum = 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B2RunAction::~B2RunAction()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B2RunAction::BeginOfRunAction(const G4Run*)
{ 
  //inform the runManager to save random number seed
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);
  Config* configure = Config::Get_Config_Man();
  G4String Output_FileName = configure->Get_ConfigValue_string("Output_FileName");
  
  f1_data = new TFile(Output_FileName.c_str(),"recreate");
  t1_data = new TTree("t1","dEdX_Hits");
  
  t1_data->Branch("HitsNum",&HitsNum,"HitsNum/I");
//  t1_data->Branch("PosX",PosX,"PosX[HitsNum]/D");
//  t1_data->Branch("PosY",PosY,"PosY[HitsNum]/D");
//  t1_data->Branch("PosZ",PosZ,"PosZ[HitsNum]/D");
//  t1_data->Branch("Edep_Ionization",Edep_Ionization,"Edep_Ionization[HitsNum]/D");
  t1_data->Branch("LostE",LostE,"LostE[HitsNum]/D");
  t1_data->Branch("StepLength",StepLength,"StepLength[HitsNum]/D");
  t1_data->Branch("TrackID",TrackID,"TrackID[HitsNum]/I");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B2RunAction::EndOfRunAction(const G4Run* )
{

  if(t1_data!=0) { t1_data->Write(); }
  if(t1_data!=0) { t1_data->Delete(); t1_data=0; }
  if(f1_data!=0)
  {
    cout<<f1_data->GetName()<<" Closed!"<<endl;
    f1_data->Close(); f1_data->Delete(); f1_data=0; 
  }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
