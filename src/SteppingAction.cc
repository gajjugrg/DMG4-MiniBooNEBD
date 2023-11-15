#include "SteppingAction.hh"
#include "EventAction.hh"
#include "DetectorConstruction.hh"
#include "G4Version.hh"
#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4Track.hh"

#if G4VERSION != 1100
#include "g4root.hh"
#else
#include "G4AnalysisManager.hh"
#endif

#include "DarkMatter.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

    SteppingAction::SteppingAction(EventAction* myEA)
: eventAction(myEA)
{
    eventAction->SetSteppingAction(this);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SteppingAction::UserSteppingAction(const G4Step* step)
{
    // Prepare analysis manager
    auto analysisManager = G4AnalysisManager::Instance();
    G4Track* track = step->GetTrack();
    if (step->GetPostStepPoint() -> GetProcessDefinedStep() !=0 ) {
        auto procName = step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
        if (procName.find(std::string("DMProcessDMBrem")) != std::string::npos){
            auto secondary = step -> GetSecondaryInCurrentStep();
            G4int parentID = track->GetDefinition()->GetPDGEncoding();
            auto p_pMass = track->GetDefinition()->GetPDGMass();
            auto p_px = track->GetMomentum().x();
            auto p_py = track->GetMomentum().y();
            auto p_pz = track->GetMomentum().z();
            auto p_kEne = track->GetKineticEnergy();

            size_t size_secondary = (*secondary).size();
            if (size_secondary) {
                for (size_t i = 0; i <(size_secondary); i++){
                    auto secstep = (*secondary)[i];
                    auto kEne = secstep->GetKineticEnergy();
                    G4int pID = secstep->GetDefinition()->GetPDGEncoding();
                    auto pMass = secstep->GetDefinition()->GetPDGMass();
                    auto  px = secstep-> GetMomentum().x();
                    auto  py = secstep-> GetMomentum().y();
                    auto pz = secstep-> GetMomentum().z();
                    analysisManager->FillNtupleIColumn(0, parentID);
                    analysisManager->FillNtupleIColumn(1, pID);                 
                    analysisManager->FillNtupleDColumn(2, p_px/CLHEP::MeV);
                    analysisManager->FillNtupleDColumn(3, p_py/CLHEP::MeV);
                    analysisManager->FillNtupleDColumn(4, p_pz/CLHEP::MeV);
                    analysisManager->FillNtupleDColumn(5, p_kEne/CLHEP::MeV);
                    analysisManager->FillNtupleDColumn(6, p_pMass/CLHEP::MeV);

                    analysisManager->FillNtupleDColumn(7, px/CLHEP::MeV);
                    analysisManager->FillNtupleDColumn(8, py/CLHEP::MeV);
                    analysisManager->FillNtupleDColumn(9, pz/CLHEP::MeV);
                    analysisManager->FillNtupleDColumn(10, kEne/CLHEP::MeV);
                    analysisManager->FillNtupleDColumn(11, pMass/CLHEP::MeV);
                    analysisManager->FillNtupleSColumn(12, procName);
                    analysisManager->AddNtupleRow();
                }
            }
        }
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void SteppingAction::Reset()
{
    eventAction->GetDarkMatterPointer()->ResetNEmissions();
}


void SteppingAction::Finalize()
{
}
