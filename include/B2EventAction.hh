#ifndef B2EventAction_h
#define B2EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"
#include "B2RunAction.hh"

class G4DigiManager;
/// Event action class

class B2EventAction : public G4UserEventAction
{
public:
  B2EventAction(B2RunAction* p_Run_tem);
  virtual ~B2EventAction();
  G4DigiManager* m_DM;
  
  virtual void  BeginOfEventAction(const G4Event* );
  virtual void  EndOfEventAction(const G4Event* );
  
public:
  B2RunAction* m_Run;
  
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
