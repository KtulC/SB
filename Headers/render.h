#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "game.h"


#define PRESSED_NO 0
#define PRESSED_YES 1
#define BORDERS_NO 0
#define BORDERS_YES 1

#define NOT_FOR_PRESSING_B -1
//Menu buttons
#define NEW_B 0
#define GAME_B 1
#define LOAD_B 2
#define SAVE_B 3
#define RECORDS_B 4
//"New" option buttons
#define SIZE_B 5
#define SIZE1_B 6
#define SIZE2_B 7
#define COMPS_B 8
#define HUM_B 9
#define EASY_B 10
#define MED_B 11
#define HARD_B 12
#define CON_B 13
//"Create" option buttons
#define SHIP_SIZE1_B 16
#define SHIP_SIZE2_B 17
#define SHIP_SIZE3_B 18
#define SHIP_SIZE4_B 19
#define SHIP_SIZE5_B 20
#define V_B 21
#define H_B 22
#define DEL_B 23
#define PLAY_B 24
#define STAT_B 25
#define NOTE1_B 26
// "Game" option buttons
#define NOTE2_B 27
#define PLAYER1_B 29
#define PLAYER2_B 30
// "Save" option buttons
#define NOTE3_B 32
#define NAME_B 33
#define ENTER_B 34
#define DEL_S_B 35
#define SAVE_S_B 36

typedef enum 
{
	NEW, 
	CREATE,
	GAME,
	LOAD,
	SAVE,
	RECORDS
}prgrm_stat;
typedef struct vertics
{
	int presence;
	float verts[16];
}vertices_t;
typedef struct element
{
	char* view_info;
	struct vertics element_vertices;
	float text_size;
	int am_i_pressed;
	int have_i_borders;
	int action_index;
}graphic_element;
typedef struct
{
	int first;
	int last;
}new_info;
typedef struct
{
	int first;
	int last;
}create_info;
typedef struct
{
	int first;
	int last;
}game_info;
typedef struct
{
	int first;
	int last;
}load_info;
typedef struct
{
	int first;
	int last;
}save_info;
typedef struct
{
	int first;
	int last;
}records_info;
typedef struct
{
	prgrm_stat status;
	new_info new;
	create_info create;
	game_info game;
	load_info load;
	save_info save;
	records_info records;
}render_info;

static GLuint CreateProgram(GLchar** , GLsizei , GLchar** , GLsizei );
static GLuint CreateShader(GLenum , GLchar** , GLsizei );
GLuint load_shaders();
GLuint selecting_texture(const char *);

void render_scene(graphic_element*, render_info, cur_game_info*, const unsigned int);
void render_hum_field(cur_game_info* , unsigned int);
void render_com_field(cur_game_info* ,unsigned int);
void render_keybord(unsigned int);
void making_buttons(graphic_element *, render_info *, char**);
void render_element(graphic_element, const unsigned int);
void gen_render_data(vertices_t *,  graphic_element);
//
int get_char_index(char);
void get_chars(int* , graphic_element);
void get_tex_vertices(vertices_t*, const int*);
void get_tex_vertices_one(vertices_t*, const int*, int);
void get_vertices(vertices_t*, graphic_element);
void get_borders(vertices_t*, graphic_element);
void get_pressing(vertices_t*, graphic_element);
//
void render_data(vertices_t*, const unsigned int);

//void testing_render(float *, unsigned int);