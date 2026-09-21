#ifndef GUI_H
#define GUI_H

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_GLFW_GL3_IMPLEMENTATION

#define MAX_VERTEX_BUFFER  512 * 1024
#define MAX_ELEMENT_BUFFER 512 * 1024

struct nk_glfw glfw;
struct nk_context *ctx;
struct nk_colorf bg;

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../../vendor/nuklear.h"
#include "../../vendor/nuklear_glfw_gl3.h"

#include <stdbool.h>
#include "var.h"

int init_gui() {
    ctx = nk_glfw3_init(&glfw, window, NK_GLFW3_INSTALL_CALLBACKS);
   
    char font_path[] = "../res/ComicShannsMonoNerd.otf";
    struct nk_font_atlas *atlas;
    nk_glfw3_font_stash_begin(&glfw, &atlas);
    
    struct nk_font *comic = nk_font_atlas_add_from_file(atlas, font_path, 14, 0);
    nk_glfw3_font_stash_end(&glfw);

    bg.r = 0.10f, bg.g = 0.18f, bg.b = 0.24f, bg.a = 1.0f;
    return 1;
}

int draw_gui_setup() {
    nk_glfw3_new_frame(&glfw);

    if (nk_begin(ctx, "mage-baka", nk_rect(50, 50, 250, 250), 
                NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|
                NK_WINDOW_SCALABLE|NK_WINDOW_MINIMIZABLE|
                NK_WINDOW_TITLE))
    {
        enum {NORMAL, INVERTED};
        static int op = NORMAL;
        static int property = 20;
        nk_layout_row_static(ctx, 30, 80, 1);
        if (nk_button_label(ctx, "button"))
            fprintf(stdout, "button pressed\n");

        nk_layout_row_dynamic(ctx, 30, 2);
        
        if (nk_option_label(ctx, "normal", op == NORMAL)) {
            op = NORMAL;
            b_inverse = false;
        }

        if (nk_option_label(ctx, "inverted", op == INVERTED)) {
            op = INVERTED;
            b_inverse = true;
        }

        nk_layout_row_dynamic(ctx, 25, 1);
        nk_property_int(ctx, "Compression:", 0, &property, 100, 10, 1);

        nk_layout_row_dynamic(ctx, 20, 1);
        nk_label(ctx, "background:", NK_TEXT_LEFT);
        nk_layout_row_dynamic(ctx, 25, 1);

        if (nk_combo_begin_color(ctx, nk_rgb_cf(bg), nk_vec2(nk_widget_width(ctx),400))) {
            nk_layout_row_dynamic(ctx, 120, 1);
            bg = nk_color_picker(ctx, bg, NK_RGBA);
            nk_layout_row_dynamic(ctx, 25, 1);
            bg.r = nk_propertyf(ctx, "#R:", 0, bg.r, 1.0f, 0.01f,0.005f);
            bg.g = nk_propertyf(ctx, "#G:", 0, bg.g, 1.0f, 0.01f,0.005f);
            bg.b = nk_propertyf(ctx, "#B:", 0, bg.b, 1.0f, 0.01f,0.005f);
            bg.a = nk_propertyf(ctx, "#A:", 0, bg.a, 1.0f, 0.01f,0.005f);
            nk_combo_end(ctx);
        }
    }
    nk_end(ctx);

    return 1;
}

void sure_draw_gui() {
    nk_glfw3_render(&glfw, NK_ANTI_ALIASING_ON, MAX_VERTEX_BUFFER, MAX_ELEMENT_BUFFER);

    glDisable(GL_SCISSOR_TEST);
    glDisable(GL_BLEND);
    glDisable(GL_CULL_FACE);
}

void gui_shutdown() {
    nk_glfw3_shutdown(&glfw);
}

#endif 
