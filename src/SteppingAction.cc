#include "SteppingAction.hh"
#include "EventAction.hh"
#include "DetectorConstruction.hh"
#include "G4Version.hh"
#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4Track.hh"
#include "g4root.hh"

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
    G4StepPoint* SPointPreStep = step->GetPreStepPoint();
    G4StepPoint* SPointPostStep = step->GetPostStepPoint();
    G4Track* track = step->GetTrack();
    if (SPointPostStep-> GetProcessDefinedStep() !=0 ) {
        auto procName = SPointPostStep->GetProcessDefinedStep()->GetProcessName();
        if (procName.find(std::string("DMProcess")) != std::string::npos){
            auto secondary = step -> GetSecondaryInCurrentStep();
            G4int parentID = track->GetDefinition()->GetPDGEncoding();
            auto p_pMass = track->GetDefinition()->GetPDGMass();
            auto p_px = SPointPreStep->GetMomentum().x();
            auto p_py = SPointPreStep->GetMomentum().y();
            auto p_pz = SPointPreStep->GetMomentum().z();
            auto p_kinEne = SPointPreStep->GetKineticEnergy();

            size_t size_secondary = (*secondary).size();
            if (size_secondary) {
                for (size_t i = 0; i <(size_secondary); i++){
                    auto secstep = (*secondary)[i];
                    auto kinEne = secstep->GetKineticEnergy();
                    G4int pID = secstep->GetDefinition()->GetPDGEncoding();
                    auto pMass = secstep->GetDefinition()->GetPDGMass();
                    auto px = secstep-> GetMomentum().x();
                    auto py = secstep-> GetMomentum().y();
                    auto pz = secstep-> GetMomentum().z();
                    analysisManager->FillNtupleIColumn(1, parentID);
                    analysisManager->FillNtupleIColumn(2, pID);
                    analysisManager->FillNtupleSColumn(3, procName);
                    analysisManager->FillNtupleDColumn(4, p_px/CLHEP::MeV);
                    analysisManager->FillNtupleDColumn(5, p_py/CLHEP::MeV);
                    analysisManager->FillNtupleDColumn(6, p_pz/CLHEP::MeV);
                    analysisManager->FillNtupleDColumn(7, p_kinEne/CLHEP::MeV);
                    analysisManager->FillNtupleDColumn(8, p_pMass/CLHEP::MeV);
                    analysisManager->FillNtupleDColumn(9, px/CLHEP::MeV);
                    analysisManager->FillNtupleDColumn(10, py/CLHEP::MeV);
                    analysisManager->FillNtupleDColumn(11, pz/CLHEP::MeV);
                    analysisManager->FillNtupleDColumn(12, kinEne/CLHEP::MeV);
                    analysisManager->FillNtupleDColumn(13, pMass/CLHEP::MeV);
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
