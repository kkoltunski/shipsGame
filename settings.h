/*****************************************************************//**
 * \file   settings.h
 * \brief  Header with settings variables and magic numbers used as parameters in software
 * 
 * \author kkoltunski
 * \date   April 2020
***********************************************************************/

#ifndef SETTINGS_H
#define SETTINGS_H
///Boards magic numbers.
enum boardMagicNumbers { boardRows = 10, boardColumns = 10, alphabetSize = 26};

///Fleets magic numbers.
enum fleetMagicNumbers { fleetPoints = 10 , maximumPlayerNumber = 2};

///Ships magic numbers.
enum shipsMagicNumbers { highestPossibleShipType = 5, lowestPossibleShipType = 1};

///Offsets, chars etc magic numbers.
enum charsMagicNumbers : char {alphabetFirstChar = 'A', alphabetLastChar = 'Z', horizontal = 'H', vertical = 'V'};
///Ships type using in shipyard.h
enum class shipType { Scout = 1, Ubot, Hybrid, Destroyer, Aircraft_carrier };

///Options which are shown when user should choose ship type
constexpr const char* stringUserType [6] {"Discard" ,"Scout", "Ubot", "Hybrid", "Destroyer", "Aircraft_carrier"};

#endif