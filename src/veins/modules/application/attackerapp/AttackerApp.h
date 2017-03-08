/*
 * AttackerApp.h
 *
 *  Created on: 06.03.2017
 *      Author: Florian
 */


#ifndef __VEINS_ATTACKERAPP_H_
#define __VEINS_ATTACKERAPP_H_

#include <omnetpp.h>
#include "veins/modules/application/tracingapp/TracingApp.h"
#include "veins/modules/application/ieee80211p/BaseWaveApplLayer.h"

#define ATTACKER_TYPE_CONST_POSITION 0

using namespace omnetpp;

class AttackerApp : public TracingApp
{
    private:
        bool attacker;
        static long attackerCount;
    public:
        virtual void initialize(int stage);
    protected:
        virtual void handleSelfMsg(cMessage* msg);
        virtual void populateWSM(WaveShortMessage* wsm, int rcvId=0, int serial=0);
        virtual void attackBSM(BasicSafetyMessage* bsm);
        virtual void attackSetConstPosition(BasicSafetyMessage* bsm);
};

long AttackerApp::attackerCount = 0;

#endif
