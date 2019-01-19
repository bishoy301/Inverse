/* 
 * This file handles user input and keymapping.
 */

#ifndef INPUT_H
#define INPUT_H

#define NUM_MOUSE_BUTTONS 256

#include "math3D.h"
#include <SDL2/SDL.h>
#include <string>


class Window;

class Input {
    public:
        const static int num_mouse_buttons = NUM_MOUSE_BUTTONS;

        Input();
        
        Input(Window *window);

        //Key Functions

        //Checks if passed scan code is within bounds of the enum and return true if it is or false if it's not. 
        inline bool get_key(int scan_code) const
        {
            return m_key_inputs[scan_code];
        }

        //Sets the corresponding index within the array to true if the key was pressed.
        inline void set_key(int scan_code, bool code_found)
        {
            m_key_inputs[scan_code] = code_found;
        }

        //Called for held down key state.
        inline bool get_key_down(int scan_code) const
        {
            return m_down_keys[scan_code];
        }

        //Sets the corresponding index within the array for held down keys to true if the key was pressed.
        inline void set_key_down(int scan_code, bool code_found)
        {
            m_down_keys[scan_code] = code_found;
        }

        //Checks if passed scan code is within bounds.
        inline bool get_key_up(int scan_code) const
        {
            return m_up_keys[scan_code];
        }

        // Sets both arrays for the corresponding scan code to false. 
        inline void set_key_up(int scan_code, bool code_found)
        {
            m_key_inputs[scan_code] = code_found;
            m_down_keys[scan_code] = code_found;
        }

        //Mouse Functions

        // Sets corresponding array index to true if button is pressed/held/released.
        inline void set_mouse(int button, bool listener)
        {
            m_mouse_inputs[button] = listener;
        }

        inline void set_mouse_down(int button, bool listener)
        {
            m_down_mouse[button] = listener;
        }

        inline void set_mouse_up(int button, bool listener)
        {
            m_up_mouse[button] = listener;
        }
        
        
        inline void set_mouseX(int val) { m_mouseX = val; }

        inline void set_mouseY(int val) { m_mouseY = val; }

        inline int get_mouseX() const { return m_mouseX; }

        inline int get_mouseY() const { return m_mouseY; }

        inline Vec2f get_mouse_pos() const {return Vec2f((float) m_mouseX, (float) m_mouseY); }

        void set_cursor(bool visible) const;

        void set_mouse_position(const Vec2f& pos) const;

    private:

        Window *m_window;

        //Boolean arrays for key inputs to track pressed/held/released key inputs.
        bool m_key_inputs[SDL_NUM_SCANCODES] = {0};
        bool m_down_keys[SDL_NUM_SCANCODES] = {0};
        bool m_up_keys[SDL_NUM_SCANCODES] = {0};

        //Boolean arrays for mouse input to track pressed/held/released mouse buttons. 

        bool m_mouse_inputs[NUM_MOUSE_BUTTONS];
        bool m_down_mouse[NUM_MOUSE_BUTTONS];
        bool m_up_mouse[NUM_MOUSE_BUTTONS];

        int m_mouseX;
        int m_mouseY;
       
};

#endif
