#include "game.h"

static int check_two_ships(ship , ship );
static int check_two_cells(int, int, int, int);

void make_test_flot10(int [SIZE_15][SIZE_15], ship* armada);
void make_test_flot15(int [SIZE_15][SIZE_15], ship* armada);
static int check_single_death(int [SIZE_15][SIZE_15], ship , int , int );
static int check_ship_death(int [SIZE_15][SIZE_15], ship* , int , int , int* , int* , int* , int* );
static void death_status(int [SIZE_15][SIZE_15], int, int , int , int );

int check_end_of_game(cur_game_info* g_info)
{
    int x = 0;
    int y = 0;
    int size = g_info->size;
    int win1 = 1;
    int win2 = 1;
    while (x < size)
    {
        y = 0;
        while (y < size && win1 == 1)
        {
            if (g_info->com_render[x][y] == MIDDLE_UNDAMAGED || g_info->com_render[x][y] == SINGLE_UNDAMAGED ||
                g_info->com_render[x][y] == HALFED_UP_UNDAMAGED || g_info->com_render[x][y] == HALFED_DOWN_UNDAMAGED ||
                g_info->com_render[x][y] == HALFED_RIGHT_UNDAMAGED || g_info->com_render[x][y] == HALFED_LEFT_UNDAMAGED)
            {
                win1 = 0;
                break;
            }
            y++;
        }
        x++;
    }
    if (win1 == 1) return 1;
    x = 0;
    y = 0;
    while (x < size)
    {
        y = 0;
        while (y < size && win2 == 1)
        {
            if (g_info->hum_com_render[x][y] == MIDDLE_UNDAMAGED       || g_info->hum_com_render[x][y] == SINGLE_UNDAMAGED ||
                g_info->hum_com_render[x][y] == HALFED_UP_UNDAMAGED    || g_info->hum_com_render[x][y] == HALFED_DOWN_UNDAMAGED ||
                g_info->hum_com_render[x][y] == HALFED_RIGHT_UNDAMAGED || g_info->hum_com_render[x][y] == HALFED_LEFT_UNDAMAGED)
            {
                win2 = 0;
                break;
            }
            y++;
        }
        x++;
    }
    if (win2 == 1) return 2;
    return 0;
}
void update_render_field_with_armada(cur_game_info* g_info)
{
    int copy_mem;
    int size = 0;

    int cells_x[5] = { 0 };
    int cells_y[5] = { 0 };


    int i = 0; 
    while (i < 12 && g_info->armada_hum_com[i].presence) 
    {
        size = 0;
        if (g_info->armada_hum_com[i].x_first == g_info->armada_hum_com[i].x_last) 
        {
            copy_mem = g_info->armada_hum_com[i].y_first;
            while (copy_mem <= g_info->armada_hum_com[i].y_last)
            {
                g_info->hum_com_render[g_info->armada_hum_com[i].x_first][copy_mem] = MIDDLE_UNDAMAGED;
                size++; 
                copy_mem++; 
            }
            if (size != 1)
            {
                g_info->hum_com_render[g_info->armada_hum_com[i].x_first][g_info->armada_hum_com[i].y_first] = HALFED_UP_UNDAMAGED;
                g_info->hum_com_render[g_info->armada_hum_com[i].x_last][g_info->armada_hum_com[i].y_last] =   HALFED_DOWN_UNDAMAGED; 
            }
            else
            {
                g_info->hum_com_render[g_info->armada_hum_com[i].x_first][g_info->armada_hum_com[i].y_first] = SINGLE_UNDAMAGED; 
            }
        }
        else
        {
            copy_mem = g_info->armada_hum_com[i].x_first;
            while (copy_mem <= g_info->armada_hum_com[i].x_last)
            {
                g_info->hum_com_render[copy_mem][g_info->armada_hum_com[i].y_first] = MIDDLE_UNDAMAGED;
                size++; 
                copy_mem++; 
            }
            if (size != 1)
            {
                g_info->hum_com_render[g_info->armada_hum_com[i].x_first][g_info->armada_hum_com[i].y_first] = HALFED_LEFT_UNDAMAGED; 
                g_info->hum_com_render[g_info->armada_hum_com[i].x_last][g_info->armada_hum_com[i].y_last] =   HALFED_RIGHT_UNDAMAGED;  
            }
            else
            {
                g_info->hum_com_render[g_info->armada_hum_com[i].x_first][g_info->armada_hum_com[i].y_first] = SINGLE_UNDAMAGED;
            }
        }
        i++;
        
    }
    int x = 0;
    int y = 0;
    while (x < g_info->size)
    {
        y = 0;
        while (y < g_info->size)
        {
            if (g_info->hum_com[x][y] == EMPTY)
            {
                g_info->hum_com_render[x][y] = EMPTY_UNDAMAGED;
            }
            y++;
        }
        x++;
    }
    // Add com render update
    i = 0;
    while (i < 12 && g_info->armada_com[i].presence)
    {
        size = 0;
        if (g_info->armada_com[i].x_first == g_info->armada_com[i].x_last)
        {
            copy_mem = g_info->armada_com[i].y_first;
            while (copy_mem <= g_info->armada_com[i].y_last)
            {
                g_info->com_render[g_info->armada_com[i].x_first][copy_mem] = MIDDLE_UNDAMAGED;
                size++;
                copy_mem++;
            }
            if (size != 1)
            {
                g_info->com_render[g_info->armada_com[i].x_first][g_info->armada_com[i].y_first] = HALFED_UP_UNDAMAGED;
                g_info->com_render[g_info->armada_com[i].x_last][g_info->armada_com[i].y_last] = HALFED_DOWN_UNDAMAGED;
            }
            else
            {
                g_info->com_render[g_info->armada_com[i].x_first][g_info->armada_com[i].y_first] = SINGLE_UNDAMAGED;
            }
        }
        else
        {
            copy_mem = g_info->armada_com[i].x_first;
            while (copy_mem <= g_info->armada_com[i].x_last)
            {
                g_info->com_render[copy_mem][g_info->armada_com[i].y_first] = MIDDLE_UNDAMAGED;
                size++;
                copy_mem++;
            }
            if (size != 1)
            {
                g_info->com_render[g_info->armada_com[i].x_first][g_info->armada_com[i].y_first] = HALFED_LEFT_UNDAMAGED;
                g_info->com_render[g_info->armada_com[i].x_last][g_info->armada_com[i].y_last] = HALFED_RIGHT_UNDAMAGED;
            }
            else
            {
                g_info->com_render[g_info->armada_com[i].x_first][g_info->armada_com[i].y_first] = SINGLE_UNDAMAGED;
            }
        }
        i++;
    }
}
int update_render_after_shot(cur_game_info* g_info, int x, int y)
{
    if (g_info->is_humans_current_shot)
    {
             if (g_info->com_render[x][y] == EMPTY_UNDAMAGED) g_info->com_render[x][y] = EMPTY_DAMAGED; 
        else if (g_info->com_render[x][y] == MIDDLE_UNDAMAGED) g_info->com_render[x][y] = MIDDLE_DAMAGED;
        else if (g_info->com_render[x][y] == SINGLE_UNDAMAGED) g_info->com_render[x][y] = SINGLE_DAMAGED; 
        else if (g_info->com_render[x][y] == HALFED_DOWN_UNDAMAGED) g_info->com_render[x][y] = HALFED_DOWN_DAMAGED; 
        else if (g_info->com_render[x][y] == HALFED_LEFT_UNDAMAGED) g_info->com_render[x][y] = HALFED_LEFT_DAMAGED; 
        else if (g_info->com_render[x][y] == HALFED_RIGHT_UNDAMAGED) g_info->com_render[x][y] = HALFED_RIGHT_DAMAGED; 
        else if (g_info->com_render[x][y] == HALFED_UP_UNDAMAGED) g_info->com_render[x][y] = HALFED_UP_DAMAGED; 
             if (g_info->com_render[x][y] != EMPTY_DAMAGED) return 3;
             else return 4;
    }
    else
    {
             if (g_info->hum_com_render[x][y] == EMPTY_UNDAMAGED)  g_info->hum_com_render[x][y] = EMPTY_DAMAGED;
        else if (g_info->hum_com_render[x][y] == MIDDLE_UNDAMAGED) g_info->hum_com_render[x][y] = MIDDLE_DAMAGED;
        else if (g_info->hum_com_render[x][y] == SINGLE_UNDAMAGED) g_info->hum_com_render[x][y] = SINGLE_DAMAGED;
        else if (g_info->hum_com_render[x][y] == HALFED_DOWN_UNDAMAGED)  g_info->hum_com_render[x][y] = HALFED_DOWN_DAMAGED;
        else if (g_info->hum_com_render[x][y] == HALFED_LEFT_UNDAMAGED)  g_info->hum_com_render[x][y] = HALFED_LEFT_DAMAGED;
        else if (g_info->hum_com_render[x][y] == HALFED_RIGHT_UNDAMAGED) g_info->hum_com_render[x][y] = HALFED_RIGHT_DAMAGED;
        else if (g_info->hum_com_render[x][y] == HALFED_UP_UNDAMAGED) g_info->hum_com_render[x][y] = HALFED_UP_DAMAGED;
             if (g_info->hum_com_render[x][y] != EMPTY_DAMAGED) return 5;
             else return 6;
    }

}
int check_all_ships_presence(cur_game_info* g_info)
{
    int armada_counter = 0;
    while (armada_counter < 11 && g_info->armada_hum_com[armada_counter].presence == 1) { armada_counter++; }
    if ((g_info->size == 15 && armada_counter == 11) || (g_info->size == 10 && armada_counter == 10)) return 1;
    else { return 0; }
}
int check_validness_of_adding_ship(int pressed_index, cur_game_info* g_info, int size_sh, int type)
{
    int size = g_info->size;
    int x = (pressed_index - 1000) % size;
    int y = (pressed_index - 1000) / size;
    ship adding = {0};
    adding.presence = 1; 
    adding.x_first = x;  
    adding.y_first = y;  
    if (type == HORIZONTAL)
    {
        adding.x_last = x + size_sh - 1;
        adding.y_last = y;
    }
    else
    {
        adding.x_last = x;
        adding.y_last = y + size_sh - 1;
    }
    if (adding.x_last >= size || adding.y_last >= size) return ADDING_ERROR_INVALID_PLACEMENT; 
    int i = 0;
    while (g_info->armada_hum_com[i].presence == 1)
    {
        if (check_two_ships(g_info->armada_hum_com[i], adding) == 0) return ADDING_ERROR_INVALID_PLACEMENT; 
        i++;
    }
    // Проверить потом на соответствие изначальных кораблей
    int how_many_allready_preasent_ships_with_size_1 = 0;
    int how_many_allready_preasent_ships_with_size_2 = 0;
    int how_many_allready_preasent_ships_with_size_3 = 0;
    int how_many_allready_preasent_ships_with_size_4 = 0;
    int how_many_allready_preasent_ships_with_size_5 = 0;
    i = 0;
    int sh_size;
    while (g_info->armada_hum_com[i].presence == 1)
    {
        sh_size = g_info->armada_hum_com[i].x_last - g_info->armada_hum_com[i].x_first +
                  g_info->armada_hum_com[i].y_last - g_info->armada_hum_com[i].y_first + 1;
        if (sh_size == 1) how_many_allready_preasent_ships_with_size_1++;
        else if (sh_size == 2) how_many_allready_preasent_ships_with_size_2++;
        else if (sh_size == 3) how_many_allready_preasent_ships_with_size_3++;
        else if (sh_size == 4) how_many_allready_preasent_ships_with_size_4++;
        else if (sh_size == 5) how_many_allready_preasent_ships_with_size_5++;
        i++;
    }
    if (size_sh == 1 && how_many_allready_preasent_ships_with_size_1 >= 4) return ADDING_ERROR_TOO_MUCH_SAME_SIZE;      
    else if (size_sh == 2 && how_many_allready_preasent_ships_with_size_2 >= 3) return ADDING_ERROR_TOO_MUCH_SAME_SIZE; 
    else if (size_sh == 3 && how_many_allready_preasent_ships_with_size_3 >= 2) return ADDING_ERROR_TOO_MUCH_SAME_SIZE; 
    else if (size_sh == 4 && how_many_allready_preasent_ships_with_size_4 >= 1) return ADDING_ERROR_TOO_MUCH_SAME_SIZE;   
    else if (size_sh == 5 && how_many_allready_preasent_ships_with_size_5 >= 1 || size != 15 && size_sh == 5)
        return ADDING_ERROR_5CELL_SHIP_IN_10X10_FIELD;
    return 1;
}
static int check_two_ships(ship correct, ship added)
{
    int copy_mem;
    int size_1 = 0, size_2 = 0;

    int cells1_x[5] = {0};
    int cells1_y[5] = { 0 };
    if (correct.x_first == correct.x_last)
    {
        copy_mem = correct.y_first;
        while (copy_mem <= correct.y_last)
        {
            cells1_x[size_1] = correct.x_first;
            cells1_y[size_1] = copy_mem;
            size_1++;
            copy_mem++;
        }
    }
    else
    {
        copy_mem = correct.x_first;
        while (copy_mem <= correct.x_last)
        {
            cells1_y[size_1] = correct.y_first;
            cells1_x[size_1] = copy_mem;
            size_1++;
            copy_mem++;
        }
    }

    int cells2_x[5] = { 0 };
    int cells2_y[5] = { 0 };

    if (added.x_first == added.x_last) 
    {
        copy_mem = added.y_first;
        while (copy_mem <= added.y_last)
        {
            cells2_x[size_2] = added.x_first;
            cells2_y[size_2] = copy_mem;
            size_2++;
            copy_mem++;
        }
    }
    else
    {
        copy_mem = added.x_first;
        while (copy_mem <= added.x_last)
        {
            cells2_y[size_2] = added.y_first;
            cells2_x[size_2] = copy_mem;
            size_2++;
            copy_mem++;
        }
    }
    int i = 0;
    int j = 0;
    while (i < size_2)
    {
        j = 0;
        while (j < size_1)
        {
            if (check_two_cells(cells1_x[j], cells1_y[j], cells2_x[i], cells2_y[i]) == 0) return 0;
            j++;
        }
        i++;
    }
    return 1;
}
static int check_two_cells(int correct_x, int correct_y , int added_x, int added_y)
{
    if ((added_x == correct_x - 1 || added_x == correct_x || added_x == correct_x + 1) && 
        (added_y == correct_y - 1 || added_y == correct_y || added_y == correct_y + 1)) return 0;
    else { return 1; }
}
void find_best_shot(int f[SIZE_15][SIZE_15], int size, int* best_x, int* best_y)
{
    *best_x = rand() % size;
    *best_y = rand() % size; 
    while (f[*best_x][*best_y] != EMPTY && f[*best_x][*best_y] != SHIP)
    {
        *best_x = rand() % size;
        *best_y = rand() % size;
    }
    
}

