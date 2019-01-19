#include "input.h"
#include "window.h"

Input::Input(Window *window) : m_window(window)
{
    m_mouseX = 0;
    m_mouseY = 0;
}

void Input::set_cursor(bool visible)
{
    if (visible)
        SDL_ShowCursor(1);
    else
        SDL_ShowCursor(0);
}

void Input::set_mouse_position(Vec2f& pos)
{
    SDL_WarpMouseInWindow(m_window->get_sdl_window(), (int)pos.get_x(), (int)pos.get_y());
}

