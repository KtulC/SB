//#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string.h>
#include "render.h"
#include "stb_image.h"
/*
void testing_render(float* vertices, unsigned int VBO)
{
    float vertices_copy[16];
    memcpy(vertices_copy, vertices, 16 * sizeof(float));

    float buffer1[] = {
       -1.0f,-1.0f, 0.0f, 0.0f,//0
        1.0f,-1.0f, 1.0f, 0.0f,//1
        1.0f, 1.0f, 1.0f, 1.0f,//2
       -1.0f, 1.0f, 0.0f, 1.0f //3
    };
    memcpy(vertices, buffer1, 16 * sizeof(float));
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 16 * sizeof(float), vertices, GL_STATIC_DRAW);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
    float buffer2[] = {
         0.0f, -0.25f, 0.0f, 0.833333f,//0
         0.5f, -0.25f, 0.1666666f, 0.833333f,//1
         0.5f,  0.25f, 0.1666666f, 1.0f,//2
         0.0f,  0.25f, 0.0f, 1.0f //3
    };
    memcpy(vertices, buffer2, 16 * sizeof(float));
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 16 * sizeof(float), vertices, GL_STATIC_DRAW);
    //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

    memcpy(vertices, vertices_copy, 16 * sizeof(float));
}
*/
void render_hum_field(cur_game_info* g_info, unsigned int VBO)
{
    int size = g_info->size;
    float hor_step = (0.7f / (float)size) * 0.66f;
    float vert_step = -0.9f / (float)size;
    graphic_element cur_cell = { 0 };

    vertices_t CELL_verts = { 0 };
    CELL_verts.presence = 1;
    CELL_verts.verts[0] = -0.975f;
    CELL_verts.verts[1] = 0.95f + vert_step;
    CELL_verts.verts[4] = -0.975f + hor_step;
    CELL_verts.verts[5] = 0.95f + vert_step;
    CELL_verts.verts[8] = -0.975f + hor_step;
    CELL_verts.verts[9] = 0.95f;
    CELL_verts.verts[12] = -0.975f;
    CELL_verts.verts[13] = 0.95f;

    char info_text[2] = "/A";

    cur_cell.view_info = info_text;
    cur_cell.have_i_borders = BORDERS_YES;
    cur_cell.text_size = 1.0f;
    cur_cell.element_vertices = CELL_verts;
    int i = 0;
    int j = 0;
    while (i < size)
    {
        j = 0;
        while (j < size)
        {
            cur_cell = (graphic_element){ 0 };
            cur_cell.view_info = info_text;
            cur_cell.have_i_borders = BORDERS_YES;
            cur_cell.text_size = 1.0f;
            cur_cell.element_vertices = CELL_verts;
            info_text[1] = (char)(g_info->hum_com_render[i][j] + 'A'); 
            CELL_verts.verts[0] = -0.975f + (float)i * hor_step;
            CELL_verts.verts[1] = 0.95f + vert_step + (float)j * vert_step;
            CELL_verts.verts[4] = -0.975f + hor_step + (float)i * hor_step;
            CELL_verts.verts[5] = 0.95f + vert_step + (float)j * vert_step;
            CELL_verts.verts[8] = -0.975f + hor_step + (float)i * hor_step;
            CELL_verts.verts[9] = 0.95f + (float)j * vert_step;
            CELL_verts.verts[12] = -0.975f + (float)i * hor_step;
            CELL_verts.verts[13] = 0.95f + (float)j * vert_step;
            cur_cell.element_vertices = CELL_verts;
            render_element(cur_cell, VBO);
            j++;
        }
        i++;
    }
}
void render_keybord(unsigned int VBO)
{
    int size = 6;
    float hor_step = (0.7f / (float)size) * 0.66f;
    float vert_step = -0.9f / (float)size;
    graphic_element cur_cell = { 0 }; 

    vertices_t CELL_verts = { 0 };
    CELL_verts.presence = 1;   
    CELL_verts.verts[0] = -0.225f;
    CELL_verts.verts[1] = -0.05f + vert_step;
    CELL_verts.verts[4] = -0.225f + hor_step;
    CELL_verts.verts[5] = -0.05f + vert_step;
    CELL_verts.verts[8] = -0.225f + hor_step;
    CELL_verts.verts[9] = -0.05f;
    CELL_verts.verts[12] = -0.225f;
    CELL_verts.verts[13] = -0.05f;

    char info_text[1] = "A";

    cur_cell.view_info = info_text;
    cur_cell.have_i_borders = BORDERS_YES;
    cur_cell.text_size = 1.0f;
    cur_cell.element_vertices = CELL_verts;
    int i = 0;
    int j = 0;
    while (i < size)
    {
        j = 0;
        while (j < size)
        {
            cur_cell = (graphic_element){ 0 };
            cur_cell.view_info = info_text;
            cur_cell.have_i_borders = BORDERS_YES;
            cur_cell.text_size = 0.5f;
            cur_cell.element_vertices = CELL_verts;
            info_text[0] = (char)(j * size + i  + 'A');
            if (info_text[0] > 'Z')
            {
                info_text[0] -= 'Z';
                info_text[0] += '0' - 1;
            }
            CELL_verts.verts[0] = -0.225f + (float)i * hor_step;
            CELL_verts.verts[1] = -0.05f + vert_step + (float)j * vert_step;
            CELL_verts.verts[4] = -0.225f + hor_step + (float)i * hor_step;
            CELL_verts.verts[5] = -0.05f + vert_step + (float)j * vert_step;
            CELL_verts.verts[8] = -0.225f + hor_step + (float)i * hor_step;
            CELL_verts.verts[9] = -0.05f + (float)j * vert_step;
            CELL_verts.verts[12] = -0.225f + (float)i * hor_step;
            CELL_verts.verts[13] = -0.05f + (float)j * vert_step;
            cur_cell.element_vertices = CELL_verts;
            render_element(cur_cell, VBO);
            j++;
        }
        i++;
    }
}
void render_com_field(cur_game_info* g_info, unsigned int VBO)
{
    int size = g_info->size;
    float hor_step = (0.7f / (float)size) * 0.66f;
    float vert_step = -0.9f / (float)size;
    graphic_element cur_cell = { 0 };

    vertices_t CELL_verts = { 0 };
    CELL_verts.presence = 1;
    CELL_verts.verts[0] = -0.225f;
    CELL_verts.verts[1] = -0.05f + vert_step;
    CELL_verts.verts[4] = -0.225f + hor_step;
    CELL_verts.verts[5] = -0.05f + vert_step;
    CELL_verts.verts[8] = -0.225f + hor_step;
    CELL_verts.verts[9] = -0.05f;
    CELL_verts.verts[12] = -0.225f;
    CELL_verts.verts[13] = -0.05f;

    char info_text[2] = "/A";

    cur_cell.view_info = info_text;
    cur_cell.have_i_borders = BORDERS_YES;
    cur_cell.text_size = 1.0f;
    cur_cell.element_vertices = CELL_verts;
    int i = 0;
    int j = 0;
    if (g_info->is_there_human == 0)
    {
        while (i < size)
        {
            j = 0;
            while (j < size)
            {
                cur_cell = (graphic_element){ 0 };
                cur_cell.view_info = info_text;
                cur_cell.have_i_borders = BORDERS_YES;
                cur_cell.text_size = 1.0f;
                cur_cell.element_vertices = CELL_verts;
                info_text[1] = (char)(g_info->com_render[i][j] + 'A');
                CELL_verts.verts[0] = -0.225f + (float)i * hor_step;
                CELL_verts.verts[1] = -0.05f + vert_step + (float)j * vert_step;
                CELL_verts.verts[4] = -0.225f + hor_step + (float)i * hor_step;
                CELL_verts.verts[5] = -0.05f + vert_step + (float)j * vert_step;
                CELL_verts.verts[8] = -0.225f + hor_step + (float)i * hor_step;
                CELL_verts.verts[9] = -0.05f + (float)j * vert_step;
                CELL_verts.verts[12] = -0.225f + (float)i * hor_step;
                CELL_verts.verts[13] = -0.05f + (float)j * vert_step;
                cur_cell.element_vertices = CELL_verts;
                render_element(cur_cell, VBO);
                j++;
            }
            i++;
        }
    }
    else
    {
        while (i < size)
        {
            j = 0;
            while (j < size)
            {
                cur_cell = (graphic_element){ 0 };
                cur_cell.view_info = info_text;
                cur_cell.have_i_borders = BORDERS_YES;
                cur_cell.text_size = 1.0f;
                cur_cell.element_vertices = CELL_verts;
                if (g_info->com_render[i][j] == EMPTY_DAMAGED || g_info->com_render[i][j] == SINGLE_DAMAGED || 
                    g_info->com_render[i][j] == MIDDLE_DAMAGED || g_info->com_render[i][j] == HALFED_UP_DAMAGED ||
                    g_info->com_render[i][j] == HALFED_LEFT_DAMAGED || g_info->com_render[i][j] == HALFED_DOWN_DAMAGED || 
                    g_info->com_render[i][j] == HALFED_RIGHT_DAMAGED)
                {
                    info_text[1] = (char)(g_info->com_render[i][j] + 'A');
                }
                else
                {
                    info_text[1] = (char)('A');
                    cur_cell.am_i_pressed = PRESSED_YES;
                }
                CELL_verts.verts[0] = -0.225f + (float)i * hor_step;
                CELL_verts.verts[1] = -0.05f + vert_step + (float)j * vert_step;
                CELL_verts.verts[4] = -0.225f + hor_step + (float)i * hor_step;
                CELL_verts.verts[5] = -0.05f + vert_step + (float)j * vert_step;
                CELL_verts.verts[8] = -0.225f + hor_step + (float)i * hor_step;
                CELL_verts.verts[9] = -0.05f + (float)j * vert_step;
                CELL_verts.verts[12] = -0.225f + (float)i * hor_step;
                CELL_verts.verts[13] = -0.05f + (float)j * vert_step;
                cur_cell.element_vertices = CELL_verts;
                render_element(cur_cell, VBO);
                j++;
            }
            i++;
        }
    }
    /*
    cur_cell = (graphic_element){ 0 };
    cur_cell.view_info = info_text;
    cur_cell.have_i_borders = BORDERS_YES;
    cur_cell.text_size = 1.0f;
    cur_cell.element_vertices = CELL_verts;
    info_text[1] = (char)(g_info->hum_com_render[i][j] + 'A');
    CELL_verts.verts[0] = -0.225f + (float)i * hor_step;
    CELL_verts.verts[1] = -0.05f + vert_step + (float)j * vert_step;
    CELL_verts.verts[4] = -0.225f + hor_step + (float)i * hor_step;
    CELL_verts.verts[5] = -0.05f + vert_step + (float)j * vert_step;
    CELL_verts.verts[8] = -0.225f + hor_step + (float)i * hor_step;
    CELL_verts.verts[9] = -0.05f + (float)j * vert_step;
    CELL_verts.verts[12] = -0.225f + (float)i * hor_step;
    CELL_verts.verts[13] = -0.05f + (float)j * vert_step;
    render_element(cur_cell, VBO);
    */
}
void render_scene(graphic_element* all_buttons, render_info r_info, cur_game_info* g_info,const unsigned int VBO) 
{
    int i = 0;
    int j = 0;
    if (r_info.status == NEW)
    {
        all_buttons[0].am_i_pressed = 1;
        all_buttons[1].am_i_pressed = 0;
        all_buttons[2].am_i_pressed = 0;
        all_buttons[3].am_i_pressed = 0;
        all_buttons[4].am_i_pressed = 0;
        i = r_info.new.first;
        j = r_info.new.last;
    }
    if (r_info.status == CREATE)
    {
        all_buttons[0].am_i_pressed = 1;
        all_buttons[1].am_i_pressed = 0;
        all_buttons[2].am_i_pressed = 0;
        all_buttons[3].am_i_pressed = 0;
        all_buttons[4].am_i_pressed = 0;
        i = r_info.create.first;
        j = r_info.create.last;
        render_hum_field(g_info, VBO); 
    }
    else if (r_info.status == GAME)
    {
        all_buttons[0].am_i_pressed = 0;
        all_buttons[1].am_i_pressed = 1;
        all_buttons[2].am_i_pressed = 0;
        all_buttons[3].am_i_pressed = 0;
        all_buttons[4].am_i_pressed = 0;
        i = r_info.game.first;
        j = r_info.game.last; 
        render_hum_field(g_info, VBO); 
        render_com_field(g_info, VBO); 
    }
    else if (r_info.status == LOAD)
    {
        all_buttons[0].am_i_pressed = 0;
        all_buttons[1].am_i_pressed = 0;
        all_buttons[2].am_i_pressed = 1;
        all_buttons[3].am_i_pressed = 0;
        all_buttons[4].am_i_pressed = 0;
        i = r_info.load.first;
        j = r_info.load.last;
    }
    else if (r_info.status == SAVE)
    {
        all_buttons[0].am_i_pressed = 0;
        all_buttons[1].am_i_pressed = 0;
        all_buttons[2].am_i_pressed = 0;
        all_buttons[3].am_i_pressed = 1;
        all_buttons[4].am_i_pressed = 0;
        i = r_info.save.first;
        j = r_info.save.last;
        render_keybord(VBO);
    }
    else if (r_info.status == RECORDS)
    {
        all_buttons[0].am_i_pressed = 0;
        all_buttons[1].am_i_pressed = 0;
        all_buttons[2].am_i_pressed = 0;
        all_buttons[3].am_i_pressed = 0;
        all_buttons[4].am_i_pressed = 1;
        i = r_info.records.first;
        j = r_info.records.last;
    }
    int y = 0;
    while (y < 5)
    {
        render_element(all_buttons[y], VBO);
        y++;
    }
    
    while (i <= j)
    {
        render_element(all_buttons[i], VBO);
        i++;
    }
    
}
void making_buttons(graphic_element* all_buttons, render_info* r_info, char **names)
{
    //Right big buttons
    vertices_t NEW_verts = {0};
    NEW_verts.presence = 1;

    NEW_verts.verts[0] = 0.5f;
    NEW_verts.verts[1] = 0.6f;
    NEW_verts.verts[4] = 1.0f;
    NEW_verts.verts[5] = 0.6f;
    NEW_verts.verts[8] = 1.0f;
    NEW_verts.verts[9] = 1.0f;
    NEW_verts.verts[12] = 0.5f;
    NEW_verts.verts[13] = 1.0f;

    vertices_t GAME_verts = { 0 };
    GAME_verts.presence = 1;
    
    GAME_verts.verts[0] = 0.5f;
    GAME_verts.verts[1] = 0.2f;
    GAME_verts.verts[4] = 1.0f;
    GAME_verts.verts[5] = 0.2f;
    GAME_verts.verts[8] = 1.0f;
    GAME_verts.verts[9] = 0.6f;
    GAME_verts.verts[12] = 0.5f;
    GAME_verts.verts[13] = 0.6f;

    vertices_t LOAD_verts = { 0 };
    LOAD_verts.presence = 1;

    LOAD_verts.verts[0] = 0.5f;
    LOAD_verts.verts[1] = -0.2f;
    LOAD_verts.verts[4] = 1.0f;
    LOAD_verts.verts[5] = -0.2f;
    LOAD_verts.verts[8] = 1.0f;
    LOAD_verts.verts[9] = 0.2f;
    LOAD_verts.verts[12] = 0.5f;
    LOAD_verts.verts[13] = 0.2f;

    vertices_t SAVE_verts = { 0 };
    SAVE_verts.presence = 1;

    SAVE_verts.verts[0] = 0.5f;
    SAVE_verts.verts[1] = -0.6f;
    SAVE_verts.verts[4] = 1.0f;
    SAVE_verts.verts[5] = -0.6f;
    SAVE_verts.verts[8] = 1.0f;
    SAVE_verts.verts[9] = -0.2f;
    SAVE_verts.verts[12] = 0.5f;
    SAVE_verts.verts[13] = -0.2f;

    vertices_t RECORDS_verts = { 0 };
    RECORDS_verts.presence = 1;

    RECORDS_verts.verts[0] = 0.5f;
    RECORDS_verts.verts[1] = -1.0f;
    RECORDS_verts.verts[4] = 1.0f;
    RECORDS_verts.verts[5] = -1.0f;
    RECORDS_verts.verts[8] = 1.0f;
    RECORDS_verts.verts[9] = -0.6f;
    RECORDS_verts.verts[12] = 0.5f;
    RECORDS_verts.verts[13] = -0.6f;

    graphic_element NEW_button     = {names[0], NEW_verts, 0.2f, 0, 1, 0};
    graphic_element GAME_button    = {names[1], GAME_verts, 0.2f, 0, 1, 1};
    graphic_element LOAD_button    = {names[2], LOAD_verts, 0.2f, 0, 1, 2};
    graphic_element SAVE_button    = {names[3], SAVE_verts, 0.2f, 0, 1, 3};
    graphic_element RECORDS_button = {names[4], RECORDS_verts, 0.2f, 0, 1, 4};
    all_buttons[0] = NEW_button    ;
    all_buttons[1] = GAME_button   ;
    all_buttons[2] = LOAD_button   ;
    all_buttons[3] = SAVE_button   ;
    all_buttons[4] = RECORDS_button;

    // New buttons
    vertices_t SIZE_verts = { 0 };
    SIZE_verts.presence = 1;
    SIZE_verts.verts[0] = -0.7f;
    SIZE_verts.verts[1] =  0.6f;
    SIZE_verts.verts[4] = -0.45f;
    SIZE_verts.verts[5] =  0.6f;
    SIZE_verts.verts[8] = -0.45f;
    SIZE_verts.verts[9] =  0.8f;
    SIZE_verts.verts[12] =-0.7f;
    SIZE_verts.verts[13] = 0.8f;
    graphic_element SIZE_button = { names[5], SIZE_verts, 0.4f, PRESSED_NO, BORDERS_NO, NOT_FOR_PRESSING_B };
    all_buttons[5] = SIZE_button;

    vertices_t SIZE1_verts = { 0 };
    SIZE1_verts.presence = 1;
    SIZE1_verts.verts[0] = -0.35f;
    SIZE1_verts.verts[1] = 0.6f;
    SIZE1_verts.verts[4] = -0.25f;
    SIZE1_verts.verts[5] = 0.6f;
    SIZE1_verts.verts[8] = -0.25f;
    SIZE1_verts.verts[9] = 0.8f;
    SIZE1_verts.verts[12] = -0.35f;
    SIZE1_verts.verts[13] = 0.8f;
    graphic_element SIZE1_button = { names[6], SIZE1_verts, 0.22f, PRESSED_YES, BORDERS_YES, SIZE1_B}; 
    all_buttons[6] = SIZE1_button;

    vertices_t SIZE2_verts = { 0 };
    SIZE2_verts.presence = 1;
    SIZE2_verts.verts[0] = -0.25f;
    SIZE2_verts.verts[1] = 0.6f;
    SIZE2_verts.verts[4] = -0.15f;
    SIZE2_verts.verts[5] = 0.6f;
    SIZE2_verts.verts[8] = -0.15f;
    SIZE2_verts.verts[9] = 0.8f;
    SIZE2_verts.verts[12] = -0.25f;
    SIZE2_verts.verts[13] = 0.8f;
    graphic_element SIZE2_button = { names[7], SIZE2_verts, 0.22f, PRESSED_NO, BORDERS_YES, SIZE2_B};
    all_buttons[7] = SIZE2_button;

    vertices_t COMPS_verts = { 0 };
    COMPS_verts.presence = 1;
    COMPS_verts.verts[0] = -0.75f;
    COMPS_verts.verts[1] = 0.4f;
    COMPS_verts.verts[4] = -0.4f;
    COMPS_verts.verts[5] = 0.4f;
    COMPS_verts.verts[8] = -0.4f;
    COMPS_verts.verts[9] = 0.5f;
    COMPS_verts.verts[12] = -0.75f;
    COMPS_verts.verts[13] = 0.5f;
    graphic_element COMPS_button = { names[8], COMPS_verts, 0.4f, PRESSED_YES, BORDERS_YES, COMPS_B };
    all_buttons[8] = COMPS_button;

    vertices_t HUM_verts = { 0 };
    HUM_verts.presence = 1;
    HUM_verts.verts[0] = -0.1f;
    HUM_verts.verts[1] = 0.4f;
    HUM_verts.verts[4] = 0.495f;
    HUM_verts.verts[5] = 0.4f;
    HUM_verts.verts[8] = 0.495f;
    HUM_verts.verts[9] = 0.5f;
    HUM_verts.verts[12] = -0.1f;
    HUM_verts.verts[13] = 0.5f;
    graphic_element HUM_button = { names[9], HUM_verts, 0.4f, PRESSED_NO, BORDERS_YES, HUM_B };
    all_buttons[9] = HUM_button;

    vertices_t EASY_verts = { 0 };
    EASY_verts.presence = 1;
    EASY_verts.verts[0] = -0.32f;
    EASY_verts.verts[1] = 0.2f;
    EASY_verts.verts[4] = -0.15f;
    EASY_verts.verts[5] = 0.2f;
    EASY_verts.verts[8] = -0.18f;
    EASY_verts.verts[9] = 0.3f;
    EASY_verts.verts[12] = -0.35f;
    EASY_verts.verts[13] = 0.3f;
    graphic_element EASY_button = { names[10], EASY_verts, 0.4f, PRESSED_YES, BORDERS_YES, EASY_B };
    all_buttons[10] = EASY_button;

    vertices_t MED_verts = { 0 };
    MED_verts.presence = 1;
    MED_verts.verts[0] = -0.35f;
    MED_verts.verts[1] = 0.0f;
    MED_verts.verts[4] = -0.12f;
    MED_verts.verts[5] = 0.0f;
    MED_verts.verts[8] = -0.15f;
    MED_verts.verts[9] = 0.1f;
    MED_verts.verts[12] = -0.38f;
    MED_verts.verts[13] = 0.1f;
    graphic_element MED_button = { names[11], MED_verts, 0.4f, PRESSED_NO, BORDERS_YES, MED_B};
    all_buttons[11] = MED_button;

    vertices_t HARD_verts = { 0 };
    HARD_verts.presence = 1;
    HARD_verts.verts[0] = -0.32f;
    HARD_verts.verts[1] = -0.2f;
    HARD_verts.verts[4] = -0.147f;
    HARD_verts.verts[5] = -0.2f;
    HARD_verts.verts[8] = -0.177f;
    HARD_verts.verts[9] = -0.1f;
    HARD_verts.verts[12] = -0.35f;
    HARD_verts.verts[13] = -0.1f;
    graphic_element HARD_button = { names[12], HARD_verts, 0.4f, PRESSED_NO, BORDERS_YES, HARD_B};
    all_buttons[12] = HARD_button;

    vertices_t CON_verts = { 0 };
    CON_verts.presence = 1;
    CON_verts.verts[0] = -0.36f;
    CON_verts.verts[1] = -0.5f;
    CON_verts.verts[4] = -0.08f;
    CON_verts.verts[5] = -0.5f;
    CON_verts.verts[8] = -0.13f;
    CON_verts.verts[9] = -0.4f;
    CON_verts.verts[12] = -0.41f;
    CON_verts.verts[13] = -0.4f;
    graphic_element CON_button = { names[13], CON_verts, 0.4f, PRESSED_NO, BORDERS_YES, CON_B }; 
    all_buttons[13] = CON_button;

    r_info->new.first = 5;
    r_info->new.last = 13;

    // Create buttons
    vertices_t Add_Menu_verts = { 0 };
    Add_Menu_verts.presence = 1;      
    Add_Menu_verts.verts[0] = 0.0f; 
    Add_Menu_verts.verts[1] = 0.0f;   
    Add_Menu_verts.verts[4] = -0.12f; 
    Add_Menu_verts.verts[5] = 0.0f;   
    Add_Menu_verts.verts[8] = -0.15f; 
    Add_Menu_verts.verts[9] = 0.1f;   
    Add_Menu_verts.verts[12] = 0.0f;
    Add_Menu_verts.verts[13] = 0.1f;  
    graphic_element Add_Menu_button = { names[14], Add_Menu_verts, 0.4f, PRESSED_NO, BORDERS_NO, NOT_FOR_PRESSING_B };
    all_buttons[14] = Add_Menu_button;

    vertices_t Ship_Size_verts = { 0 };
    Ship_Size_verts.presence = 1;
    Ship_Size_verts.verts[0] = -0.1f;
    Ship_Size_verts.verts[1] = -0.1f;
    Ship_Size_verts.verts[4] = -0.12f;
    Ship_Size_verts.verts[5] = -0.1f;
    Ship_Size_verts.verts[8] = -0.15f;
    Ship_Size_verts.verts[9] = 0.0f;
    Ship_Size_verts.verts[12] = -0.1f;
    Ship_Size_verts.verts[13] = 0.0f;
    graphic_element Ship_Size_button = { names[15], Ship_Size_verts, 0.4f, PRESSED_NO, BORDERS_NO, NOT_FOR_PRESSING_B };
    all_buttons[15] = Ship_Size_button;

    vertices_t Ship_Size1_verts = { 0 };
    Ship_Size1_verts.presence = 1;
    Ship_Size1_verts.verts[0] = 0.05f;
    Ship_Size1_verts.verts[1] = -0.1f;
    Ship_Size1_verts.verts[4] = 0.1f;
    Ship_Size1_verts.verts[5] = -0.1f;
    Ship_Size1_verts.verts[8] = 0.1f;
    Ship_Size1_verts.verts[9] = 0.0f;
    Ship_Size1_verts.verts[12] = 0.05f;
    Ship_Size1_verts.verts[13] = 0.0f;
    graphic_element Ship_Size1_button = { names[16], Ship_Size1_verts, 0.4f, PRESSED_YES, BORDERS_YES, SHIP_SIZE1_B };
    all_buttons[16] = Ship_Size1_button;

    vertices_t Ship_Size2_verts = { 0 };
    Ship_Size2_verts.presence = 1;
    Ship_Size2_verts.verts[0] = 0.1f;
    Ship_Size2_verts.verts[1] = -0.1f;
    Ship_Size2_verts.verts[4] = 0.15f;
    Ship_Size2_verts.verts[5] = -0.1f;
    Ship_Size2_verts.verts[8] = 0.15f;
    Ship_Size2_verts.verts[9] = 0.0f;
    Ship_Size2_verts.verts[12] = 0.1f;
    Ship_Size2_verts.verts[13] = 0.0f;
    graphic_element Ship_Size2_button = { names[17], Ship_Size2_verts, 0.4f, PRESSED_NO, BORDERS_YES, SHIP_SIZE2_B };
    all_buttons[17] = Ship_Size2_button;

    vertices_t Ship_Size3_verts = { 0 };
    Ship_Size3_verts.presence = 1;
    Ship_Size3_verts.verts[0] = 0.15f;
    Ship_Size3_verts.verts[1] = -0.1f;
    Ship_Size3_verts.verts[4] = 0.2f;
    Ship_Size3_verts.verts[5] = -0.1f;
    Ship_Size3_verts.verts[8] = 0.2f;
    Ship_Size3_verts.verts[9] = 0.0f;
    Ship_Size3_verts.verts[12] = 0.15f;
    Ship_Size3_verts.verts[13] = 0.0f;
    graphic_element Ship_Size3_button = { names[18], Ship_Size3_verts, 0.4f, PRESSED_NO, BORDERS_YES, SHIP_SIZE3_B };
    all_buttons[18] = Ship_Size3_button;

    vertices_t Ship_Size4_verts = { 0 };
    Ship_Size4_verts.presence = 1;
    Ship_Size4_verts.verts[0] = 0.2f;
    Ship_Size4_verts.verts[1] = -0.1f;
    Ship_Size4_verts.verts[4] = 0.25f;
    Ship_Size4_verts.verts[5] = -0.1f;
    Ship_Size4_verts.verts[8] = 0.25f;
    Ship_Size4_verts.verts[9] = 0.0f;
    Ship_Size4_verts.verts[12] = 0.2f;
    Ship_Size4_verts.verts[13] = 0.0f;
    graphic_element Ship_Size4_button = { names[19], Ship_Size4_verts, 0.4f, PRESSED_NO, BORDERS_YES, SHIP_SIZE4_B };
    all_buttons[19] = Ship_Size4_button;

    vertices_t Ship_Size5_verts = { 0 };
    Ship_Size5_verts.presence = 1;
    Ship_Size5_verts.verts[0] = 0.25f;
    Ship_Size5_verts.verts[1] = -0.1f;
    Ship_Size5_verts.verts[4] = 0.3f;
    Ship_Size5_verts.verts[5] = -0.1f;
    Ship_Size5_verts.verts[8] = 0.3f;
    Ship_Size5_verts.verts[9] = 0.0f;
    Ship_Size5_verts.verts[12] = 0.25f;
    Ship_Size5_verts.verts[13] = 0.0f;
    graphic_element Ship_Size5_button = { names[20], Ship_Size5_verts, 0.4f, PRESSED_NO, BORDERS_YES, SHIP_SIZE5_B };
    all_buttons[20] = Ship_Size5_button;

    vertices_t V_verts = { 0 };
    V_verts.presence = 1;
    V_verts.verts[0] = 0.05f;
    V_verts.verts[1] = -0.2f;
    V_verts.verts[4] = 0.1f;
    V_verts.verts[5] = -0.2f;
    V_verts.verts[8] = 0.1f;
    V_verts.verts[9] = -0.1f;
    V_verts.verts[12] = 0.05f;
    V_verts.verts[13] = -0.1f;
    graphic_element V_button = { names[V_B], V_verts, 0.4f, PRESSED_YES, BORDERS_YES, V_B };
    all_buttons[21] = V_button;

    vertices_t H_verts = { 0 };
    H_verts.presence = 1;
    H_verts.verts[0] = 0.1f;
    H_verts.verts[1] = -0.2f;
    H_verts.verts[4] = 0.15f;
    H_verts.verts[5] = -0.2f;
    H_verts.verts[8] = 0.15f;
    H_verts.verts[9] = -0.1f;
    H_verts.verts[12] = 0.1f;
    H_verts.verts[13] = -0.1f;
    graphic_element H_button = { names[H_B], H_verts, 0.4f, PRESSED_NO, BORDERS_YES, H_B };
    all_buttons[22] = H_button;

    vertices_t Del_verts = { 0 };
    Del_verts.presence = 1;
    Del_verts.verts[0] = 0.05f;
    Del_verts.verts[1] = -0.4f;
    Del_verts.verts[4] = 0.1905f;
    Del_verts.verts[5] = -0.4f;
    Del_verts.verts[8] = 0.1605f;
    Del_verts.verts[9] = -0.3f;
    Del_verts.verts[12] = 0.02f;
    Del_verts.verts[13] = -0.3f;
    graphic_element Del_button = { names[DEL_B], Del_verts, 0.4f, PRESSED_NO, BORDERS_YES, DEL_B };
    all_buttons[23] = Del_button;
    
    vertices_t Play_verts = { 0 };
    Play_verts.presence = 1;
    Play_verts.verts[0] = 0.05f;
    Play_verts.verts[1] = -0.55f;
    Play_verts.verts[4] = 0.2205f;
    Play_verts.verts[5] = -0.55f;
    Play_verts.verts[8] = 0.1905f;
    Play_verts.verts[9] = -0.45f;
    Play_verts.verts[12] = 0.02f;
    Play_verts.verts[13] = -0.45f;
    graphic_element Play_button = { names[PLAY_B], Play_verts, 0.4f, PRESSED_NO, BORDERS_YES, PLAY_B };
    all_buttons[24] = Play_button;

    vertices_t Stat_verts = { 0 };
    Stat_verts.presence = 1;
    Stat_verts.verts[0] = -0.9f;
    Stat_verts.verts[1] = -0.55f;
    Stat_verts.verts[4] = -0.8f;
    Stat_verts.verts[5] = -0.55f;
    Stat_verts.verts[8] = -0.8f;
    Stat_verts.verts[9] = -0.45f;
    Stat_verts.verts[12] = -0.9f;
    Stat_verts.verts[13] = -0.45f;
    graphic_element Stat_button = { names[STAT_B], Stat_verts, 0.4f, PRESSED_NO, BORDERS_NO, NOT_FOR_PRESSING_B};
    all_buttons[STAT_B] = Stat_button;

    vertices_t NOTE1_verts = { 0 };
    NOTE1_verts.presence = 1;
    NOTE1_verts.verts[0] = -0.9f;
    NOTE1_verts.verts[1] = -0.65f;
    NOTE1_verts.verts[4] = -0.8f;
    NOTE1_verts.verts[5] = -0.65f;
    NOTE1_verts.verts[8] = -0.8f;
    NOTE1_verts.verts[9] = -0.55f;
    NOTE1_verts.verts[12] = -0.9f;
    NOTE1_verts.verts[13] = -0.55f;
    graphic_element NOTE1_button = { names[NOTE1_B], NOTE1_verts, 0.3f, PRESSED_NO, BORDERS_NO, NOT_FOR_PRESSING_B };
    all_buttons[NOTE1_B] = NOTE1_button;
    
    r_info->create.first = 14;
    r_info->create.last = 26;
    // Game buttons
    all_buttons[27] = Stat_button;

    vertices_t NOTE2_verts = { 0 };
    NOTE2_verts.presence = 1;
    NOTE2_verts.verts[0] = -0.9f;
    NOTE2_verts.verts[1] = -0.65f;
    NOTE2_verts.verts[4] = -0.8f;
    NOTE2_verts.verts[5] = -0.65f;
    NOTE2_verts.verts[8] = -0.8f;
    NOTE2_verts.verts[9] = -0.55f;
    NOTE2_verts.verts[12] = -0.9f;
    NOTE2_verts.verts[13] = -0.55f;
    graphic_element NOTE2_button = { names[NOTE2_B], NOTE2_verts, 0.3f, PRESSED_NO, BORDERS_NO, NOT_FOR_PRESSING_B };
    all_buttons[NOTE2_B + 1] = NOTE2_button;

    vertices_t PLAYER1_verts = { 0 };
    PLAYER1_verts.presence = 1;
    PLAYER1_verts.verts[0] = -0.1f;
    PLAYER1_verts.verts[1] = 0.0f;
    PLAYER1_verts.verts[4] = -0.8f;
    PLAYER1_verts.verts[5] = 0.0f;
    PLAYER1_verts.verts[8] = -0.8f;
    PLAYER1_verts.verts[9] = 0.1f;
    PLAYER1_verts.verts[12] = -0.91;
    PLAYER1_verts.verts[13] = 0.1f;
    graphic_element PLAYER1_button = { names[PLAYER2_B], PLAYER1_verts, 0.4f, PRESSED_NO, BORDERS_NO, NOT_FOR_PRESSING_B };
    all_buttons[PLAYER1_B] = PLAYER1_button;

    vertices_t PLAYER2_verts = { 0 };
    PLAYER2_verts.presence = 1;
    PLAYER2_verts.verts[0] = -0.9f;
    PLAYER2_verts.verts[1] = -0.1f;
    PLAYER2_verts.verts[4] = -0.8f;
    PLAYER2_verts.verts[5] = -0.1f;
    PLAYER2_verts.verts[8] = -0.8f;
    PLAYER2_verts.verts[9] = 0.0f;
    PLAYER2_verts.verts[12] = -0.9f;
    PLAYER2_verts.verts[13] = 0.0f;
    graphic_element PLAYER2_button = { names[PLAYER1_B], PLAYER2_verts, 0.4f, PRESSED_NO, BORDERS_NO, NOT_FOR_PRESSING_B };
    all_buttons[PLAYER2_B] = PLAYER2_button; 

    r_info->game.first = 27;
    r_info->game.last = 30;

    // Save buttons
    all_buttons[31] = Stat_button;
    
    vertices_t NOTE3_verts = { 0 };
    NOTE3_verts.presence = 1;
    NOTE3_verts.verts[0] = -0.9f;
    NOTE3_verts.verts[1] = -0.65f;
    NOTE3_verts.verts[4] = -0.8f;
    NOTE3_verts.verts[5] = -0.65f;
    NOTE3_verts.verts[8] = -0.8f;
    NOTE3_verts.verts[9] = -0.55f;
    NOTE3_verts.verts[12] = -0.9f;
    NOTE3_verts.verts[13] = -0.55f;
    graphic_element NOTE3_button = { names[NOTE3_B], NOTE3_verts, 0.3f, PRESSED_NO, BORDERS_NO, NOT_FOR_PRESSING_B };
    all_buttons[NOTE3_B] = NOTE2_button;

    vertices_t NAME_verts = { 0 };
    NAME_verts.presence = 1;
    NAME_verts.verts[0] = -0.18f;
    NAME_verts.verts[1] = 0.0f;
    NAME_verts.verts[4] = 0.2f;
    NAME_verts.verts[5] = 0.0f;
    NAME_verts.verts[8] = 0.2f;
    NAME_verts.verts[9] = 0.1f;
    NAME_verts.verts[12] = -0.18f;
    NAME_verts.verts[13] = 0.1f;
    graphic_element NAME_button = { names[NAME_B], NAME_verts, 0.4f, PRESSED_NO, BORDERS_YES, NOT_FOR_PRESSING_B };
    all_buttons[NAME_B] = NAME_button;

    vertices_t ENTER_verts = { 0 };
    ENTER_verts.presence = 1; 
    ENTER_verts.verts[0] = -0.15f; 
    ENTER_verts.verts[1] = 0.12f; 
    ENTER_verts.verts[4] = 0.2f; 
    ENTER_verts.verts[5] = 0.12f;
    ENTER_verts.verts[8] = 0.2f; 
    ENTER_verts.verts[9] = 0.22f; 
    ENTER_verts.verts[12] = -0.15f; 
    ENTER_verts.verts[13] = 0.22f; 
    graphic_element ENTER_button = { names[ENTER_B], ENTER_verts, 0.4f, PRESSED_NO, BORDERS_NO, NOT_FOR_PRESSING_B };
    all_buttons[ENTER_B] = ENTER_button;

    vertices_t DEL_S_verts = { 0 };
    DEL_S_verts.presence = 1;
    DEL_S_verts.verts[0] = -0.5f;
    DEL_S_verts.verts[1] = -0.15f;
    DEL_S_verts.verts[4] = -0.27f;
    DEL_S_verts.verts[5] = -0.15f;
    DEL_S_verts.verts[8] = -0.3f;
    DEL_S_verts.verts[9] = -0.05f;
    DEL_S_verts.verts[12] = -0.53f;
    DEL_S_verts.verts[13] = -0.05f;
    graphic_element DEL_S_button = { names[DEL_S_B], DEL_S_verts, 0.4f, PRESSED_NO, BORDERS_YES, DEL_S_B };
    all_buttons[DEL_S_B] = DEL_S_button;

    vertices_t SAVE_S_verts = { 0 };
    SAVE_S_verts.presence = 1;
    SAVE_S_verts.verts[0] = -0.5f;
    SAVE_S_verts.verts[1] = -0.3f;
    SAVE_S_verts.verts[4] = -0.27f;
    SAVE_S_verts.verts[5] = -0.3f;
    SAVE_S_verts.verts[8] = -0.3f;
    SAVE_S_verts.verts[9] = -0.2f;
    SAVE_S_verts.verts[12] = -0.53f;
    SAVE_S_verts.verts[13] = -0.2f;
    graphic_element SAVE_S_button = { names[SAVE_S_B], SAVE_S_verts, 0.4f, PRESSED_NO, BORDERS_YES, SAVE_S_B };
    all_buttons[SAVE_S_B] = SAVE_S_button;

    r_info->save.first = 31;
    r_info->save.last = 36;
    // Load buttons
    // Records buttons
}
void render_element(graphic_element element, const unsigned int VBO)
{
    vertices_t vertices[50];
    gen_render_data(vertices, element);
    render_data(vertices, VBO);
}
void gen_render_data(vertices_t* vertices, graphic_element element)
{
    int indexes[50] = {0};
    get_chars(indexes, element);
    get_tex_vertices(vertices, indexes);
    get_vertices(vertices, element);
    get_borders(vertices, element);
    get_pressing(vertices, element);
}
void render_data(vertices_t* vertices, const unsigned int VBO)
{
    int i = 0;
    while (i < 50 && vertices[i].presence == 1)
    {
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, 16 * sizeof(float), vertices[i].verts, GL_STATIC_DRAW);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
        i++;
    }
}

