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

void testMinHeap();
void testRedBlackTree();
vector<Command> getCommands(char* filename);
vector<string> split(string);

int main(int argc, char* argv[]) {
    char *filename = new char[100];
    strcpy(filename, argv[1]);
    vector<Command> cmds = getCommands(filename);
    for (Command c : cmds) {
        cout<<c.time<<" | "<<c.cmd<<" | "<<c.arg1<<" | "<<c.arg2<<endl;
    }

    int counter = 0;
    MinHeap<Building> *heap = new MinHeap<Building>();
    RedBlackTree<int, Building*> *rbtree = new RedBlackTree<int, Building*>();
    int currentNum = -1;
    int builtDays = 0;
    while (!(currentNum < 0 && counter > cmds[cmds.size() - 1].time)) {
        if (currentNum >= 0) {
            int nowBuildingIndex = heap->getIndexByElement(*rbtree->getValueByKey(currentNum));
            int newIndex = heap->increase(nowBuildingIndex, 1);
            rbtree->update(currentNum, heap->getElementPointer(newIndex));
            builtDays ++;
        }
        for (Command cmd : cmds) {
            if (cmd.time == counter) {
                if (cmd.cmd == "Insert") {
                    Building *b = new Building(cmd.arg1, 0, cmd.arg2);
                    heap->insert(b);
                    rbtree->insert(b->buildingNum, b);
                } else if (cmd.cmd == "PrintBuilding") {
                    if (cmd.arg2 == -1) {
                        Building *toPrint = rbtree->getValueByKey(cmd.arg1);
                        if (toPrint != nullptr) {
                            cout<<"("<<toPrint->buildingNum<<","<<toPrint->executedTime<<","<<toPrint->totalTime<<")"<<endl;
                        } else {
                            cout<<"(0,0,0)"<<endl;
                        }
                    } else {
                        // Print range
                    }
                } else {
                    // Illegal
                }
            } else if (cmd.time > counter) {
                break;
            }
        }
        if (currentNum > 0) {
            Building currentBuilding = *rbtree->getValueByKey(currentNum);
            if (currentBuilding.executedTime == currentBuilding.totalTime) {
                cout<<"("<<currentBuilding.buildingNum<<","<<counter<<")"<<endl;
                heap->removeElement(currentBuilding);
                rbtree->remove(currentBuilding.buildingNum);
                builtDays = 0;
                currentNum = -1;
            }
            if (builtDays == 5) {
                if (heap->getLength() != 0) {
                    currentNum = heap->getElement(1).buildingNum;
                } else {
                    currentNum = -1;
                }
                builtDays = 0;
            }
        }
        if (currentNum == -1 && heap->getLength() != 0) {
            currentNum = heap->getElement(1).buildingNum;
        }
        counter ++;
    }
    return 0;
}

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

void testMinHeap()
{
    MinHeap<int> minHeap = MinHeap<int>();
    int arr[11] = {
            37, 58, 91, 12, 43, 5, 84, 68, 99, 77, 29
    };
//    for (int i = 0; i < 11; ++i) {
//        minHeap.insert(arr[i]);
//        minHeap.print();
//    }
    minHeap.increase(1, 100);
    minHeap.print();
    minHeap.removeMin();
    minHeap.print();
    minHeap.remove(4);
    minHeap.print();
    minHeap.removeMin();
    minHeap.print();
    minHeap.removeMin();
    minHeap.print();
    minHeap.removeMin();
    minHeap.print();
    minHeap.remove(2);
    minHeap.print();
    minHeap.remove(3);
    minHeap.print();
}

void testRedBlackTree()
{
    RedBlackTree<int, int> tree = RedBlackTree<int, int>();
//    for (int i = 1; i <= 10000; ++i) {
//        tree.insert(i, i*10);
//        std::cout<<i<<','<<i*10<<" Inserted:"<<std::endl;
//    }
//    int *to_remove = new int[1000]();
//    for (int k = 0; k < 1000; ++k) {
//        to_remove[k] = k * 2 + 1;
//    }
//    for (int j = 0; j < 1000; ++j) {
//        tree.remove(to_remove[j]);
//        std::cout<<to_remove[j]<<" removed: ======================================="<<std::endl;
//    }
    tree.insert(0, 100);
    tree.insert(0, 101);
    std::cout<<"???"<<std::endl;
}