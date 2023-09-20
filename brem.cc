#include "DetectorConstruction.hh"
#include "ActionInitialization.hh"
#include "G4Version.hh"

// version dependent header files
#if G4VERSION_NUMBER != 1100
#include "G4MTRunManager.hh"  // for G4_10
#else
#include "G4RunManagerFactory.hh" // for G4_11
#endif

// Modification for the DMG4 extension
#include "G4PhysListFactory.hh"
#include "DarkMatterPhysics.hh"
#include "DarkMatter.hh"
#include "DarkMatterParametersFactory.hh"
// Modification ends here

#include "G4SteppingVerbose.hh"
#include "G4UImanager.hh"
#include "FTFP_BERT.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "G4Version.hh"

#include "Randomize.hh"

#include <unistd.h>
#include <cstdlib>

void print_usage(){
	G4cerr << "Usage: " << G4endl;
	G4cerr << "   -m [macro (input) file name]" << G4endl;
	G4cerr << "   -o [output (date) file name]" << G4endl;
	G4cerr << "   -s [random number randSeed]"  << G4endl;
}

int main(int argc,char** argv)
{
	int opt = 0;

	G4long randSeed = time(NULL); // here is where we set the seed
	G4UIExecutive* ui = nullptr;
	G4String macroFilename, dataFilename;
	const G4String* dataFilename_ptr = &dataFilename;
	while((opt = getopt(argc, argv, "m:o:s:"))!= -1) {
		switch(opt){
			case 'm':
				macroFilename = optarg;
				break;

			case 'o':
				dataFilename = optarg;
				break;

			case 's':
				randSeed = atol(optarg);
				break;

			case ':':
			case '?':
				print_usage();
				exit(EXIT_FAILURE);
				break;
		}
	}

	G4Random::setTheEngine(new CLHEP::MTwistEngine);
	G4Random::setTheSeed(randSeed);
	//  G4Random::showEngineStatus();


	// version dependent function call
#if G4VERSION_NUMBER == 1100
	G4int precision = 4;
	G4SteppingVerbose::UseBestUnit(precision);
#endif

	// Construct the default run manager
#ifdef G4MULTITHREADED
	G4MTRunManager* runManager = new G4MTRunManager;
	runManager->SetNumberOfThreads(2*(G4Threading::G4GetNumberOfCores()));
	G4cout << "Multithreaded" << G4endl;
#else
	G4RunManager* runManager = new G4RunManager;
	G4cout << "Single threaded" << G4endl;
#endif
	// Set mandatory initialization classes
	// Detector construction
	DetectorConstruction* detectorConstruction = new DetectorConstruction();
	runManager->SetUserInitialization(detectorConstruction);

	// Physics list
	/*
	   G4VModularPhysicsList* physicsList = new FTFP_BERT;
	   physicsList->SetVerboseLevel(1);
	   runManager->SetUserInitialization(physicsList);
	   */

	// Modified Physics List!!!
	G4PhysListFactory factory;
	G4VModularPhysicsList * phys = factory.GetReferencePhysList("FTFP_BERT");
	DarkMatterPhysics* darkMatterPhysics = new DarkMatterPhysics();
	DarkMatterParametersFactory* DMpar = DarkMatterParametersFactory::GetInstance();
	G4cout << "BiasSigmaFactor0 = " << DMpar->GetRegisteredParam("BiasSigmaFactor0") << G4endl;
	G4cout << "EThresh = " << DMpar->GetRegisteredParam("EThresh") << G4endl;
	G4cout << "DMProcessType = " << DMpar->GetRegisteredParam("DMProcessType") << G4endl;
	G4cout << "DMMass = " << DMpar->GetRegisteredParam("DMMass") << G4endl;
	G4cout << "Epsilon = " << DMpar->GetRegisteredParam("Epsilon") << G4endl;
	phys->RegisterPhysics(darkMatterPhysics);
	// Here the DMG4 modification ends ^^^
	runManager->SetUserInitialization(phys);  // init phys

	if(!dataFilename.empty()) {
		runManager->SetUserInitialization(new ActionInitialization(
							dataFilename_ptr,
							detectorConstruction,
							darkMatterPhysics->GetDarkMatterPointer()
							                  )
						 );
	}
	else {
		runManager->SetUserInitialization(new ActionInitialization());
	}

	// Initialize visualization
	G4VisManager* visManager = new G4VisExecutive;
	// G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
	// G4VisManager* visManager = new G4VisExecutive("Quiet");
	visManager->Initialize();

	G4cout << "Version: " << G4VERSION_NUMBER << G4endl;
	// Detect interactive mode (if no arguments) and define UI session
	// Get the pointer to the User Interface manager
	G4UImanager* UImanager = G4UImanager::GetUIpointer();

	if ( ! ui ) {
		// batch mode
		G4String command = "/control/execute ";
		//  G4String fileName = argv[1];
		UImanager->ApplyCommand(command+macroFilename);
	}
	else {
		//interactive mode
		ui = new G4UIExecutive(argc, argv);
		UImanager->ApplyCommand("/control/execute init_vis.mac");
		ui->SessionStart();
		delete ui;
	}
	delete visManager;
	delete runManager;
}

