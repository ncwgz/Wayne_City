//
// Created by wangguozhi on 2019-11-22.
//
#include <iostream>

#ifndef WAYNE_CITY_BUILDING_H
#define WAYNE_CITY_BUILDING_H

#endif //WAYNE_CITY_BUILDING_H

using namespace std;

class Building {
private:

public:
    // Unique number of the building
    int buildingNum;
    // How many days have the building been built
    int executedTime;
    // How many days does the building needs to finish
    int totalTime;

    // Construct a building with give arguments
    Building(int buildingNum, int executedTime, int totalTime) {
        this->buildingNum = buildingNum;
        this->executedTime = executedTime;
        this->totalTime = totalTime;
    }

    // Construct a void building (when no building found)
    Building() {
        this->buildingNum = 0;
        this->executedTime = 0;
        this->totalTime = 0;
    }

    /* If the executed time of this building is greater or
     * if they have a same executed time but the number of
     * this building is greater, return true. Vice versa.
     * */
    bool operator > (const Building &b) {
        return (this->executedTime > b.executedTime)
               || (this->executedTime == b.executedTime
                   && this->buildingNum < b.buildingNum);
    }

    /* If the executed time of this building is smaller or
     * if they have a same executed time but the number of
     * this building is smaller, return true. Vice versa.
     * */
    bool operator < (const Building &b) {
        return this->executedTime < b.executedTime
               || (this->executedTime == b.executedTime
                   && this->buildingNum < b.buildingNum);
    }

    // Add delta to the executed time of this building
    Building operator + (int delta) {
        Building *building = new Building(this->buildingNum, this->executedTime+delta, this->totalTime);
        return *building;
    }

    // If they share the same building number, return true
    bool operator == (int toCompare) {
        if (this->buildingNum == toCompare) {
            return true;
        } else {
            return false;
        }
    }

    // If they share the same building number, return true
    bool operator == (const Building toCompare) {
        if (this->buildingNum == toCompare.buildingNum) {
            return true;
        } else {
            return false;
        }
    }
};