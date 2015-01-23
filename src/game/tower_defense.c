
#include "tower_defense.h"


//MAP-RELATED FUNCTIONS

int level_1_create(map * m){
  //straignt line across row 20
  int c = 0;
  for( c = 0; c < 50 ; c++ ){
    tile * t = &(m->board[20][c]);
    t->type = PATH;
    t->path.id = c;
    if(c != 49 )
      (&(t->path))->next = &(m->board[20][c+1]);
  }
  return 0;
}

int map_create(map *m){
  //printf("creating map\n");
  int r = 0;
  int c = 0;
  for( r = 0 ; r < 50 ; r++){
    for ( c = 0 ; c < 50 ; c++){
      tile * temp = &(m->board[r][c]);
      temp = (tile *)malloc(sizeof(tile));
      (&(m->board[r][c]))->type = EMPTY;
    }
  }
  level_1_create(m);
  //printf("map created\n");
  return 0;
}

//TOWER-RELATED FUNCTIONS
//assuming proper coordinates
int tower_create(map * m, int x, int y){
  tile * t = &(m->board[x][y]);
  //printf("adress: %lu \n" , &t );
  //printf("adress2: %lu \n" , &(m->board[x][y]));
  /*int type = t->type;
    if(type != EMPTY){
    printf("cannot build here\n");
    return -1;
    }else{*/
  t->type = TOWER;
  //^^memory not allocated in map initialization?
  (&( t->tower ))->range = 3; // arbitrary range and damage constant
  (&( t->tower ))->damage = 1; // arbitrary range and damage constants

  //printf("type1:: %d\n", t->type);
  //printf("type2:: %d\n", (&(m->board[x][y]))->type);


  return 0;
}

int tower_destroy(map * m, int x, int y){
  printf("creating tower/n");
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

void print_map(map *m){
  int y,x;
  for (y = 0; y < 50; y++){
    for (x = 0; x < 50; x++){
      int img = m->board[y][x].type;
      if (img == TOWER){
	printf("T");
      }
      else if (img == MONSTER){
	printf("M");
      }
      else if (img == PATH){
	printf("P");
      }
      else{
	printf(".");
      }
    }
    printf("\n");
  }
}

int main(){

  printf("\nSTARTING\n\n");

  map * m = (map *)malloc(sizeof(map *));
  map_create(m);

  
  tower_create(m, 3,3 );
  //printf("tower %d \n", m->board[3][3].tower.range);
  print_map(m);
  
  printf("\nDONE\n\n");

  return 0;
}
