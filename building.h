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
    int buildingNum;
    int executedTime;
    int totalTime;

    Building(int buildingNum, int executedTime, int totalTime) {
        this->buildingNum = buildingNum;
        this->executedTime = executedTime;
        this->totalTime = totalTime;
    }

    Building() {
        this->buildingNum = 0;
        this->executedTime = 0;
        this->totalTime = 0;
    }

    bool operator > (const Building &b) {
        if (this->executedTime > b.executedTime) {
            return true;
        } else if (this->executedTime == b.executedTime) {
            if (this->buildingNum > b.executedTime) {
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    bool operator < (const Building &b) {
        if (this->executedTime < b.executedTime) {
            return true;
        } else if (this->executedTime == b.executedTime) {
            if (this->buildingNum < b.buildingNum) {
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    Building operator + (int delta) {
        Building *building = new Building(this->buildingNum, this->executedTime+delta, this->totalTime);
        return *building;
    }

    bool operator == (int toCompare) {
        if (this->buildingNum == toCompare) {
            return true;
        } else {
            return false;
        }
    }

    bool operator == (const Building toCompare) {
        if (this->buildingNum == toCompare.buildingNum) {
            return true;
        } else {
            return false;
        }
    }
};