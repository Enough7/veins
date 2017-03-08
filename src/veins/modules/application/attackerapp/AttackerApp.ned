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

package org.car2x.veins.modules.application.attackerapp;
import org.car2x.veins.modules.application.tracingapp.TracingApp;

//
// network description file for your Veins Application. Add parameters here
//
simple AttackerApp extends TracingApp
{
    @class(AttackerApp);
    double attackerProbability = default(0);    // probability that a node is an attacker
                                                // attackerProbability < 0: 1 attacker
                                                
    int attackerMaxCount = default(-1);         // it's aimed to reach attackerMaxCount, but the effective number of attackers can be higher or lower
                                                // attackerMaxCount < 0: no attacker limit
                                                
    int attackerType = default(0);				// specifies the attacker type
                                                // 0: sets the position in BSMs to a const value (can be specified in the parameters attackerXPos and attackerYPos)
                                                // 1: sets the position in BSMs to a dynamic value (newXPos = xPos + attackerXPos, newYPos = yPos + attackerYPos)
                                                
    double attackerXPos = default(0);           // x coordinate of the attacker (in BSMs)
    double attackerYPos = default(0);           // y coordinate of the attacker (in BSMs)

}
