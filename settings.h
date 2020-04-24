/*****************************************************************//**
 * \file   settings.h
 * \brief  Header with settings variables and magic numbers used as parameters in software
 * 
 * \author kkoltunski
 * \date   April 2020
***********************************************************************/

#ifndef SETTINGS_H
#define SETTINGS_H

///Rows in boards
constexpr int boardRows = 10;
///columns in boards
constexpr int boardColumns = 10;

///Player points
constexpr int fleetPoints = 10;

///Options which are shown when user should choose ship type
constexpr const char* stringUserType [6] {"Discard" ,"Scout", "Ubot", "Hybrid", "Destroyer", "Aircraft_carrier"};

///Maximum ship type
constexpr int highestPossibleShipType = 5;	
///Minimum ship type
constexpr int lowestPossibleShipType = 1;
///Ships type using in shipyard.h
enum class shipType { Scout = 1, Ubot, Hybrid, Destroyer, Aircraft_carrier };

#endif