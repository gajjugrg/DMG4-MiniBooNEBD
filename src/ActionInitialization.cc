#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"
#include "DetectorConstruction.hh"
#include "DarkMatter.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ActionInitialization::ActionInitialization()
	: fOutputFileNamePtr(nullptr),
	fDetectorConstruction(nullptr),
	fDarkMatter(nullptr)
{}

ActionInitialization::ActionInitialization(const G4String* outputFileNamePtr, DetectorConstruction* detectorConstruction, DarkMatter* darkMatter)
	: fOutputFileNamePtr(outputFileNamePtr),
	fDetectorConstruction(detectorConstruction),
	fDarkMatter(darkMatter)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ActionInitialization::~ActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ActionInitialization::BuildForMaster() const
{
	RunAction* runAction;
	if( fOutputFileNamePtr != nullptr)
		runAction = new RunAction(fOutputFileNamePtr);
	else 
		runAction = new RunAction();
	SetUserAction(runAction);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ActionInitialization::Build() const
{
	SetUserAction(new PrimaryGeneratorAction());
	RunAction* runAction; 
	if (fOutputFileNamePtr != nullptr)
		runAction = new RunAction(fOutputFileNamePtr);
	else 
		runAction = new RunAction;
	SetUserAction(runAction);
	EventAction* eventAction = new EventAction(runAction, fDetectorConstruction, fDarkMatter);
	SetUserAction(eventAction);
	SetUserAction(new SteppingAction(eventAction));

}

