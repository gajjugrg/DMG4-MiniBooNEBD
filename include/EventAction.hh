#ifndef BremEventAction_h
#define BremEventAction_h 1

#include "RunAction.hh"

#include "G4UserEventAction.hh"
#include "globals.hh"

/// Event action class
///

class DetectorConstruction;
class SteppingAction;
class DarkMatter;
class G4Event;
class RunAction;

class EventAction : public G4UserEventAction
{
    public:
        EventAction(/*RunAction* runAction*/);
        EventAction(RunAction* runAction, DetectorConstruction* detectorConstruction, DarkMatter* darkMatter);
        ~EventAction();

        void BeginOfEventAction(const G4Event* event);
        void EndOfEventAction(const G4Event* event);
        void SetSteppingAction(SteppingAction* steppingAction) {fSteppingAction = steppingAction;}
        DarkMatter* GetDarkMatterPointer(){return fDarkMatter;}
        void CountEmission() {NEmissions++;}

    private:
        RunAction* fRunAction;
        DetectorConstruction* fDetectorConstruction;
        SteppingAction* fSteppingAction;
        DarkMatter* fDarkMatter;
        G4int NEmissions;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif


