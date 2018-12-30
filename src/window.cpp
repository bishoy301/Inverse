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

