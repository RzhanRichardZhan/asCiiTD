#include "tower_defense.h"


//MAP-RELATED FUNCTIONS
int map_create(map *m){
  int r = 0;
  int c = 0;
  for( ; r < 50 ; r++){
    for ( ; c < 50 ; c++){
      (&(m->board[r][c]))->type = EMPTY;
    }
  }

  return 0;
}

//TOWER-RELATED FUNCTIONS
//assuming proper coordinates
int tower_create(map * m, int x, int y){
  tile * t = &(m->board[x][y]);
  /*int type = t->type;
    if(type != EMPTY){
    printf("cannot build here\n");
    return -1;
    }else{*/
  t->type = TOWER;
  tower * new_tower = (tower *)malloc(sizeof(tower));
  //^^memory not allocated in map initialization?
  new_tower->range = 3; // arbitrary range and damage constant
  new_tower->damage = 1; // arbitrary range and damage constants
  t->tower = * new_tower;

  return 0;
}

int tower_destroy(map * m, int x, int y){
  tile * t = &(m->board[x][y]);
  /*int type = t->type;
    if(type != TOWER){
    printf("no tower here, cannot remove\n");
    return -1;
    }else{*/
  t->type = EMPTY;
  //t->tower = NULL;
  //the tile will still have the mem of tower
  // but b/c type is changed to empty oit won't be accesed anyway
  return 0;
}

int tower_shoot(map *m, int x, int y){
  tile * t = &(m->board[x][y]);

  return 0;
}


//MONSTER-RELATED FUNCTIONS
//assume proper coordinates
int monster_create(map *m, int x, int y){
  tile * t = &(m->board[x][y]); 
  struct tile * new = (t->path.next);

  t->type = MONSTER;
  t->monster.health = 5;//5 is an arbitrary number
  t->monster.next = new;

  return 0;
}

int monster_destroy(map *m, int x, int y){
  
  return 0;
}

int monster_move(map *m, int x, int y){
  tile * t = &(m->board[x][y]); //tile where monster starts
  tile * temp = (tile *)(t->monster.next); //tile where monster is going

  //set next tile to monster
  temp->type = MONSTER;
  temp->monster.next = temp->path.next;
  temp->monster.health = t->monster.health;

  //set original tile to path
  t->type = PATH;
  t->path.next = temp;

}

int monster_dmg(map *m, int x, int y){
  //What is this supposed to do??
  //should there be an int for amount of damage?
  return 0;
}

int main(){

  //printf("size of map:%lu \n",sizeof(map));

  return 0;
}
