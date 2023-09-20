#ifndef BremSteppingAction_h
#define BremSteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

/// Stepping action class
///

class G4LogicalVolume;
class DetectorConstruction;
class EventAction;

class SteppingAction : public G4UserSteppingAction
{
    public:
        SteppingAction(EventAction* myEA);
        virtual ~SteppingAction(){};

        // method from the base class
        virtual void UserSteppingAction(const G4Step* step);

        virtual void Reset();

        virtual void Finalize();

    private:
        EventAction* eventAction;
};

#endif
