#ifndef BremRunAction_h
#define BremRunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"
#include "G4Version.hh"

#include "g4root.hh" 
class G4Run;

class RunAction : public G4UserRunAction
{
  public:
    RunAction();
    RunAction(const G4String* outputFileNamePtr);
    virtual ~RunAction();

    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);
    
private:
    const G4String* fOutputFileNamePtr;
};

#endif