void get_chars(int * indexes, graphic_element element)
{
    int i = 0;
    int j = 0;
    while (i < 50 && element.view_info[i] != '\0' && element.view_info[i] != '/')
    {
        if ((indexes[j] = get_char_index(element.view_info[i])) != -1)
        {
            j++;
        }
        i++;
    }
    if (element.view_info[i] == '/') i++;
    while (i < 50 && element.view_info[i] != '\0')
    {
        if ((indexes[j] = get_char_index(element.view_info[i]) + 100) != -1)
        {
            j++;
        }
        i++;
    }
    if (j < 50) indexes[j] = -1;
}
int get_char_index(char example)
{
    int index = -1;
    int i = 0;
    char alph[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ";
    while (i < 38)
    {
        if (example == alph[i])
        {
            index = i;
            break;
        }
        i++;
    }
    return index;
}
void get_tex_vertices(vertices_t* vertices, const int* indexes)
{
    int i = 0;
    while (i < 50 && indexes[i] != -1 && indexes[i] < 100)
    {
        vertices[i].presence = 1;
        get_tex_vertices_one(vertices, indexes, i);
        i++;
    }
    while (i < 50 && indexes[i] != -1)
    {
        vertices[i].presence = 1;
        get_tex_vertices_one(vertices, indexes, i);
        i++;
    }
    if (i < 50) vertices[i].presence = 0;
}
void get_tex_vertices_one(vertices_t* vertices, const int* indexes, int position)
{
    float cord1v = 0.0f;
    float cord1h = 0.0f;
    float cord2v = 0.0f;
    float cord2h = 0.0f;
    float cord3v = 0.0f;
    float cord3h = 0.0f;
    float cord4v = 0.0f;
    float cord4h = 0.0f;
    if (indexes[position] >= 100)
    {
        cord1v = 650.0f / 700.0f - (float)(indexes[position] - 100) * 50.0f / 700.0f;
        cord1h = 650.0f / 700.0f;
        cord2v = 650.0f / 700.0f - (float)(indexes[position] - 100) * 50.0f / 700.0f;
        cord2h = 700.0f / 700.0f;
        cord3v = 700.0f / 700.0f - (float)(indexes[position] - 100) * 50.0f / 700.0f;
        cord3h = 700.0f / 700.0f;
        cord4v = 700.0f / 700.0f - (float)(indexes[position] - 100) * 50.0f / 700.0f;
        cord4h = 650.0f / 700.0f;
    }
    else if (indexes[position] != 36)
    {
        int vert = -1 * (indexes[position] / 6);
        int hor = indexes[position] % 6;
        float vert_coord = 0.0f;
        float hor_coord = 0.0f;
        while (vert++) { vert_coord -= 1.0f; }
        while (hor--) { hor_coord += 1.0f; }
        vert_coord = (645.0f + (533.0f / 5.0f) * vert_coord) / 700.0f;
        hor_coord = (55.0f + (533.0f / 5.0f) * hor_coord) / 700.0f;
        cord1v = vert_coord - 40.0f / 700.0f;
        cord1h = hor_coord - 30.0f / 700.0f;
        cord2v = vert_coord - 40.0f / 700.0f;
        cord2h = hor_coord + 30.0f / 700.0f;
        cord3v = vert_coord + 40.0f / 700.0f;
        cord3h = hor_coord + 30.0f / 700.0f;
        cord4v = vert_coord + 40.0f / 700.0f;
        cord4h = hor_coord - 30.0f / 700.0f;
    }
    else
    {
        cord1v = 660.0f / 700.0f;
        cord1h = 660.0f / 700.0f;
        cord2v = 660.0f / 700.0f;
        cord2h = 690.0f / 700.0f;
        cord3v = 690.0f / 700.0f;
        cord3h = 690.0f / 700.0f;
        cord4v = 690.0f / 700.0f;
        cord4h = 660.0f / 700.0f;
    }

    vertices[position].verts[2] = cord1h;
    vertices[position].verts[3] = cord1v;
    vertices[position].verts[6] = cord2h;
    vertices[position].verts[7] = cord2v;
    vertices[position].verts[10] = cord3h;
    vertices[position].verts[11] = cord3v;
    vertices[position].verts[14] = cord4h;
    vertices[position].verts[15] = cord4v;
}
void get_vertices(vertices_t* vertices, graphic_element element)
{
    if (vertices->verts[2] == 650.0f / 700.0f)
    {
        vertices[0].verts[0 ]  = element.element_vertices.verts[0 ];
        vertices[0].verts[1 ]  = element.element_vertices.verts[1 ];
        vertices[0].verts[4 ]  = element.element_vertices.verts[4 ];
        vertices[0].verts[5 ]  = element.element_vertices.verts[5 ];
        vertices[0].verts[8 ]  = element.element_vertices.verts[8 ];
        vertices[0].verts[9 ]  = element.element_vertices.verts[9 ];
        vertices[0].verts[12] = element.element_vertices.verts [12];
        vertices[0].verts[13] = element.element_vertices.verts [13];
        return;
    }
    float button_fatness = element.element_vertices.verts[13] - element.element_vertices.verts[1];
    float invisible_lower_border = button_fatness * (1.0f - element.text_size) / 2.0f + element.element_vertices.verts[1];
    float invisible_left_border = button_fatness * 0.1f + element.element_vertices.verts[0];
    float text_height = button_fatness * element.text_size;
    float next_letter_step = text_height * 0.75f;

    float example1h = invisible_left_border;
    float example1v = invisible_lower_border;
    float example2h = invisible_left_border + next_letter_step;
    float example2v = invisible_lower_border;
    float example3h = invisible_left_border + next_letter_step;
    float example3v = invisible_lower_border + text_height;
    float example4h = invisible_left_border;
    float example4v = invisible_lower_border + text_height;

    vertices[0].verts[0]  = example1h;
    vertices[0].verts[1] = example1v;
    vertices[0].verts[4] = example2h;
    vertices[0].verts[5] = example2v;
    vertices[0].verts[8] = example3h;
    vertices[0].verts[9] = example3v;
    vertices[0].verts[12] = example4h;
    vertices[0].verts[13] = example4v;

    int i = 1;
    while (vertices[i].presence == 1)
    {
        vertices[i].verts[0] = vertices[i - 1].verts[0] + next_letter_step;
        vertices[i].verts[1] = vertices[i - 1].verts[1];
        vertices[i].verts[4] = vertices[i - 1].verts[4] + next_letter_step;
        vertices[i].verts[5] = vertices[i - 1].verts[5];
        vertices[i].verts[8] = vertices[i - 1].verts[8] + next_letter_step;
        vertices[i].verts[9] = vertices[i - 1].verts[9];
        vertices[i].verts[12] = vertices[i - 1].verts[12] + next_letter_step;
        vertices[i].verts[13] = vertices[i - 1].verts[13];
        i++;
    }
}
void get_borders(vertices_t* vertices, graphic_element element)
{
    if (element.have_i_borders == 1)
    {
        int i = 0;
        while (vertices[i].presence == 1) { i++; }
        vertices[i] = element.element_vertices;
        vertices[i].verts[2] = 651.5f/700.f;
        vertices[i].verts[3] = 651.5f / 700.f;
        vertices[i].verts[6] = 698.5f / 700.f;
        vertices[i].verts[7] = 651.5f / 700.f;
        vertices[i].verts[10] = 698.5f / 700.f;
        vertices[i].verts[11] = 698.5f / 700.f;
        vertices[i].verts[14] = 651.5f / 700.f;
        vertices[i].verts[15] = 698.5f / 700.f;
        vertices[i].presence = 1;
    }
}
void get_pressing(vertices_t* vertices, graphic_element element)
{
    if (element.am_i_pressed == 1)
    {
        int i = 0;
        while (vertices[i].presence == 1) { i++; }
        vertices[i] = element.element_vertices;
        vertices[i].verts[2] = 451.0f / 700.f;
        vertices[i].verts[3] = 2.0f / 700.f;
        vertices[i].verts[6] = 500.0f / 700.f;
        vertices[i].verts[7] = 2.0f / 700.f;
        vertices[i].verts[10] = 500.0f / 700.f;
        vertices[i].verts[11] = 49.0f / 700.f;
        vertices[i].verts[14] = 451.0f / 700.f;
        vertices[i].verts[15] = 49.0f / 700.f;
        vertices[i].presence = 1;
    }
}
GLuint load_shaders()
{
    GLchar* vertex_shader_src =
        "#version 330 core\n"
        "in vec2 aPos;\n"
        "in vec2 tex_cord;\n"
        "out vec2 v_TexCord;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, 1.0f, 1.0f);\n"
        "   v_TexCord = tex_cord;\n"
        "}\n";

    GLchar* fragment_shader_src =
        "#version 330 core\n"
        "out vec4 color;\n"
        "in vec2 v_TexCord;\n"
        "\n"
        "uniform sampler2D u_TexSlot;\n"
        "uniform vec4 u_Color;\n"
        "void main()\n"
        "{\n"
        "   vec4 TexCol = texture(u_TexSlot, v_TexCord);\n"
        "   color = TexCol + u_Color;\n"
        "}\n";
    GLuint shader = CreateProgram(&vertex_shader_src, 1, &fragment_shader_src, 1);
    return shader;
}
GLuint selecting_texture(const char* address)
{
    char filepath[100];
    strcpy(filepath, address);
    unsigned char* LocBuf = NULL;
    GLuint texture_id;
    unsigned int slot = 0;
    int Width = 0, Hight = 0, BitsPerPix = 0;

    stbi_set_flip_vertically_on_load(1);
    LocBuf = stbi_load(filepath, &Width, &Hight, &BitsPerPix, 4);
    if (!LocBuf) return 0;

    glGenTextures(1, &texture_id);
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Width, Hight, 0, GL_RGBA, GL_UNSIGNED_BYTE, LocBuf);// ?
    //glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(LocBuf);
    return texture_id;
}
static GLuint CreateProgram(GLchar** vsh_src, GLsizei length_vsh, GLchar** fsh_src, GLsizei length_fsh)
{
    //Getting id'es of shaders and program
    GLuint program = glCreateProgram();
    GLuint vsh_id = CreateShader(GL_VERTEX_SHADER, vsh_src, length_vsh);
    GLuint fsh_id = CreateShader(GL_FRAGMENT_SHADER, fsh_src, length_fsh);

    //Doing things to link all
    glAttachShader(program, vsh_id);
    glAttachShader(program, fsh_id);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vsh_id);
    glDeleteShader(fsh_id);

    return program;
}
static GLuint CreateShader(GLenum shaderType, GLchar** src, GLsizei length)
{
    GLuint id = glCreateShader(shaderType);
    glShaderSource(id, length, src, NULL);
    glCompileShader(id);
    return id;
}