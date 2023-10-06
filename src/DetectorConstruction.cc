#include "DetectorConstruction.hh"
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{
    // Get nist material manager
    G4NistManager* nist = G4NistManager::Instance();

    // Envelope parameters
    //
    G4double env_sizeXY = 4*m, env_sizeZ = 4.21*m;
    G4Material* env_mat = nist->FindOrBuildMaterial("G4_Fe");
    //  G4Material* env_mat = new G4Material("Graphite", 6., 12.0107*(g/mole), 2.5*g/cm3);
    G4cout << "DetectorConstruction::A() " << env_mat->GetA()/(g/mole) << G4endl;
    G4cout << "DetectorConstruction::Z() " << env_mat->GetZ() << G4endl;
    G4cout << "DetectorConstruction::Density() " << env_mat->GetDensity()/(g/cm3) << G4endl;

    // Option to switch on/off checking of volumes overlaps
    //
    G4bool checkOverlaps = true;

    //
    // World
    //
    G4double world_sizeXY = 1.2*env_sizeXY;
    G4double world_sizeZ  = 1.2*env_sizeZ;
    G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");

    G4Box* solidWorld = new G4Box("World", 0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ);

    G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, world_mat, "World");

    G4VPhysicalVolume* physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "World", 0, false, 0,  checkOverlaps);
    G4Box* solidEnv = new G4Box("Envelope", 0.5*env_sizeXY, 0.5*env_sizeXY, 0.5*env_sizeZ);
    G4LogicalVolume* logicEnv =
        new G4LogicalVolume(solidEnv, env_mat, "Envelope");

    new G4PVPlacement(0,                       //no rotation
            G4ThreeVector(),         //at (0,0,0)
            logicEnv,                //its logical volume
            "Envelope",              //its name
            logicWorld,              //its mother  volume
            false,                   //no boolean operation
            0,                       //copy number
            checkOverlaps);          //overlaps checking


    // Set logicEnv as scoring volume
    //
    fScoringVolume = logicEnv;

    //
    //always return the physical World
    //
    return physWorld;
}
