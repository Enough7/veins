#include "AttackerApp.h"

Define_Module(AttackerApp);

void AttackerApp::initialize(int stage) {
    TracingApp::initialize(stage);
    if (stage == 0) {
        // initialize
        EV << "Initializing attacker" << std::endl;
        attacker = false;
        attackerPosRangeMin = par("attackerPosRangeMin").doubleValue();
        attackerPosRangeMax = par("attackerPosRangeMax").doubleValue();

        long attackerMaxCount = par("attackerMaxCount").longValue();
        if((attackerMaxCount < 0) || (attackerCount < attackerMaxCount)) {
            // code is based on src/veins/modules/application/ldm/LDMApp.cc from branch alaa-al-momani-thesis
            double attackerProbability = par("attackerProbability").doubleValue();
            if((attackerProbability < 0 && attackerCount == 0) // < 0 means *exactly one* attacker.
                    || (attackerProbability > 0)) {
                attacker = (dblrand() <= std::abs(attackerProbability));
                if(attacker) {
                    attackerCount++;
                }
            }
        }
    }
}

void AttackerApp::handleSelfMsg(cMessage* msg) {
    // code is based on BaseWaveApplLayer::handleSelfMsg(cMessage* msg)
    switch (msg->getKind()) {
        case SEND_BEACON_EVT: {
            BasicSafetyMessage* bsm = new BasicSafetyMessage();
            populateWSM(bsm);

            // attacker
            if (attacker) {
                attackBSM(bsm);
            }

            sendDown(bsm);
            scheduleAt(simTime() + beaconInterval, sendBeaconEvt);
            break;
        }
        case SEND_WSA_EVT:   {
            WaveServiceAdvertisment* wsa = new WaveServiceAdvertisment();
            populateWSM(wsa);

            // add attacks for WSA messages here (currently no attacks)

            sendDown(wsa);
            scheduleAt(simTime() + wsaInterval, sendWSAEvt);
            break;
        }
        default: {
            if (msg)
                DBG_APP << "APP: Error: Got Self Message of unknown kind! Name: " << msg->getName() << endl;
            break;
        }
    }
}

// code is based on TracingApp::populateWSM(WaveShortMessage* wsm, int rcvId, int serial)
void AttackerApp::populateWSM(WaveShortMessage* wsm, int rcvId, int serial) {
    BaseWaveApplLayer::populateWSM(wsm, rcvId, serial);
    if (BasicSafetyMessage* bsm = dynamic_cast<BasicSafetyMessage*>(wsm)) {
        Coord pos = bsm->getSenderPos();
        std::stringstream tmp; tmp << pos.x << ", " << pos.y << ", " << pos.z;
        traceSend(std::to_string(bsm->getTreeId()), tmp.str(), std::to_string(0), attacker ? "true" : "false");
    }
}

//TODO: implement more attacker
void AttackerApp::attackBSM(BasicSafetyMessage* bsm) {
    int attackerType = par("attackerType").longValue();

    switch(attackerType)
    {
    case ATTACKER_TYPE_CONST_POSITION:
        attackSetConstPosition(bsm);
        break;
    case ATTACKER_TYPE_DYNAMIC_POSITION:
        attackSetDynamicPosition(bsm);
        break;
    case ATTACKER_TYPE_RANDOM_POSITION:
        attackSetRandomPosition(bsm);
        break;
    case ATTACKER_TYPE_RANDOM_DYNAMIC_POSITION:
        attackSetRandomDynamicPosition(bsm);
        break;
    default:
        DBG_APP << "Unknown attacker type! Type: " << attackerType << endl;
    }
}

void AttackerApp::attackSetConstPosition(BasicSafetyMessage* bsm) {
    attackSetConstPosition(bsm, par("attackerXPos").doubleValue(), par("attackerYPos").doubleValue());
}

void AttackerApp::attackSetConstPosition(BasicSafetyMessage* bsm, double xPos, double yPos) {
    DBG_APP << "Attack: SetConstPosition (x=" << xPos << ", y=" << yPos << ")" << std::endl;
    bsm->setSenderPos(Coord(xPos, yPos, (bsm->getSenderPos()).z));
}

void AttackerApp::attackSetDynamicPosition(BasicSafetyMessage* bsm) {
    attackSetDynamicPosition(bsm, par("attackerXPos").doubleValue(), par("attackerYPos").doubleValue());
}

void AttackerApp::attackSetDynamicPosition(BasicSafetyMessage* bsm, double xPos, double yPos) {
    double newXPos = (bsm->getSenderPos()).x + xPos;
    double newYPos = (bsm->getSenderPos()).y + yPos;

    DBG_APP << "Attack: SetDynamicPosition (x=" << newXPos << ", y=" << newYPos << ")" << std::endl;
    bsm->setSenderPos(Coord(newXPos, newYPos, (bsm->getSenderPos()).z));
}

void AttackerApp::attackSetRandomPosition(BasicSafetyMessage* bsm){
    Coord randomPosition = getRandomPosition();
    attackSetConstPosition(bsm, randomPosition.x, randomPosition.y);
}

void AttackerApp::attackSetRandomDynamicPosition(BasicSafetyMessage* bsm) {
    Coord randomPositionInRange = getRandomPositionInRange();
    attackSetDynamicPosition(bsm, randomPositionInRange.x, randomPositionInRange.y);
}

Coord AttackerApp::getRandomPosition() {
    if(world == NULL) {
        world = FindModule<BaseWorldUtility*>::findGlobalModule();
    }
    return world->getRandomPosition();
}

Coord AttackerApp::getRandomPositionInRange() {
    return Coord(uniform(attackerPosRangeMin, attackerPosRangeMax), uniform(attackerPosRangeMin, attackerPosRangeMax));
}
