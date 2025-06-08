#include "IC_font.h"

nk_user_font* NuklearFontFromRaylibFont(Font* font, float fontSize)
{
    struct nk_user_font* userFont = (struct nk_user_font*)MemAlloc(sizeof(struct nk_user_font));
    userFont->userdata = nk_handle_ptr(font);
    userFont->height = fontSize;
    userFont->width = nk_raylib_font_get_text_width_user_font;
    return userFont;
}
