#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include <Windows.h> 
#include <mmsystem.h> 
#pragma comment(lib, "Winmm.lib")

#include "program_logic.h"

#define HOW_MANY_BUTTONS 1000

void InitGL();
void processInput(GLFWwindow*, int*, double*, double*);
void press_coords(float *, float *, double, double, const int, const int);
int check_pressing(graphic_element *, float, float, render_info, cur_game_info);
int check_hum_field_pressing(float, float, cur_game_info);
int check_com_field_pressing(float, float, cur_game_info);
int check_Keybord_pressing(float x_pos, float y_pos, render_info* r_info, graphic_element* all_buttons);
// Make Del buttn behavour
int main()
{ 
    //PlaySound((LPCWSTR)"music.wav", NULL, SND_ALIAS);
    //wchar_t* txt = L"0.wav";
    //PlaySound(txt, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP); 
    srand((unsigned int)time(NULL));
    InitGL();
    int win_size1 = 1920;
    int win_size2 = 950;
    double x = 0.0;
    double y = 0.0;
    float x_pos = -1.0f;
    float y_pos = 1.0f;
    int press_status;
    GLFWwindow* window = glfwCreateWindow(win_size1, win_size2, "SeaBattle", NULL , NULL); 
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    gladLoadGL();
    GLuint shader = load_shaders();
    glUseProgram(shader);

    //uniforms
    int TexSlot_location = glGetUniformLocation(shader, "u_TexSlot");
    if (TexSlot_location == -1) return 1;
    glUniform1i(TexSlot_location, GL_TEXTURE0);

    int location = glGetUniformLocation(shader, "u_Color"); 
    if (location == -1) return 1;
    float red = 0.1f;
    float blue = 0.1f;
    float red_incr = 0.000f; 
    float blue_incr= 0.001f; 
    glUniform4f(location, red, 0.0f, blue, 0.0f);

    // Buffers
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, 0.0f,//0
         0.5f, -0.5f, 1.0f, 0.0f,//1
         0.5f,  0.5f, 1.0f, 1.0f,//2
        -0.5f,  0.5f, 0.0f, 1.0f //3
    };
    unsigned int elements[] =
    {
        0, 1, 2,
        2, 3, 0
    };
    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLint posAttrib = glGetAttribLocation(shader, "aPos");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);

    GLint texAttrib = glGetAttribLocation(shader, "tex_cord");
    glEnableVertexAttribArray(texAttrib);
    glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));

    unsigned int IBO;
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

    //textures
    char address[] = "texturers/alph.png";
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    GLuint texture_id = selecting_texture(address);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    /*
    glUseProgram(shader);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glUniform1i(TexSlot_location, GL_TEXTURE0 + 0);
    */

    //graphic_element all_buttons[HOW_MANY_BUTTONS] = { 0 };
    graphic_element *all_buttons = (graphic_element* )malloc(HOW_MANY_BUTTONS * sizeof(graphic_element));
    if (all_buttons == NULL) return 0;
    render_info r_info = (render_info){ 0 };
    r_info.status = NEW;
    // Saving texts of buttons 
    char name0[] = "  NEW";
    char name1[] = "  GAME";
    char name2[] = "  LOAD";
    char name3[] = "  SAVE";
    char name4[] = "RECORDS";

    char name5[] = "SIZE";
    char name6[] = "10";
    char name7[] = "15";
    char name8[] = "2 COMPUTERS";
    char name9[] = " HUMAN AND COMPUTER";
    char name10[] = "EASY";
    char name11[] = "MEDIUM";
    char name12[] = "HARD";
    char name13[] = "CONFIRM";
    char name14[] = "ADD MENU";
    char name15[] = "SIZE";
    char name16[] = "1";
    char name17[] = "2";
    char name18[] = "3";
    char name19[] = "4";
    char name20[] = "5";
    char name21[] = "V";
    char name22[] = "H";
    char name23[] = "DEL";
    char name24[] = "PLAY";
    char name25[] = "STATUS";
    char name26[] = "TRY TO ADD A SHIP|SUCCESS|INVALID|TOO MUCH|TOO BIG";
    name26[17] = '\0';
    name26[25] = '\0';
    name26[33] = '\0';
    name26[42] = '\0';
    char name27[] = "MAKE A SHOT|PLAYER1 DIRECT HIT|PLAYER1 MISS|PLAYER2 DIRECT HIT|PLAYER2 MISS";
    name27[11] = '\0';
    name27[30] = '\0';
    name27[43] = '\0';
    name27[62] = '\0';
    char name29[] = "PLAYER1";
    char name30[] = "PLAYER2";
    char name32[] = "MAKE A SAVE|PLAYER1 WINNED|PLAYER2 WINNED";
    name32[11] = '\0';
    name32[26] = '\0';
    char name33[12] = "          ";
    char name34[] = "ENTER NAME";
    char name35[] = "DELETE";
    char name36[] = " SAVE";

    char* names[HOW_MANY_BUTTONS] = {0};
    names[0] = name0;
    names[1] = name1;
    names[2] = name2;
    names[3] = name3;
    names[4] = name4;
    names[5 ] = name5 ;
    names[6 ] = name6 ;
    names[7 ] = name7 ;
    names[8 ] = name8 ;
    names[9 ] = name9 ;
    names[10] = name10;
    names[11] = name11;
    names[12] = name12;
    names[13] = name13;
    names[14] = name14;
    names[15] = name15;
    names[16] = name16;
    names[17] = name17;
    names[18] = name18;
    names[19] = name19;
    names[20] = name20;
    names[21] = name21;
    names[22] = name22;
    names[23] = name23;
    names[24] = name24;
    names[25] = name25;
    names[26] = name26;
    names[27] = name27;
    names[29] = name29;
    names[30] = name30;
    names[32] = name32;
    names[33] = name33;
    names[34] = name34;
    names[35] = name35;
    names[36] = name36;

    making_buttons(all_buttons, &r_info, names);
    int pressed_index = -1;
    int message = 0;
    float r = (float)(rand() % 3) + 2.3f;
    float green_c = r / 10.0f;
    float green_incr = 0.00026f;

    cur_game_info g_info = (cur_game_info){ 0 };
    int x_shot = 0;
    int y_shot = 0;
    int win_status = 0;
    r_info.status = NEW;
    /*
    r_info.status = GAME;
    win_status = 1;
    */
    float red_c = 0.2f;
    while (!glfwWindowShouldClose(window))
    {
        
        if (all_buttons[NOTE1_B].view_info != name26)
        {
            all_buttons[NOTE1_B].view_info = name26;
            PlaySound(L"1.wav", NULL, SND_FILENAME);
        }
        if (all_buttons[NOTE2_B + 1].view_info != name27)
        {
            all_buttons[NOTE2_B + 1].view_info = name27;
            PlaySound(L"1.wav", NULL, SND_FILENAME);
        }
        if (all_buttons[NOTE3_B].view_info != name32)
        {
            all_buttons[NOTE3_B].view_info = name32;
            PlaySound(L"2.wav", NULL, SND_FILENAME);
            
        }
        processInput(window, &press_status, &x, &y);
        if (x != 0.0 || y != 0.0)
        {
            press_coords(&x_pos, &y_pos, x, y, win_size1, win_size2);
            pressed_index = check_pressing(all_buttons, x_pos, y_pos, r_info, g_info);
        }
        if (r_info.status == SAVE)
        {
            check_Keybord_pressing(x_pos,  y_pos, &r_info,  all_buttons); 
        }
        if (pressed_index >= 0)
        {
            //printf("%d\n", pressed_index);
            //if (pressed_index >= 2000) PlaySound(L"1.wav", NULL, SND_FILENAME | SND_ASYNC);
            message = next_frame(all_buttons, &r_info, &g_info, pressed_index);
            if (message == 1)
            {
                all_buttons[NOTE1_B].view_info += 18;
            }                                                           
            else if (message == ADDING_ERROR_INVALID_PLACEMENT)         
            {                                                           
                all_buttons[NOTE1_B].view_info += 26;                                                                
            }                                                           
            else if (message == ADDING_ERROR_TOO_MUCH_SAME_SIZE)        
            {                                                           
                all_buttons[NOTE1_B].view_info += 34;                                                                   
            }                                                            
            else if (message == ADDING_ERROR_5CELL_SHIP_IN_10X10_FIELD)  
            {                                                            
                all_buttons[NOTE1_B].view_info += 43;                                                                     
            }
            else if (message == 3)
            {
                all_buttons[NOTE2_B + 1].view_info += 12;
            }
            else if (message == 4)
            {
                all_buttons[NOTE2_B + 1].view_info += 31;
            }
        }
        green_c = green_c + green_incr;
        if (green_c > 0.6f)
        {
            green_incr = -0.00019f;
        }
        else if (green_c < 0.3f)
        {
            green_incr = 0.00017f;
        }
        if (red_incr != 0.0f)
        {
            red = red + red_incr;
            if (red > 0.19f)
            {
                red_incr = -0.0004f;
            }
            else if (red <= 0.1f)
            {
                red_incr = 0.0f;
                blue_incr = 0.001f;
            }
        }
        else if (blue_incr != 0.0f)
        {
            blue = blue + blue_incr;
            if (blue > 0.3f)
            {
                blue_incr = -0.0003f;
            }
            else if (blue <= 0.1f)
            {
                blue_incr = 0.0f;
                red_incr = 0.0004f;
            }
        }

        x_shot = 0;
        y_shot = 0;
        
        if (r_info.status == GAME && all_buttons[NOTE2_B + 1].view_info == name27)
        {
            if ((win_status = check_end_of_game(&g_info)) != 0)
            {
                if (win_status == 1)
                {
                    all_buttons[NOTE3_B].view_info += 12;
                }
                else if (win_status == 2)
                {
                    all_buttons[NOTE3_B].view_info += 27;
                }
                g_info.am_i_finished = 1;
                r_info.status = SAVE;
                red_c = 1;
                green_c = 1;
            }
            if (win_status == 0 && g_info.is_there_human)
            {
                if (g_info.is_humans_current_shot == 0)
                {
                    find_best_shot(g_info.hum_com, g_info.size, &x_shot, &y_shot);
                    make_shot(g_info.hum_com, g_info.armada_hum_com, x_shot, y_shot);
                    g_info.how_many_shots_made++;
                    message = update_render_after_shot(&g_info, x_shot, y_shot);
                    if (message == 6)
                    {
                        g_info.is_humans_current_shot = 1;
                    }
                }
            }
            else if(win_status == 0)
            {
                if (g_info.is_humans_current_shot)
                {
                    find_best_shot(g_info.com, g_info.size, &x_shot, &y_shot);
                    make_shot(g_info.com, g_info.armada_com, x_shot, y_shot);
                    g_info.how_many_shots_made++;
                    message = update_render_after_shot(&g_info, x_shot, y_shot);
                    if (message == 4)
                    {
                        g_info.is_humans_current_shot = 0;
                    }
                }
                else
                {
                    find_best_shot(g_info.hum_com, g_info.size, &x_shot, &y_shot);
                    make_shot(g_info.hum_com, g_info.armada_hum_com, x_shot, y_shot);
                    g_info.how_many_shots_made++;
                    message = update_render_after_shot(&g_info, x_shot, y_shot);
                    if (message == 6)
                    {
                        g_info.is_humans_current_shot = 1;
                    }
                }
            }
            if (message == 5)
            {
                all_buttons[NOTE2_B + 1].view_info += 44;
            }
            else if (message == 6)
            {
                all_buttons[NOTE2_B + 1].view_info += 63; 
            }
            else if (message == 3)
            {
                all_buttons[NOTE2_B + 1].view_info += 12;
            }
            else if (message == 4)
            {
                all_buttons[NOTE2_B + 1].view_info += 31;
            }
            message = 0;
        }
        glClearColor(red_c, green_c, 0.6f, 0.0f); 
        glClear(GL_COLOR_BUFFER_BIT);  
        render_scene(all_buttons, r_info, &g_info, VBO); 
        glUniform4f(location, red, 0.0f, blue, 0.0f); 

        x_pos = -1.0f;
        y_pos = 1.0f;
        x = 0.0;
        y = 0.0;
        pressed_index = -1;
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteTextures(1, &texture_id);
    glDeleteProgram(shader);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    glfwTerminate();
	return EXIT_SUCCESS;
}
void InitGL()
{
    if (!glfwInit()) { exit(0); }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}
