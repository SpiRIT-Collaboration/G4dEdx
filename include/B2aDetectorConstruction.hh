#ifndef B2aDetectorConstruction_h
#define B2aDetectorConstruction_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "tls.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;
class G4Material;
class G4UserLimits;
class G4GlobalMagFieldMessenger;

class B2aDetectorMessenger;

/// Detector construction class to define materials, geometry
/// and global uniform magnetic field.

class B2aDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    B2aDetectorConstruction();
    virtual ~B2aDetectorConstruction();

  public:
    virtual G4VPhysicalVolume* Construct();
    virtual void ConstructSDandField();

    // Set methods
    void SetTargetMaterial (G4String );
    void SetChamberMaterial(G4String );
    void SetMaxStep (G4double );
    void SetCheckOverlaps(G4bool );
    G4Material* P10_Standard;
    G4Material* P10_24C;
    G4Material* Material_TPC;
    
  private:
    // methods
    void DefineMaterials();
    G4VPhysicalVolume* DefineVolumes();
    
    // data members
    G4int fNbOfChambers;

    G4LogicalVolume*   fLogicTarget;     // pointer to the logical Target
    G4LogicalVolume**  fLogicChamber;    // pointer to the logical Chamber

    G4Material*        fTargetMaterial;  // pointer to the target  material
    G4Material*        fChamberMaterial; // pointer to the chamber material

    G4UserLimits* fStepLimit;            // pointer to user step limits

    B2aDetectorMessenger*  fMessenger;   // messenger

    static G4ThreadLocal G4GlobalMagFieldMessenger*  fMagFieldMessenger; 
                                         // magnetic field messenger
    
    G4bool  fCheckOverlaps; // option to activate checking of volumes overlaps 
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
