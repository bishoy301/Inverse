#ifndef WINDOW_H
#define WINDOW_H

#include "../Core/input.h"
#include <SDL2/SDL.h>
#include <string>

class Window {
	public:
		Window(int width, int height, const std::string& title);
		virtual ~Window();

		void update();
		void swap_buffers();
		void bind_as_render_target() const;

		inline bool is_close_requested() const {
			return m_is_close_requested;
		}
		inline int get_width() const {
			return m_width;
		}
		inline int get_height() const {
			return m_height;
		}
		inline float get_aspect_ratio() const {
			return (float)m_width / (float)m_height;
		}
		inline const std::string& get_title() const {
			return m_title;
		}
		// Calculation for center of screen
		inline Vec2f get_center() const {
			return Vec2f((float)m_width/2.0f, (float)m_height/2.0f);
		}
		inline SDL_Window *get_sdl_window() {
			return m_window;
		}
		inline const Input& get_input() const {
			return m_input;
		}

		void set_fullscreen(bool value);
	private:
		int           m_width;
		int  	      m_height;
		bool          m_is_close_requested;
		std::string   m_title;
		SDL_Window   *m_window;
		SDL_GLContext m_glContext;
		Input         m_input;

		Window(const Window& other) : m_input(this) {}
		void operator=(const Window& other) {}
};

#endif