void processInput(GLFWwindow* window, int *press_status, double *x, double *y)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    if (*press_status == GLFW_PRESS && glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
    {
        glfwGetCursorPos(window, x, y);
    }
    *press_status = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
}
void press_coords(float* x_pos, float* y_pos, double x, double y, const int size1, const int size2)
{
    *x_pos = ((float)x / (float)size1) * 2.0f - 1.0f;
    *y_pos = ((float)y / (float)size2) * -2.0f + 1.0f;
}
int check_pressing(graphic_element *element, float x_pos, float y_pos, render_info r_info, cur_game_info g_info)
{
    int answer = -2;
    int i = 0;
    int j = 4;
    int field_pressing = 0;
    while (i <= j)
    {
        if (x_pos > element[i].element_vertices.verts[0] && x_pos < element[i].element_vertices.verts[4] &&
            y_pos > element[i].element_vertices.verts[1] && y_pos < element[i].element_vertices.verts[9])
        {
            answer = element[i].action_index;
            break;
        }
        i++;
    }
    if (answer != -2)
    {
        return answer;
    }
    if (r_info.status == NEW)
    {
        i = r_info.new.first;
        j = r_info.new.last;
    }
    if (r_info.status == CREATE)
    {
        i = r_info.create.first;
        j = r_info.create.last;
        if ((field_pressing = check_hum_field_pressing(x_pos, y_pos, g_info)) != 0)
        {
            return field_pressing;
        }
    }
    else if (r_info.status == GAME)
    {
        i = r_info.game.first;
        j = r_info.game.last;
        if ((field_pressing = check_com_field_pressing(x_pos, y_pos, g_info)) != 0 && g_info.is_there_human == 1)
        {
            return field_pressing;
        }
    }
    else if (r_info.status == LOAD)
    {
        i = r_info.load.first;
        j = r_info.load.last;
    }
    else if (r_info.status == SAVE)
    {
        i = r_info.save.first;
        j = r_info.save.last;
    }
    else if (r_info.status == RECORDS)
    {
        i = r_info.records.first;
        j = r_info.records.last;
    }
    while (i <= j)
    {
        if (x_pos > element[i].element_vertices.verts[0] && x_pos < element[i].element_vertices.verts[4] &&
            y_pos > element[i].element_vertices.verts[1] && y_pos < element[i].element_vertices.verts[9])
        {
            answer = element[i].action_index;
            break;
        }
        i++;
    }
    if (answer >= 0)
    {
        element[i].am_i_pressed++;
        element[i].am_i_pressed = element[i].am_i_pressed % 2;
    }
    
    return answer;
}
int check_hum_field_pressing(float x_pos, float y_pos, cur_game_info g_info)
{
    int size = g_info.size;
    float hor_step = (0.7f / (float)size) * 0.66f;
    float vert_step = -0.9f / (float)size;
    float x1 = -0.975f;
    float x2 = -0.975f + (float)size * hor_step;
    float y1 = 0.95f;
    float y2 = 0.95f + (float)size * vert_step;
    if (x_pos < x1 || x_pos > x2 || y_pos < y2 || y_pos > y1)
    {
        return 0;
    }
    int x_cord = (int)((x_pos - x1) / hor_step);
    int y_cord = size - (int)((y2 - y_pos) / vert_step) - 1;

printf("Hum field touch: x: %d, y: %d;\n", x_cord, y_cord);
    return 1000 + y_cord * size + x_cord;
}
int check_com_field_pressing(float x_pos, float y_pos, cur_game_info g_info)
{
    if (g_info.is_there_human == 0 || g_info.is_humans_current_shot == 0 && g_info.is_there_human == 1)
        return 0;
    int size = g_info.size;
    float hor_step = (0.7f / (float)size) * 0.66f;
    float vert_step = -0.9f / (float)size;
    float x1 = -0.225f;
    float x2 = -0.225f + (float)size * hor_step;
    float y1 = -0.05f;
    float y2 = -0.05f + (float)size * vert_step;
    if (x_pos < x1 || x_pos > x2 || y_pos < y2 || y_pos > y1)
    {
        return 0;
    }
    int x_cord = (int)((x_pos - x1) / hor_step);
    int y_cord = size - (int)((y2 - y_pos) / vert_step) - 1;

printf("Com field touch: x: %d, y: %d;\n", x_cord, y_cord);
    return 2000 + y_cord * size + x_cord;
}
int check_Keybord_pressing(float x_pos, float y_pos, render_info *r_info, graphic_element* all_buttons)
{
    if (r_info->status != SAVE)
        return 0;
    int size = 6;
    float hor_step = (0.7f / (float)size) * 0.66f;
    float vert_step = -0.9f / (float)size;
    float x1 = -0.225f;
    float x2 = -0.225f + (float)size * hor_step;
    float y1 = -0.05f;
    float y2 = -0.05f + (float)size * vert_step;
    if (x_pos < x1 || x_pos > x2 || y_pos < y2 || y_pos > y1)
    {
        return 0;
    }
    int x_cord = (int)((x_pos - x1) / hor_step);
    int y_cord = size - (int)((y2 - y_pos) / vert_step) - 1;
    int i = 0;
    while (i < 10 && all_buttons[NAME_B].view_info[i] != ' ')
    {
        i++;
    }
    if (i > 9) return 0;
    char v = 0;
    v = (char)(y_cord * size + x_cord + 'A');
    if (v > 'Z')
    {
        v -= 'Z';
        v += '0' - 1;
    }
    all_buttons[NAME_B].view_info[i] = v;
    printf("Keybord touch: x: %d, y: %d;\n", x_cord, y_cord);
    return 3000 + y_cord * size + x_cord;
}