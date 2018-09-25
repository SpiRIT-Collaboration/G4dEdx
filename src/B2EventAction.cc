#include "B2EventAction.hh"

#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4ios.hh"
#include "iostream"
#include "B2TrackerHit.hh"
#include "G4DigiManager.hh"

using namespace std;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B2EventAction::B2EventAction(B2RunAction* p_Run_tem)
: G4UserEventAction()
{
  m_DM = G4DigiManager::GetDMpointer();
  m_Run = p_Run_tem;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B2EventAction::~B2EventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B2EventAction::BeginOfEventAction(const G4Event*)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B2EventAction::EndOfEventAction(const G4Event* evt)
{
  G4int event_id = evt->GetEventID();
  if(event_id%10000==0) 
  { 
    cout<<"EvtID: "<<event_id<<endl;
  }
  
  G4int HCI = -1;
  HCI = m_DM->GetHitsCollectionID("TrackerHitsCollection");

  if(HCI>=0)
  {
    B2TrackerHitsCollection* HC = 0;
    HC = (B2TrackerHitsCollection*) (m_DM->GetHitsCollection(HCI));
    G4int n_hit = HC->entries();
    if(n_hit>0)
    {
      double Edep_tem[10000] = {0};
      double LostE_tem[10000] = {0};
      double StepLength_tem[10000] = {0};
      double PosX_tem[10000] = {0};
      double PosY_tem[10000] = {0};
      double PosZ_tem[10000] = {0};
      int TrackID_tem[10000] = {-1};
      
      int HitsNum = 0;
      for(G4int i=0;i<n_hit;i++)
      {
        Edep_tem[HitsNum] = (*HC)[i]->GetEdep();
        LostE_tem[HitsNum] = (*HC)[i]->GetELost();
        TrackID_tem[HitsNum] = (*HC)[i]->GetTrackID();
        StepLength_tem[HitsNum] = (*HC)[i]->GetStepLength();
        PosX_tem[HitsNum] = (*HC)[i]->GetPos().x();
        PosY_tem[HitsNum] = (*HC)[i]->GetPos().y();
        PosZ_tem[HitsNum] = (*HC)[i]->GetPos().z();
        HitsNum++;
      }
      m_Run->FillData(HitsNum,Edep_tem,LostE_tem,StepLength_tem,TrackID_tem,PosX_tem,PosY_tem,PosZ_tem);
    }
  }

}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
