#include "RunAction.hh"
#include "PrimaryGeneratorAction.hh"
#include "DetectorConstruction.hh"
#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4AccumulableManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::RunAction()
    :fOutputFileNamePtr(nullptr)
{
    // set printing event number per each event
    G4RunManager::GetRunManager()->SetPrintProgress(1);

    // Get analysis manager
    auto analysisManager = G4AnalysisManager::Instance();

    // Create directories
    analysisManager->SetVerboseLevel(1);
    analysisManager->SetNtupleMerging(true);
    // Creating ntuple
    analysisManager->CreateNtuple("brem", "dark photon bremsstrahlung in Fe");
    analysisManager->CreateNtupleIColumn("parentID");
    analysisManager->CreateNtupleIColumn("pID");
    analysisManager->CreateNtupleDColumn("p_px");
    analysisManager->CreateNtupleDColumn("p_py");
    analysisManager->CreateNtupleDColumn("p_pz");
    analysisManager->CreateNtupleDColumn("p_kEne");
    analysisManager->CreateNtupleDColumn("p_Mass");
    analysisManager->CreateNtupleDColumn("px");
    analysisManager->CreateNtupleDColumn("py");
    analysisManager->CreateNtupleDColumn("pz");
    analysisManager->CreateNtupleDColumn("kEne");
    analysisManager->CreateNtupleDColumn("pMass");
    analysisManager->CreateNtupleSColumn("ProcName");
    analysisManager->FinishNtuple();
}

RunAction::RunAction(const G4String* outputFileName)
    :fOutputFileNamePtr(outputFileName)
{
    // set printing event number per each event
    G4RunManager::GetRunManager()->SetPrintProgress(1);

    // Get analysis manager
    auto analysisManager = G4AnalysisManager::Instance();

    // Create directories
    analysisManager->SetVerboseLevel(1);
    analysisManager->SetNtupleMerging(true);
    // Creating ntuple
    analysisManager->CreateNtuple("brem", "dark photon bremsstrahlung in Fe");
    analysisManager->CreateNtupleIColumn("parentID"); //0
    analysisManager->CreateNtupleIColumn("pID"); //1
    analysisManager->CreateNtupleDColumn("p_px"); //2
    analysisManager->CreateNtupleDColumn("p_py"); //3
    analysisManager->CreateNtupleDColumn("p_pz"); //4
    analysisManager->CreateNtupleDColumn("p_kEne"); //5
    analysisManager->CreateNtupleDColumn("p_Mass"); //6
    analysisManager->CreateNtupleDColumn("px"); //7
    analysisManager->CreateNtupleDColumn("py"); //8
    analysisManager->CreateNtupleDColumn("pz"); //9
    analysisManager->CreateNtupleDColumn("kEne"); //10
    analysisManager->CreateNtupleDColumn("pMass"); //11
    analysisManager->CreateNtupleSColumn("ProcName"); //12
    analysisManager->FinishNtuple();
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::~RunAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// default mode
void RunAction::BeginOfRunAction(const G4Run*)
{
    // Get analysis manager
    auto analysisManager = G4AnalysisManager::Instance();
    // set output file name
    if (fOutputFileNamePtr == nullptr)
    {
        //single file mode
        G4String fileName = "bremOutput";
        G4cout << "Single File Mode: Setting the output file name: " << fileName << G4endl;
        analysisManager->SetFileName(fileName);
    }
    else
    {// batch mode
        G4cout << "Batch mode: Setting output file name: " << *fOutputFileNamePtr << G4endl;
        analysisManager->SetFileName(*fOutputFileNamePtr);
    }
    analysisManager->OpenFile();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::EndOfRunAction(const G4Run*)
{
    auto analysisManager = G4AnalysisManager::Instance();
    //write and close the file at the end of each run
    analysisManager->Write();
    analysisManager->CloseFile();
}
