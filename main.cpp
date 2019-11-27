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
void testRedBlackTree2();
vector<Command> getCommands(char* filename);
vector<string> split(string);

//int main() {
//    testRedBlackTree2();
//    return 0;
//}

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
            Building *thisBuilding = rbtree->getValueByKey(currentNum);
            int nowBuildingIndex = heap->getIndexByElement(*thisBuilding);
            int newIndex = heap->increase(nowBuildingIndex, 1);
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
                        vector<Building*> v;
                        v = rbtree->getValuesByRange(cmd.arg1, cmd.arg2);
                        for (int i = 0; i < v.size() - 1; ++i) {
                            cout<<"("<<v[i]->buildingNum<<","<<v[i]->executedTime<<","<<v[i]->totalTime<<")"<<",";
                        }
                        int last = v.size()-1;
                        cout<<"("<<v[last]->buildingNum<<","<<v[last]->executedTime<<","<<v[last]->totalTime<<")"<<endl;
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
//                if (heap->getLength() != 0) {
//                    currentNum = heap->getElement(1).buildingNum;
//                } else {
//                    currentNum = -1;
//                }
                currentNum = -1;
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

void testRedBlackTree()
{
    cout<<"==============Testing red black tree=============="<<endl;
    // Initialize a red black tree with numbers from 1 to 2049
    RedBlackTree<int, int> tree = RedBlackTree<int, int>();
    for (int i = 1; i <= 2049; ++i) {
        tree.insert(i, i*10);
    }

    cout<<"Expecting: 40"<<endl;
    cout<<tree.getValueByKey(4)<<endl;

    cout<<"Expecting: 5120"<<endl;
    cout<<tree.getValueByKey(512)<<endl;

    cout<<"Expecting: 10"<<endl;
    cout<<tree.getValueByKey(1)<<endl;

    cout<<"Expecting: 0"<<endl;
    cout<<tree.getValueByKey(-5)<<endl;

    cout<<"Expecting: 0"<<endl;
    cout<<tree.getValueByKey(3000)<<endl;

    vector<int> v;

    cout<<"Expecting: 10200, 10210, 10220, 10230, 10240, 10250, 10260"<<endl;
    v = tree.getValuesByRange(1020, 1026);
    for (auto x : v) {
        cout<<x<<" ";
    }
    cout<<endl;

    cout<<"Expecting: 0"<<endl;
    v = tree.getValuesByRange(1026, 1020);
    for (auto x : v) {
        cout<<x<<" ";
    }
    cout<<endl;

    cout<<"Expecting: 0"<<endl;
    v = tree.getValuesByRange(2222, 3333);
    for (auto x : v) {
        cout<<x<<" ";
    }
    cout<<endl;

    cout<<"Expecting: nothing"<<endl;
    tree.remove(256);
    cout<<"Expecting: nothing"<<endl;
    tree.remove(-1);

    cout<<"=====================Test end====================="<<endl;
}

void testRedBlackTree2() {
    RedBlackTree<int, int> tree = RedBlackTree<int, int>();
    tree.insert(3, 30);
    tree.insert(2, 20);
    tree.insert(1, 10);
    vector<int> v = tree.getValuesByRange(0, 4);
    for (auto x : v) {
        cout<<x<<endl;
    }
}