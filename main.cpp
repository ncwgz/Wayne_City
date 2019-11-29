#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include "minheap.h"
#include "redblacktree.h"
#include "building.h"

using namespace std;

typedef struct Command {
    int time;
    string cmd;
    int arg1;
    int arg2;
};

// Get commands from the input file
vector<Command> getCommands(char* filename);
// Clear output file if it exists
void initOutputFile();
// Write message into the end of the file with a new line.
void writeIntoFile(string msg);

int main(int argc, char* argv[]) {
    initOutputFile(); // Init output file

    char *filename = new char[100];
    strcpy(filename, argv[1]); // Get filename from arguments
    vector<Command> cmds = getCommands(filename); // Get commands from input file

    int counter = 0; // The timer
    /*
     * Use a min heap to store the buildings.
     */
    MinHeap<Building> *heap = new MinHeap<Building>();
    /*
     * Use a red black tree to store the pointers of the buildings.
     * Use building number as the key.
     */
    RedBlackTree<int, Building*> *rbtree = new RedBlackTree<int, Building*>();
    // The building number of the current building, -1 when no building is being constructing
    int currentNum = -1;
    // How many days has the current building been built in this single period (not totally)
    int builtDays = 0;
    // Stop when no building is being built and all commands have been performed
    while (!(currentNum < 0 && counter > cmds[cmds.size() - 1].time)) {
        // We have a building to construct today!
        if (currentNum >= 0) {
            // Get the building by building num from tree
            Building *thisBuilding = rbtree->getValueByKey(currentNum);
            int nowBuildingIndex = heap->getIndexByElement(*thisBuilding);
            // Increase its executed time by 1
            int newIndex = heap->increase(nowBuildingIndex, 1);
            // Also the its past days
            builtDays ++;
        }
        // See if we have a command for today
        for (Command cmd : cmds) {
            // We have one
            if (cmd.time == counter) {
                // Insert command
                if (cmd.cmd == "Insert") {
                    // Construct a new building and set its executed time to 0
                    Building *b = new Building(cmd.arg1, 0, cmd.arg2);
                    // Insert the new buliding to the heap
                    heap->insert(b);
                    // Insert the new building to the tree
                    rbtree->insert(b->buildingNum, b);
                }
                // PrintBuilding command
                else if (cmd.cmd == "PrintBuilding") {
                    // Only one argument, search a single building
                    if (cmd.arg2 == -1) {
                        Building *toPrint = rbtree->getValueByKey(cmd.arg1);
                        // Some building found
                        if (toPrint != nullptr) {
                            // Write it into the output
                            string toWrite = "(" + to_string(toPrint->buildingNum) + "," + to_string(toPrint->executedTime) + "," + to_string(toPrint->totalTime) + ")";
                            writeIntoFile(toWrite);
                        }
                        // No building found
                        else {
                            // Write a void building into output
                            writeIntoFile("(0,0,0)");
                        }
                    }
                    // Search buildings with a range
                    else {
                        // Use a vector to store the results
                        vector<Building*> v;
                        v = rbtree->getValuesByRange(cmd.arg1, cmd.arg2);

                        string toWrite = "";
                        for (int i = 0; i < v.size() - 1; ++i) { // Except the last one
                            if (v[i]->executedTime != v[i]->totalTime) {
                                cout << "(" << v[i]->buildingNum << "," << v[i]->executedTime << "," << v[i]->totalTime
                                     << "),";
                                toWrite +=
                                        "(" + to_string(v[i]->buildingNum) + "," + to_string(v[i]->executedTime) + "," +
                                        to_string(v[i]->totalTime) + "),";
                            }
                        }
                        // Add the last one, but with no comma
                        int last = v.size()-1;
                        toWrite += "(" + to_string(v[last]->buildingNum) + "," + to_string(v[last]->executedTime) + "," + to_string(v[last]->totalTime) + ")";
                        // Write them into output
                        writeIntoFile(toWrite);
                    }
                }
            } else if (cmd.time > counter) {
                break;
            }
        }
        // We have constructed some building today
        if (currentNum > 0) {
            Building currentBuilding = *rbtree->getValueByKey(currentNum);
            // The building has been finished
            if (currentBuilding.executedTime == currentBuilding.totalTime) {
                string toWrite = "(" + to_string(currentBuilding.buildingNum) + "," + to_string(counter) + ")";
                writeIntoFile(toWrite);
                heap->removeElement(currentBuilding);
                rbtree->remove(currentBuilding.buildingNum);

                builtDays = 0;
                currentNum = -1;
            }
            // The building has not finished but has been built for 5 days in this period
            if (builtDays == 5) {
                currentNum = -1;
                builtDays = 0;
            }
        }
        // We need to decide the building for tomorrow
        if (currentNum == -1 && heap->getLength() != 0) {
            currentNum = heap->getElement(1).buildingNum;
        }
        // One day has past
        counter ++;
    }
    return 0;
}

// Get commands from the input file
vector<Command> getCommands(char* filename) {
    fstream txt;
    txt.open(filename, ios::in);
    vector<string> cmds;
    string cmd;
    while (getline(txt, cmd)) {
        cmds.push_back(cmd);
    }
    vector<Command> commands;
    for (string cmd : cmds) {
        string time, command, arg1, arg2;
        int phase = 1;
        for (char c : cmd) {
            string s(1, c);
            switch (phase) {
                case 1: {
                    if (s != ":" && s != " ") {
                        time += s;
                    } else if (s == " ") {
                        phase ++;
                    }
                    break;
                }
                case 2: {
                    if (s != "(") {
                        command += s;
                    } else {
                        phase ++;
                    }
                    break;
                }
                case 3: {
                    if (s != "," && s != ")") {
                        arg1 += s;
                    } else if (s == ")") {
                        arg2 = "-1";
                        phase = 5;
                    } else {
                        phase ++;
                    }
                    break;
                }
                case 4: {
                    if (s != ")") {
                        arg2 += s;
                    } else {
                        phase ++;
                    }
                    break;
                }
                case 5: {
                    break;
                }
            }
        }
        Command c = Command();
        c.time = stoi(time);
        c.cmd = command;
        c.arg1 = stoi(arg1);
        c.arg2 = stoi(arg2);
        commands.push_back(c);
    }
    return commands;
}
// Clear output file if it exists
void initOutputFile() {
    ofstream file;
    file.open("output.txt", ios::out | ios::trunc);
    file<<"";
    file.close();
}
// Write message into the end of the file with a new line.
void writeIntoFile(string msg) {
    ofstream file;
    file.open("output_file.txt", ios::out | ios::app);
    file<<msg<<endl;
    file.close();
}