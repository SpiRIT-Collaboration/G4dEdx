#include "B2TrackerSD.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B2TrackerSD::B2TrackerSD(const G4String& name,
                         const G4String& hitsCollectionName) 
 : G4VSensitiveDetector(name),
   fHitsCollection(NULL)
{
  collectionName.insert(hitsCollectionName);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B2TrackerSD::~B2TrackerSD() 
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B2TrackerSD::Initialize(G4HCofThisEvent* hce)
{
  // Create hits collection

  fHitsCollection 
    = new B2TrackerHitsCollection(SensitiveDetectorName, collectionName[0]); 

  // Add this collection in hce

  G4int hcID 
    = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  hce->AddHitsCollection( hcID, fHitsCollection ); 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool B2TrackerSD::ProcessHits(G4Step* aStep, 
                                     G4TouchableHistory*)
{
  // energy deposit
  G4double edep = aStep->GetTotalEnergyDeposit();
  G4double DeltaE = -aStep->GetDeltaEnergy();
/*
  if(aStep->GetPostStepPoint()->GetStepStatus()==fGeomBoundary && aStep->GetTrack()->GetTrackID()==1)
  {
    G4cout<<aStep->GetTrack()->GetKineticEnergy()<<G4endl;
  }
  G4cout<<"TrackID: "<<aStep->GetTrack()->GetTrackID()<<" Name: "<<aStep->GetTrack()->GetDefinition()->GetParticleName()<<"  DeltaE: "<<DeltaE<<" Edep: "<<edep;
  if(fabs(edep-DeltaE)>0.000001*(edep+DeltaE))
  {
    G4cout<<"  Track Num: "<<aStep->GetNumberOfSecondariesInCurrentStep()<<G4endl;
  }
  else 
  {
    G4cout<<G4endl;
  }
*/
//  if (DeltaE==0.) return false;
  B2TrackerHit* newHit = new B2TrackerHit();
  newHit->SetTrackID  (aStep->GetTrack()->GetTrackID());
  newHit->SetStepLength(aStep->GetStepLength());
//  newHit->SetEdep(-aStep->GetDeltaEnergy());
//  G4cout<<aStep->GetDeltaEnergy()<<G4endl;
  newHit->SetEdep(edep);
  newHit->SetELost(DeltaE);
  newHit->SetPos (aStep->GetPostStepPoint()->GetPosition());
  
  fHitsCollection->insert( newHit );
  //newHit->Print();
  return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B2TrackerSD::EndOfEvent(G4HCofThisEvent*)
{
  if ( verboseLevel>1 ) { 
     G4int nofHits = fHitsCollection->entries();
     G4cout << G4endl
            << "-------->Hits Collection: in this event they are " << nofHits 
            << " hits in the tracker chambers: " << G4endl;
     for ( G4int i=0; i<nofHits; i++ ) (*fHitsCollection)[i]->Print();
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
