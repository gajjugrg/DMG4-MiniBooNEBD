#include "EventAction.hh"
#include "RunAction.hh"
#include "SteppingAction.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"

#include "DarkMatter.hh"
#include "DetectorConstruction.hh"

//// version dependent header files
#if G4VERSION_NUMBER != 1100
#include "g4root.hh"  // G4_10
#else
#include "G4AnalysisManager.hh"  // G4_11
#endif

#include "G4UnitsTable.hh"

#include "Randomize.hh"
#include <iomanip>
#include <fstream>
#include <chrono>
#include <ctime>
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::EventAction()
{}

EventAction::EventAction(
        RunAction* runAction,
        DetectorConstruction* detectorConstruction,
        DarkMatter* darkMatter
        ) : fRunAction(runAction), fDetectorConstruction(detectorConstruction), fDarkMatter(darkMatter), NEmissions(0)
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// MODIFICATION STARTS!
EventAction::~EventAction()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::BeginOfEventAction(const G4Event*)
{
    fSteppingAction->Reset();
    fDetectorConstruction->SetAEmission(0);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::EndOfEventAction(const G4Event*)
{
    fSteppingAction->Finalize();
}
// MODIFICATION ENDS!


