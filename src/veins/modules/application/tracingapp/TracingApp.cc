//
// Copyright (C) 2016 David Eckhoff <david.eckhoff@fau.de>
//
// Documentation for these modules is at http://veins.car2x.org/
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//

#include "TracingApp.h"

Define_Module(TracingApp);

//const void TracingApp::traceStep(std::string additional) const {
//    std::ofstream tracefile;
//    tracefile.open(traceFile, std::ios_base::app);
//    if(tracefile.is_open()){
//        tracefile << getMyID() << ";" <<  getMyPosition() << ";" << simTime() << ";"  << additional << ";" << getMetaData() << std::endl;
//    }else{
//        std::cout << getMyID() << ";" <<  getMyPosition() << ";" << simTime() << ";"  << additional << ";" << getMetaData() << std::endl;
//    }
//    tracefile.close();
//}


const void TracingApp::traceRcv(std::string msgID, std::string senderID, std::string data) const {
    std::ofstream out_stream;
    out_stream.open(traceRcvFile, std::ios_base::app);
    if(out_stream.is_open())
        out_stream <<
          "\"" << getMyID() << "\"," <<
          "\"" << msgID << "\"," <<
          "\"" << senderID << "\"," <<
          "\"" << data << "\"" << std::endl;
    else
        DBG_APP << "Warning, tracing stream for sending is closed";
    out_stream.close();
}

const void TracingApp::traceSend(std::string msgID, std::string data, std::string noise, std::string attacker) const {
    std::ofstream out_stream;
    out_stream.open(traceSendFile, std::ios_base::app);
    if(out_stream.is_open())
        out_stream <<
          "\"" << getMyID() << "\"," <<
          "\"" << msgID << "\"," <<
          "\"" << data << "\"," <<
          "\"" << noise << "\"," <<
          "\"" << attacker << "\"" << std::endl;
    else
        DBG_APP << "Warning, tracing stream for sending is closed";
    out_stream.close();
}

const int TracingApp::getMyID() const {
    return getParentModule()->getIndex(); //Car.ned's index.
}

const Coord TracingApp::getMyPosition() const {
    return mobility->getPositionAt(simTime());
}

const double TracingApp::getMySpeed() const {
    return mobility->getSpeed();
}

const double TracingApp::getAngle() const {
    return mobility->getAngleRad();
}

const std::string TracingApp::getMetaData() const {
    return "";
}



void TracingApp::initialize(int stage) {
    BaseWaveApplLayer::initialize(stage);
    if (stage == 0) {
        //Initializing members and pointers of your application goes here
        EV << "Initializing " << par("appName").stringValue() << std::endl;
        std::ostringstream out_rcv; out_rcv << par("traceRcvFile").stdstringValue() << getMyID() << ".csv";
        traceRcvFile = out_rcv.str();

        //open immediately, because this file is separate for every vehicle
        //traceRcvStream.open(out_rcv.str(), std::ios_base::app);

        std::ostringstream out_send; out_send << par("traceSendFile").stdstringValue() << ".csv";
        traceSendFile = out_send.str();
    }
    else if (stage == 1) {
        //Initializing members that require initialized other modules goes here

    }
}

void TracingApp::finish() {
    BaseWaveApplLayer::finish();
    //statistics recording goes here

}

void TracingApp::onBSM(BasicSafetyMessage* bsm) {
    //Your application has received a beacon message from another car or RSU
    //code for handling the message goes here
    traceRcv(std::to_string(bsm->getTreeId()), std::to_string(bsm->getSenderAddress()), "");
}

void TracingApp::onWSM(WaveShortMessage* wsm) {
    //Your application has received a data message from another car or RSU
    //code for handling the message goes here, see TraciDemo11p.cc for examples

}

void TracingApp::onWSA(WaveServiceAdvertisment* wsa) {
    //Your application has received a service advertisement from another car or RSU
    //code for handling the message goes here, see TraciDemo11p.cc for examples

}

void TracingApp::handleSelfMsg(cMessage* msg) {
    BaseWaveApplLayer::handleSelfMsg(msg);
    //this method is for self messages (mostly timers)
    //it is important to call the BaseWaveApplLayer function for BSM and WSM transmission
}

void TracingApp::populateWSM(WaveShortMessage* wsm, int rcvId, int serial){
    BaseWaveApplLayer::populateWSM(wsm, rcvId, serial);
    if(BasicSafetyMessage* bsm = dynamic_cast<BasicSafetyMessage*>(wsm)){
        //TODO parse data
        traceSend(std::to_string(bsm->getTreeId()), "", std::to_string(0), "false");
    }
}

void TracingApp::handlePositionUpdate(cObject* obj) {
    BaseWaveApplLayer::handlePositionUpdate(obj);
    //the vehicle has moved. Code that reacts to new positions goes here.
    //member variables such as currentPosition and currentSpeed are updated in the parent class

}
