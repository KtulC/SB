#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE_10 10
#define SIZE_15 15

#define EMPTY 0
#define SHIP 1
#define HIT 2
#define MISS 3
#define ALREADY_DEAD 4

#define VERTICAL 0
#define HORIZONTAL 1

#define EMPTY_UNDAMAGED 0
#define EMPTY_DAMAGED 1
#define HALFED_LEFT_UNDAMAGED 3
#define HALFED_LEFT_DAMAGED 2
#define HALFED_UP_UNDAMAGED 9
#define HALFED_UP_DAMAGED 8
#define HALFED_RIGHT_UNDAMAGED 5
#define HALFED_RIGHT_DAMAGED 4
#define HALFED_DOWN_UNDAMAGED 7
#define HALFED_DOWN_DAMAGED 6
#define SINGLE_UNDAMAGED 11
#define SINGLE_DAMAGED 10
#define MIDDLE_UNDAMAGED 13
#define MIDDLE_DAMAGED 12

#define ADDING_ERROR_INVALID_PLACEMENT -1
#define ADDING_ERROR_TOO_MUCH_SAME_SIZE -2
#define ADDING_ERROR_5CELL_SHIP_IN_10X10_FIELD -3

typedef struct
{
    int presence;
    int x_first;
    int y_first;
    int x_last;
    int y_last;
}ship;
typedef struct
{
    int size; 
    int is_there_human; 
    int hardness; 
    int how_many_shots_made; 
    int is_humans_current_shot; 
    int hum_com[SIZE_15][SIZE_15]; 
    int com[SIZE_15][SIZE_15]; 
    int hum_com_render[SIZE_15][SIZE_15];
    int com_render[SIZE_15][SIZE_15];
    ship armada_hum_com[12]; 
    ship armada_com[12]; 
    char game_name[11]; 
    int am_i_finished;
}cur_game_info;

void update_render_field_with_armada(cur_game_info* );
int update_render_after_shot(cur_game_info* , int , int );
int check_validness_of_adding_ship(int, cur_game_info*,int,int);
int check_all_ships_presence(cur_game_info* );
void add_ship(int[SIZE_15][SIZE_15], ship*, int, int, int, int); 
void delete_ship(int[SIZE_15][SIZE_15], ship);
void make_test_flot10(int[SIZE_15][SIZE_15], ship*);
void make_test_flot15(int[SIZE_15][SIZE_15], ship*);
void find_best_shot(int [SIZE_15][SIZE_15], int , int* , int* );
void make_shot(int[SIZE_15][SIZE_15], ship* , int , int );

int check_end_of_game(cur_game_info* );