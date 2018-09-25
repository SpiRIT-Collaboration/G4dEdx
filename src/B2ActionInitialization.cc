
#include "B2ActionInitialization.hh"
#include "B2PrimaryGeneratorAction.hh"
#include "B2RunAction.hh"
#include "B2EventAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B2ActionInitialization::B2ActionInitialization()
 : G4VUserActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B2ActionInitialization::~B2ActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B2ActionInitialization::BuildForMaster() const
{
  SetUserAction(new B2RunAction);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B2ActionInitialization::Build() const
{
  SetUserAction(new B2PrimaryGeneratorAction);
  B2RunAction* m_Run = new B2RunAction();
  SetUserAction(m_Run);
  SetUserAction(new B2EventAction(m_Run));
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
