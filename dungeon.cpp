#include "dungeon.h"

dungeon::dungeon()
{

}

const char TILE_OPEN = ' ';   // blank tile
const char TILE_PLAYER = 'Z'; // tile for player's current location
const char TILE_LOOT = 'L';   // tile for loot location
const char TILE_WALL = 'O';   // tile for wall location

// constants for movement status flags
const int STATUS_STAY = 0; // flag indicating player has stayed still
const int STATUS_MOVE = 1; // flag indicating player has moved in a direction
const int STATUS_LOOT = 2; // flag indicating player has stepped onto loot

// constants for user's keyboard inputs
const char MOVE_UP = 'w';    // up movement
const char MOVE_LEFT = 'a';  // left movement
const char MOVE_DOWN = 's';  // down movement
const char MOVE_RIGHT = 'd'; // right movement


char **dungeon::create_map(vector<dungeon::Player> *loot_locs)
{
    clock();
    char **created_map = new char *[9];
    for (int row = 0; row < 9; ++row)
    {
        created_map[row] = new char[9];
    }

    for (int row = 0; row < 9; ++row)
    {
        for (int col = 0; col < 9; ++col)
        {
            created_map[row][col] = TILE_OPEN;
        }
    }

    for (int index = 0; index < 30; ++index)
    {

        int row_index = ((rand() % 100000) * (getpid() + time(NULL)) % 100) % 9;
        int col_index = ((rand() % 100000) * (getpid() * time(NULL)) % 100) % 9;
        created_map[row_index][col_index] = TILE_WALL;
    }

    for (int index = 0; index < 4; ++index)
    {
        int row_index = (rand() % 9 * getpid()) % 9;
        int col_index = (rand() % 9 * getpid()) % 9;
        created_map[row_index][col_index] = TILE_LOOT;
        dungeon::Player loot_point = {row_index, col_index};
        loot_locs->push_back(loot_point);
    }

    created_map[4][4] = TILE_PLAYER;

    return created_map;
}

void dungeon::outputMap(char **map)
{

    for (int i = 0; i < 9; ++i)
    {
        // output inner blocks
        for (int j = 0; j < 9; ++j)
        {
            // output current block
            if (map[i][j] == TILE_OPEN)
            {
                cout << " ";
            }
            else
            {
                cout << map[i][j];
            }
            cout << " ";
        }

        cout << endl
             << endl;
    }
}

void dungeon::deleteMap(char **&map)
{
    if (map)
    {
        for (int row = 0; row < 9; ++row)
        {
            delete[] map[row];
        }
        delete[] map;
    }
    map = nullptr;
}

int dungeon::doPlayerMove(char **map, dungeon::Player &player, int nextRow, int nextCol)
{
    int status = -1;

    if (nextRow >= 9 || nextCol >= 9 || nextRow < 0 || nextCol < 0 || map[nextRow][nextCol] == TILE_WALL)
    {
        status = STATUS_STAY;
        nextRow = player.row;
        nextCol = player.col;
    }
    else if (map[nextRow][nextCol] == TILE_LOOT)
    {
        status = STATUS_LOOT;
        player.loot++;
    }
    else
    {
        status = STATUS_MOVE;
    }

    map[player.row][player.col] = TILE_OPEN;

    player.row = nextRow;
    player.col = nextCol;

    map[player.row][player.col] = TILE_PLAYER;

    return status;
}

void dungeon::getDirection(char input, int &nextRow, int &nextCol)
{
    switch (input)
    {
    case MOVE_UP:
        nextRow--;
        break;
    case MOVE_DOWN:
        nextRow++;
        break;
    case MOVE_LEFT:
        nextCol--;
        break;
    case MOVE_RIGHT:
        nextCol++;
        break;
    }
}

int dungeon::begin()
{
    int nextRow = 0;
    int nextCol = 0;
    char input = 0;
    int status = 0;
    vector<dungeon::Player> loot_locs;
    dungeon::Player player = {4, 4, 0};
    char **map = create_map(&loot_locs);
    for (int index = 0; index < 4; ++index)
    {
        cout << "X: " << loot_locs[index].col << " Y: " << loot_locs[index].row << endl;
    }

    // move player
    while (true)
    {
        outputMap(map);
        cout << "Loot taken: " << player.loot << endl;
        // get user input
        cout << "Move (WASD)" << endl;
        cin >> input;

        // reprompt if invalid command
        if (input != MOVE_UP && input != MOVE_LEFT && input != MOVE_DOWN && input != MOVE_RIGHT)
        {
            cout << "Invalid input, try again" << endl;
            continue;
        }

        // translate from the character input to a direction
        // we will use the player's current location and pass-by-reference to find the intended next location
        nextRow = player.row;
        nextCol = player.col;
        getDirection(input, nextRow, nextCol);

        // move player to new location index, if possible, and get player status
        status = doPlayerMove(map, player, nextRow, nextCol);
        if (status == STATUS_STAY)
        {
            cout << "Out of bounds, go again" << endl;
            continue;
        }
    }

    deleteMap(map);
}
