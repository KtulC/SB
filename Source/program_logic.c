#include "program_logic.h"

static void menu_buttons_behavour(render_info*, int);
static void new_buttons_behavour(graphic_element*,render_info*, cur_game_info*, int);
static void create_buttons_behavour(graphic_element*, render_info*, cur_game_info*, int, int*);
static void game_buttons_behavour(graphic_element*, render_info*, cur_game_info*, int, int*); 
static void load_buttons_behavour(graphic_element*, render_info*, int);
static void save_buttons_behavour(graphic_element*, render_info*, cur_game_info* ,int);
static void records_buttons_behavour(graphic_element*, render_info*, int);

int next_frame(graphic_element *all_buttons, render_info* r_info, cur_game_info* g_info, int pressed_index)
{
	int message = 0;
	if (pressed_index < 5)
	{
		if (pressed_index != 3) *g_info = (cur_game_info){0};
		menu_buttons_behavour(r_info, pressed_index);
		return 0;
	}
	if (r_info->status == NEW)
	{
		new_buttons_behavour(all_buttons, r_info, g_info, pressed_index); 
		return 0;
	}
	else if (r_info->status == CREATE)
	{
		create_buttons_behavour(all_buttons, r_info, g_info, pressed_index, &message); 
		return message;
	}
	else if (r_info->status == GAME)
	{
		game_buttons_behavour(all_buttons, r_info, g_info, pressed_index, &message);
		return message;
	}
	else if (r_info->status == LOAD)
	{
		load_buttons_behavour(all_buttons, r_info, pressed_index);
		return 0;
	}
	else if (r_info->status == SAVE)
	{
		save_buttons_behavour(all_buttons, r_info, g_info, pressed_index);
		return 0;
	}
	else if (r_info->status == RECORDS)
	{
		records_buttons_behavour(all_buttons, r_info, pressed_index); 
		return 0;
	}
}
static void menu_buttons_behavour(render_info* r_info, int pressed_index)
{
	if (pressed_index != GAME_B) 
	{
		if (pressed_index == NEW_B) 
		{
			r_info->status = NEW;
		}
		else if (pressed_index == SAVE_B && r_info->status == GAME)
		{
			r_info->status = SAVE;
		}
		else if (pressed_index != SAVE_B && pressed_index > GAME_B)
		{
			r_info->status = pressed_index + 1;
		}
		return;
	}
}
static void new_buttons_behavour(graphic_element* all_buttons, render_info* r_info, cur_game_info* g_info, int pressed_index)
{
	if (pressed_index == SIZE1_B)
	{
		all_buttons[SIZE1_B].am_i_pressed = PRESSED_YES; 
		all_buttons[SIZE2_B].am_i_pressed = PRESSED_NO;
	}
	else if (pressed_index == SIZE2_B) 
	{
		all_buttons[SIZE2_B].am_i_pressed = PRESSED_YES;
		all_buttons[SIZE1_B].am_i_pressed = PRESSED_NO;
	}
	else if (pressed_index == COMPS_B) 
	{
		all_buttons[COMPS_B].am_i_pressed = PRESSED_YES;
		all_buttons[HUM_B].am_i_pressed = PRESSED_NO;
	}
	else if (pressed_index == HUM_B) 
	{
		all_buttons[HUM_B].am_i_pressed = PRESSED_YES;
		all_buttons[COMPS_B].am_i_pressed = PRESSED_NO;
	}
	else if (pressed_index == EASY_B) 
	{
		all_buttons[EASY_B].am_i_pressed = PRESSED_YES;
		all_buttons[MED_B].am_i_pressed = PRESSED_NO;
		all_buttons[HARD_B].am_i_pressed = PRESSED_NO;
	}
	else if (pressed_index == MED_B)
	{
		all_buttons[MED_B].am_i_pressed = PRESSED_YES;
		all_buttons[EASY_B].am_i_pressed = PRESSED_NO;
		all_buttons[HARD_B].am_i_pressed = PRESSED_NO; 
	}
	else if (pressed_index == HARD_B)
	{
		all_buttons[HARD_B].am_i_pressed = PRESSED_YES;
		all_buttons[MED_B].am_i_pressed = PRESSED_NO;
		all_buttons[EASY_B].am_i_pressed = PRESSED_NO;
	}
	else if (pressed_index == CON_B)
	{
		if (all_buttons[SIZE1_B].am_i_pressed == PRESSED_YES)
		{
			g_info->size = 10;
		}
		else if (all_buttons[SIZE2_B].am_i_pressed == PRESSED_YES)
		{
			g_info->size = 15;
		} 
		if (all_buttons[COMPS_B].am_i_pressed == PRESSED_YES) 
		{
			g_info->is_there_human = 0;
		}
		else if (all_buttons[HUM_B].am_i_pressed == PRESSED_YES) 
		{
			g_info->is_there_human = 1;
		}
		if (all_buttons[EASY_B].am_i_pressed == PRESSED_YES) 
		{
			g_info->hardness = 0;
		}
		else if (all_buttons[MED_B].am_i_pressed == PRESSED_YES) 
		{
			g_info->hardness = 1;
		}
		else if (all_buttons[HARD_B].am_i_pressed == PRESSED_YES)
		{
			g_info->hardness = 2;
		}
		all_buttons[CON_B].am_i_pressed = PRESSED_NO;
		if (all_buttons[HUM_B].am_i_pressed == PRESSED_YES)
		{
			r_info->status = CREATE;
			if (all_buttons[SIZE1_B].am_i_pressed == PRESSED_YES)
			{
				make_test_flot10(g_info->com, g_info->armada_com);
			}
			else
			{
				make_test_flot15(g_info->com, g_info->armada_com);
			}
			update_render_field_with_armada(g_info); 
		}
		else
		{
			r_info->status = GAME;
			if (all_buttons[SIZE1_B].am_i_pressed == PRESSED_YES)
			{
				make_test_flot10(g_info->hum_com, g_info->armada_hum_com);
				make_test_flot10(g_info->com, g_info->armada_com);
			}
			else
			{
				make_test_flot15(g_info->hum_com, g_info->armada_hum_com);
				make_test_flot15(g_info->com, g_info->armada_com);
			}
			update_render_field_with_armada(g_info);
		}
	}
}
static void create_buttons_behavour(graphic_element* all_buttons, render_info* r_info, cur_game_info* g_info, int pressed_index, int* message)
{
	if (pressed_index == SHIP_SIZE1_B || pressed_index == SHIP_SIZE2_B || pressed_index == SHIP_SIZE3_B ||
		pressed_index == SHIP_SIZE4_B || pressed_index == SHIP_SIZE5_B)
	{
		all_buttons[SHIP_SIZE1_B].am_i_pressed = PRESSED_NO;
		all_buttons[SHIP_SIZE2_B].am_i_pressed = PRESSED_NO;
		all_buttons[SHIP_SIZE3_B].am_i_pressed = PRESSED_NO;
		all_buttons[SHIP_SIZE4_B].am_i_pressed = PRESSED_NO;
		all_buttons[SHIP_SIZE5_B].am_i_pressed = PRESSED_NO;
		all_buttons[pressed_index].am_i_pressed = PRESSED_YES;
	}
	else if (pressed_index == V_B || pressed_index == H_B)
	{
		all_buttons[H_B].am_i_pressed = PRESSED_NO;
		all_buttons[V_B].am_i_pressed = PRESSED_NO;
		all_buttons[pressed_index].am_i_pressed = PRESSED_YES;
	}
	else if (pressed_index >= 1000)
	{
		int i = 0;
		int adding_status = 0;
		while (all_buttons[SHIP_SIZE1_B + i].am_i_pressed == PRESSED_NO)
		{
			i++;
		}
		if ((adding_status = check_validness_of_adding_ship(pressed_index, g_info, i + 1, all_buttons[H_B].am_i_pressed)) == 1)
		{
			//void add_ship(int f[SIZE_15][SIZE_15], ship* armada, int x, int y, int type, int size)
			add_ship(g_info->hum_com, g_info->armada_hum_com, (pressed_index - 1000) % g_info->size ,
				(pressed_index - 1000) / g_info->size , all_buttons[H_B].am_i_pressed, i + 1);
			*message = 1;
			update_render_field_with_armada(g_info);
		}
		else
		{
			*message = adding_status;
		}
		printf("adding status: %d\n", adding_status); 
	}
	else if (pressed_index == DEL_B)
	{
		int i_c = 0;
		all_buttons[DEL_B].am_i_pressed = PRESSED_NO;
		while (i_c < 12 && g_info->armada_hum_com[i_c].presence == 1)
		{
			i_c++; 
		} 
		if (i_c > 0)
		{
			g_info->armada_hum_com[i_c - 1].presence = 0;
			delete_ship(g_info->hum_com, g_info->armada_hum_com[i_c - 1]); 
			update_render_field_with_armada(g_info); 
			*message = 1;
		}
		printf("adding status: %d\n", *message);
	}
	else if (pressed_index == PLAY_B)
	{
		all_buttons[PLAY_B].am_i_pressed = PRESSED_NO;
		if (check_all_ships_presence(g_info)) r_info->status = GAME;
		g_info->is_humans_current_shot = rand() % 2;
	}
}
static void game_buttons_behavour(graphic_element* all_buttons, render_info* r_info, cur_game_info* g_info, int pressed_index, int* message)
{
	int x = 0;
	int y = 0;
	if (g_info->is_there_human)
	{
		if (g_info->is_humans_current_shot)
		{
			x = (pressed_index - 2000) % g_info->size;
			y = (pressed_index - 2000) / g_info->size;
			make_shot(g_info->com, g_info->armada_com, x, y);
			g_info->how_many_shots_made++;
			// check validness of human shot!!!!!
			*message = update_render_after_shot(g_info, x, y);
			if (*message == 4)
			{
				g_info->is_humans_current_shot = 0;
			}
		}
	}
}
static void load_buttons_behavour(graphic_element* all_buttons, render_info* r_info, int pressed_index)   
{

}
static void save_buttons_behavour(graphic_element* all_buttons, render_info* r_info, cur_game_info* g_info, int pressed_index)   
{
	if (pressed_index == DEL_S_B)
	{
		all_buttons[DEL_S_B].am_i_pressed = PRESSED_NO;
		int i = 0;
		while (all_buttons[NAME_B].view_info[i] != ' ' && all_buttons[NAME_B].view_info[i] != '\0') i++;
		if (i != 0) all_buttons[NAME_B].view_info[i - 1] = ' ';

	}
	else if (pressed_index == SAVE_S_B)
	{
		int i = 0;
		all_buttons[SAVE_S_B].am_i_pressed = PRESSED_NO; 
		while (all_buttons[NAME_B].view_info[i] != ' ' && all_buttons[NAME_B].view_info[i] != '\0') i++;
		if (i == 0) return;
		if (g_info->am_i_finished == 1)
		{
			make_record(all_buttons[NAME_B].view_info, g_info->how_many_shots_made); 
			*g_info = (cur_game_info){ 0 };
		}
		
	}
}
static void records_buttons_behavour(graphic_element* all_buttons, render_info* r_info, int pressed_index)
{

}