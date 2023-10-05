#ifndef DUNGEON_H
#define DUNGEON_H
#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <vector>
#include <unistd.h>
#include <ctime>

using std::cin; using std::cout; using  std::endl; using  std::string; using  std::ifstream; using  std::vector;

// Player object container


class dungeon
{
public:
    dungeon();

    struct Player
    {
        int row = 0;
        int col = 0;
        int loot = 0;
    };


    char **create_map(vector<Player> *loot_locs);
    void outputMap(char **map);
    void deleteMap(char **&map);
    int doPlayerMove(char **map, Player &player, int nextRow, int nextCol);
    void getDirection(char input, int &nextRow, int &nextCol);
    int begin();

};

#endif // DUNGEON_H
