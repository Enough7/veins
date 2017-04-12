/*
 * AttackerApp.h
 *
 *  Created on: 06.03.2017
 *      Author: Florian
 */


#ifndef __VEINS_ATTACKERAPP_H_
#define __VEINS_ATTACKERAPP_H_

#include <omnetpp.h>
#include <string>
#include "veins/modules/application/tracingapp/TracingApp.h"
#include "veins/modules/application/ieee80211p/BaseWaveApplLayer.h"
#include "veins/base/utils/FindModule.h"
#include "veins/base/modules/BaseWorldUtility.h"

#define ATTACKER_TYPE_NO_ATTACKER 0
#define ATTACKER_TYPE_CONST_POSITION 1
#define ATTACKER_TYPE_DYNAMIC_POSITION 2
#define ATTACKER_TYPE_RANDOM_POSITION 4
#define ATTACKER_TYPE_RANDOM_DYNAMIC_POSITION 8
#define ATTACKER_TYPE_STAY_AT_POSITION 16

using namespace omnetpp;

class AttackerApp : public TracingApp
{
    private:
        static int attackerTypesCount;
        static std::vector<double> attackerTypeProbability;
        static long currentAttackerCount;
        static BaseWorldUtility *world;
        bool attacker;
        double attackerPosRangeMin;
        double attackerPosRangeMax;
        Coord position;
        int attackerType;
        std::string traceJSONFile;
        std::string traceGroundTruthJSONFile;

    public:
        virtual void initialize(int stage);
    protected:
        virtual void handleSelfMsg(cMessage* msg);
        virtual void populateWSM(WaveShortMessage* wsm, int rcvId=0, int serial=0);
        virtual void attackBSM(BasicSafetyMessage* bsm);
        virtual void attackSetConstPosition(BasicSafetyMessage* bsm);
        virtual void attackSetConstPosition(BasicSafetyMessage* bsm, double xPos, double yPos);
        virtual void attackSetDynamicPosition(BasicSafetyMessage* bsm);
        virtual void attackSetDynamicPosition(BasicSafetyMessage* bsm, double xPos, double yPos);
        virtual void attackSetRandomPosition(BasicSafetyMessage* bsm);
        virtual void attackSetRandomDynamicPosition(BasicSafetyMessage* bsm);
        virtual void attackerSetCurrentPosition(BasicSafetyMessage* bsm);
        virtual Coord getRandomPosition();
        virtual Coord getRandomPositionInRange();
        virtual int getRandomAttackerType();
};

int AttackerApp::attackerTypesCount = -1;
std::vector<double> AttackerApp::attackerTypeProbability;
long AttackerApp::currentAttackerCount = 0;
BaseWorldUtility* AttackerApp::world = NULL;

#endif
