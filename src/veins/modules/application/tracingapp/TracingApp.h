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

#ifndef __VEINS_MYVEINSAPP_H_
#define __VEINS_MYVEINSAPP_H_

#include <omnetpp.h>
#include "veins/modules/application/ieee80211p/BaseWaveApplLayer.h"

#define TRACING_SEPARATOR ','
#define TRACING_QUOTECHAR '\"'

using namespace omnetpp;

/**
 * @brief
 * This is an example file that tracks data and exports it in a format
 * that is compatible with Maat.
 *
 * @author Rens van der Heijden
 *
 */

class TracingApp : public BaseWaveApplLayer {
    private:
        std::string traceRcvFile;
        std::string traceSendFile;

    public:
        virtual void initialize(int stage);
        virtual void finish();
    protected:
        virtual void onBSM(BasicSafetyMessage* bsm);
        virtual void onWSM(WaveShortMessage* wsm);
        virtual void onWSA(WaveServiceAdvertisment* wsa);

        virtual void handleSelfMsg(cMessage* msg);
        virtual void populateWSM(WaveShortMessage* wsm, int rcvId, int serial);
        virtual void handlePositionUpdate(cObject* obj);

        virtual const int getMyID() const;
        virtual const Coord getMyPosition() const;
        virtual const double getMySpeed() const;
        virtual const double getAngle() const;
        //getMetaData is meta-data included with every output
        virtual const std::string getMetaData() const;
        //create trace output (only created when createTrace is set)
        //virtual const void traceStep(std::string additional) const;
        virtual const void traceSend(std::string msgID, std::string data, std::string noise, std::string attacker) const;
        virtual const void traceRcv(std::string msgID, std::string senderID, std::string data) const;
    };

#endif