void make_shot(int f[SIZE_15][SIZE_15], ship* armada, int x, int y)
{
    int x_first;
    int y_first;
    int x_last;
    int y_last;
    if (f[x][y] == SHIP)
    {
        f[x][y] = HIT;
        if (check_ship_death(f, armada, x, y, &x_first, &y_first, &x_last, &y_last))
        {
            //printf("DEATH SHOT %d,  %d\n", x + 1, y + 1);
            death_status(f, x_first, y_first, x_last, y_last);
            return;
        }
        //printf("GOOD SHOT %d,  %d\n", x + 1, y + 1);
        f[x][y] = HIT;

    }
    else if (f[x][y] == EMPTY)
    {
        //printf("BAD SHOT %d,  %d\n", x + 1, y + 1);
        f[x][y] = MISS;
    }
    else
    {
        //printf("ERROR SHOT %d,  %d\n", x + 1, y + 1);
    }
}


//////
static int check_single_death(int f[SIZE_15][SIZE_15], ship ship_example, int x, int y)
{
    if (ship_example.x_first == ship_example.x_last)
    {
        if (x == ship_example.x_last && y <= ship_example.y_last && y >= ship_example.y_first)
        {
            y = ship_example.y_first;
            while (y <= ship_example.y_last)
            {
                if (f[x][y] != HIT) return 0;
                y++;
            }
            return 1;
        }
        else return 0;
    }
    else
    {
        if (y == ship_example.y_last && x <= ship_example.x_last && x >= ship_example.x_first)
        {
            x = ship_example.x_first;
            while (x <= ship_example.x_last)
            {
                if (f[x][y] != HIT) return 0;
                x++;
            }
            return 1;
        }
        else return 0;
    }
}
static int check_ship_death(int f[SIZE_15][SIZE_15], ship* armada, int x, int y, int* x_first, int* y_first, int* x_last, int* y_last)
{
    int armada_counter = 0;
    while (armada_counter < 11 && armada[armada_counter].presence == 1)
    {
        if (check_single_death(f, armada[armada_counter], x, y))
        {
            *x_first = armada[armada_counter].x_first;
            *y_first = armada[armada_counter].y_first;
            *x_last = armada[armada_counter].x_last;
            *y_last = armada[armada_counter].y_last;
            return 1;
        }
        armada_counter++;
    }
    return 0;
}
static void death_status(int f[SIZE_15][SIZE_15], int x_first, int y_first, int x_last, int y_last)
{
    if (x_last == x_first)
    {
        while (y_first <= y_last)
        {
            f[x_first][y_first] = ALREADY_DEAD;
            y_first++;
        }
    }
    else
    {
        while (x_first <= x_last)
        {
            f[x_first][y_first] = ALREADY_DEAD;
            x_first++;
        }
    }
}
////////////////////
void add_ship(int f[SIZE_15][SIZE_15], ship* armada, int x, int y, int type, int size)
{
    int i = 0;
    int armada_counter = 0;
    while (armada_counter < 11 && armada[armada_counter].presence == 1) { armada_counter++; }
    if (armada_counter == 11) return;
    armada[armada_counter].presence = 1;
    armada[armada_counter].x_first = x;
    armada[armada_counter].y_first = y;
    if (type == HORIZONTAL)
    {
        while (i < size)
        {
            f[x + i][y] = SHIP;
            i++;
        }
        armada[armada_counter].x_last = x + i - 1;
        armada[armada_counter].y_last = y;
    }
    else
    {
        while (i < size)
        {
            f[x][y + i] = SHIP;
            i++;
        }
        armada[armada_counter].x_last = x;
        armada[armada_counter].y_last = y + i - 1;
    }
    printf("ships 1st: %d, %d\n", armada[armada_counter].x_first, armada[armada_counter].y_first);
}
void delete_ship(int f[SIZE_15][SIZE_15], ship sh) 
{
    if (sh.x_first == sh.x_last)
    {
        while (sh.y_first <= sh.y_last)
        {
            f[sh.x_first][sh.y_first] = EMPTY;
            sh.y_first++;
        }
    }
    else
    {
        while (sh.x_first <= sh.x_last)
        {
            f[sh.x_first][sh.y_first] = EMPTY;
            sh.x_first++;
        }
    }
}
void make_test_flot10(int f[SIZE_15][SIZE_15], ship* armada)
{
    add_ship(f, armada, 1, 1, VERTICAL, 4);
    add_ship(f, armada, 1, 6, HORIZONTAL, 3);
    add_ship(f, armada, 9, 0, VERTICAL, 3);
    add_ship(f, armada, 3, 0, HORIZONTAL, 2);
    add_ship(f, armada, 2, 8, VERTICAL, 2);
    add_ship(f, armada, 4, 9, HORIZONTAL, 2);
    add_ship(f, armada, 4, 2, VERTICAL, 1);
    add_ship(f, armada, 7, 3, VERTICAL, 1);
    add_ship(f, armada, 6, 5, VERTICAL, 1);
    add_ship(f, armada, 7, 7, VERTICAL, 1);
}
void make_test_flot15(int f[SIZE_15][SIZE_15], ship* armada)
{
    add_ship(f, armada, 11, 5, VERTICAL, 5);
    add_ship(f, armada, 1, 1, VERTICAL, 4);
    add_ship(f, armada, 1, 6, HORIZONTAL, 3);
    add_ship(f, armada, 9, 0, VERTICAL, 3);
    add_ship(f, armada, 3, 0, HORIZONTAL, 2);
    add_ship(f, armada, 2, 8, VERTICAL, 2);
    add_ship(f, armada, 4, 9, HORIZONTAL, 2);
    add_ship(f, armada, 4, 2, VERTICAL, 1);
    add_ship(f, armada, 7, 3, VERTICAL, 1);
    add_ship(f, armada, 6, 5, VERTICAL, 1);
    add_ship(f, armada, 7, 7, VERTICAL, 1);
}