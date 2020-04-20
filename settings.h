#ifndef SETTINGS_H
#define SETTINGS_H

constexpr int boardRows = 10;			
constexpr int boardColumns = 10;

constexpr int fleetPoints = 10;

constexpr const char* stringUserType [6] {"Discard" ,"Scout", "Ubot", "Hybrid", "Destroyer", "Aircraft_carrier"};
constexpr int highestPossibleShipType = 5;	
constexpr int lowestPossibleShipType = 1;

const enum class shipType { Scout = 1, Ubot, Hybrid, Destroyer, Aircraft_carrier };

#endif