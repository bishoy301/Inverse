#include "window.h" 
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <iostream>
//TODO(Bishoy): Figure out if I should do profiling. Library vs Own Implementation

Window::Window(int width, int height, const std::string& title) :
	m_width(width),
	m_height(height),
	m_title(title),
	m_is_close_requested(false)
{
	if(SDL_Init(SDL_VIDEO | SDL_INIT_TIMER) != 0) {
		std::cout << "SDL couldn't be initialized" << std::endl;
	}

	// Set up of required GL Attributes
	SDL_GL_SETATTRIBUTE(SDL_GL_RED_SIZE, 8); 
	SDL_GL_SETATTRIBUTE(SDL_GL_GREEN_SIZE, 8); 
	SDL_GL_SETATTRIBUTE(SDL_GL_BLUE_SIZE, 8); 
	SDL_GL_SETATTRIBUTE(SDL_GL_ALPHA_SIZE, 8); 
	SDL_GL_SETATTRIBUTE(SDL_GL_DEPTH_SIZE, 16); 
	SDL_GL_SETATTRIBUTE(SDL_GL_BUFFER_SIZE, 32); 
	SDL_GL_SETATTRIBUTE(SDL_GL_DOUBLEBUFFER, 1); 

	SDL_GL_SETATTRIBUTE(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SETATTRIBUTE(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SETATTRIBUTE(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE); 

	m_window = SDL_CreateWindow(
			title,
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			width,
			height,
			SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
		); 
	m_glContext = SDL_GL_CreateContext(m_window);
	if (!m_glContext) {
		std::cout << "Couldn't create GL Context" << std::endl; 
	}

	SDL_GL_SetSwapInterval(1);

	GLenum res = glewInit();
	if (res != GLEW_OK) {
		std::cout << "Error: " << glewGetErrorString(res) << std::endl;
	}
}

Window::~Window()
{
	SDL_GL_DeleteContext(m_glContext);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void Window::update()
{
	//TODO(Bishoy): Handle Input in here and update window
	SDL_Event event;
	while(SDL_PollEvent(&e)) {
		if (event.type == SDL_QUIT) {
			m_is_close_requested = true;
		}

		if (event.type == SDL_MOUSEMOTION) {
			//TODO handle mouse input
		}

		if (event.type == SDL_KEYDOWN) {
			//TODO handle key input
		}

		if (event.type == SDL_KEYUP) {
			//TODO handle key up input
		}

		if (event.type == SDL_MOUSEBUTTONUP) {
			//TODO handle mouse click input
		}
	}
}

void Window::swap_buffers()
{
	SDL_GL_SwapWindow(m_window);
}

void Window::bind_as_render_target() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

# if PROFILING_SET_1x1_VIEWPORT == 0
	glViewport(0, 0, GetWidth(), GetHeight());
# else
	glViewport(0, 0, 1, 1);
# endif
}

void Window::set_fullscreen(bool value)
{
	int mode = 0;
	if (value) {
		mode = SDL_WINDOW_FULLSCREEN;
	} else {
		mode = 0;
	}

	SDL_SetWindowFullscreen(m_window, mode);
}