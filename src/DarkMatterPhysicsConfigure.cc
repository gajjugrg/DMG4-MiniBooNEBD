#include "DarkMatterPhysics.hh"

#include "DarkMatter.hh"
#include "DarkPhotons.hh"
#include "DarkScalars.hh"
#include "DarkPseudoScalars.hh"
#include "DarkAxials.hh"
#include "ALP.hh"
#include "DarkZ.hh"
#include "DarkPhotonsAnnihilation.hh"
#include "DarkScalarsAnnihilation.hh"
#include "DarkPseudoScalarsAnnihilation.hh"
#include "DarkAxialsAnnihilation.hh"
#include "DarkMatterParametersFactory.hh"

#include "G4SystemOfUnits.hh"

// BiasSigmaFactor Invisible mode Vector EThresh=35
// 900.  9.e12
// 16.7  8.e8
//  5.   1.75e8
//  2.   3.5e7
// 0.5   1.2e7
// 0.1   3.6e6
// 0.01  1.55e6
// 0.002 1.38e6

bool DarkMatterPhysics::DarkMatterPhysicsConfigure() 
{
  //call an instance of the class
  DarkMatterParametersFactory* DMpar = DarkMatterParametersFactory::GetInstance();
  DMpar->RegisterNewParam("BiasSigmaFactor0", 1e6);
  //DMpar->RegisterNewParam("EThresh", 35.); // for sensitivity calculations invisible mode
  DMpar->RegisterNewParam("EThresh", 10.1*MeV); // This is in MeV
  //G4double EThresh = 18; // for sensitivity calculations visible mode
  //G4double EThresh = 1.; // for shape studies
  //G4double EThresh = 2000.; // to turn off A emissions

  //select particle type and details
  DMpar->RegisterNewParam("DMProcessType", 1.); // 1: Vector, 2: Scalar, 3: Axial, 4: Pseudoscalar 5: spin 2, 21: ALP
  DMpar->RegisterNewParam("DMMass", 10.*MeV); // This is in MeV
  DMpar->RegisterNewParam("Epsilon", 1e-3); // default 0.1

  // Initialize for Iron (Fe)
  DMpar->RegisterNewParam("ANucl"      ,55.8451);
  DMpar->RegisterNewParam("ZNucl"      ,26.    );
  DMpar->RegisterNewParam("Density"    ,7.874*(g/cm3)  );

  DMpar->RegisterNewParam("DecayType", 0.); // 0 invisible, 2 visible

  // additional parameters for annihilation
  DMpar->RegisterNewParam("RDM", 1./3.);
  DMpar->RegisterNewParam("AlphaD", 0.5);
  return true;
}
