#include "B2PrimaryGeneratorAction.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "G4IonTable.hh"
#include "Randomize.hh"

#include "Config.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B2PrimaryGeneratorAction::B2PrimaryGeneratorAction()
 : G4VUserPrimaryGeneratorAction()
{
  G4int nofParticles = 1;
  fParticleGun = new G4ParticleGun(nofParticles);
  
  Config* configure = Config::Get_Config_Man();
  G4String ParticleName = configure->Get_ConfigValue_string("Particle");
  G4double Certain_Momentum = configure->Get_ConfigValue_double("Certain_Momentum")*MeV;
  G4double Certain_Energy = configure->Get_ConfigValue_double("Certain_Energy")*MeV;
  
  G4ParticleDefinition* particleDefinition = 0;
  
  if(ParticleName=="proton" || ParticleName=="pi+" || ParticleName=="pi-" || ParticleName=="e-" || ParticleName=="e+")
  {
    particleDefinition = G4ParticleTable::GetParticleTable()->FindParticle(ParticleName.c_str());
  }
  else if(ParticleName=="heavyion")
  {
    G4double Particle_A = configure->Get_ConfigValue_double("Particle_A");
    G4double Particle_Z = configure->Get_ConfigValue_double("Particle_Z");
    particleDefinition = G4IonTable::GetIonTable()->GetIon(Particle_Z,Particle_A,0);//[1]
  }
  
  fParticleGun->SetParticleDefinition(particleDefinition);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
  
  if(Certain_Energy>0)
  {
    fParticleGun->SetParticleEnergy(Certain_Energy);
  }
  else if(Certain_Momentum>0)
  {
    fParticleGun->SetParticleMomentum(Certain_Momentum);
  }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B2PrimaryGeneratorAction::~B2PrimaryGeneratorAction()
{
  delete fParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B2PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  // This function is called at the begining of event
 // G4cout<<"Particle Energy: "<<fParticleGun->GetParticleEnergy()<<G4endl;
//  G4cout<<"Particle Momentum: "<<fParticleGun->GetParticleMomentum()<<G4endl;
  fParticleGun->SetParticlePosition(G4ThreeVector(0., 0., 0));

  fParticleGun->GeneratePrimaryVertex(anEvent);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
