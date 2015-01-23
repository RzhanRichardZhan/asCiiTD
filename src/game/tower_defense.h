#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
   >m>>> >>>>
   ^  @m ^@
   m   v ^
>m>^ vm< ^
     >>>>^

     so exciting!
 */

enum {TOWER, MONSTER, PATH, EMPTY}; //possible entities in a tile

struct tile;
 

typedef struct tower{
  int range; //manhattan distance from tower to potential site of impact
  int damage; //damage done to monster on tile
} tower;

typedef struct monster{
  int health;
  struct tile * next;
} monster;

typedef struct path{
  int id; //determines who is closest to the finish
  //int x, y;
  struct tile * next;//so monsters can go to next space in path
} path;

typedef struct {
  int type; //one of TOWER, MONSTER, PATH, EMPTY
  union {
  tower tower;
  monster monster;
  path path;
  };
} tile;

typedef struct map{
  tile board[50][50]; //monsters spawn at 0, 0
} map;


//MAP-RELATED FUNCTIONS
int map_create(map *m);
//should initialize the map with some preset paths

//TOWER-RELATED FUNCTIONS
int tower_create(map * m, int x, int y);
int tower_destroy(map *m, int x, int y);
int tower_shoot(map *m, int x, int y);
//x and y are the coordinates of the tower, not the target square

//MONSTER-RELATED FUNCTIONS
int monster_create(map *m, int x, int y);
int monster_destroy(map *m, int x, int y);
int monster_move(map *m, int x, int y);
//x and y are the coordinates of the monster, not the square to move to
int monster_dmg(map *m, int x, int y);

int run(map* m);
//runs game once towers are done being built
//uses spawn monster and shoot
