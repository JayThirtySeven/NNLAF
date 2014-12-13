#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include <SDL.h>
#undef main

#include <SDL_image.h>
#include <SDL_mixer.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include "core.h"
#include "game.h"

#ifdef WINDOWS
	#pragma comment(lib, "lua51")
	#pragma comment(lib, "SDL2")
	#pragma comment(lib, "SDL2_gfx")
	#pragma comment(lib, "SDL2_mixer")
	#pragma comment(lib, "SDL2_image")
#endif

#ifdef WINDOWS
	#include <direct.h>
	#define GetCurrentDir _getcwd
#else
	#include <unistd.h>
	#define GetCurrentDir getcwd
#endif

int main_event_watch(void *data, SDL_Event *e){
	game_t *game = (game_t *)data;
	
	if(e->type == SDL_KEYDOWN && e->key.keysym.scancode == SDL_SCANCODE_F11){
		core_toggle_fullscreen(game->core);
	}else if((e->type == SDL_QUIT) || (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_ESCAPE)){
		game->core->running = false;
	}else if(e->type == SDL_KEYDOWN && e->key.keysym.scancode == SDL_SCANCODE_F1){
	}else if(e->type == SDL_KEYDOWN && e->key.keysym.scancode == SDL_SCANCODE_F2){
	}else if(e->type == SDL_KEYDOWN && e->key.keysym.scancode == SDL_SCANCODE_F3){
	}else if(e->type == SDL_KEYDOWN && e->key.keysym.scancode == SDL_SCANCODE_F4){
	}else if(e->type == SDL_KEYDOWN && e->key.keysym.scancode == SDL_SCANCODE_F5){
	}else if(e->type == SDL_WINDOWEVENT && e->window.event == SDL_WINDOWEVENT_RESIZED){
		core_window_resize(game->core, e->window.data1, e->window.data2);
	}

	return 0;
}

char CURRENT_PATH[FILENAME_MAX];

int main(void){
	if (!GetCurrentDir(CURRENT_PATH, sizeof(CURRENT_PATH))){ return 1; }

	#ifdef DEBUG
	printf("The current working directory is %s\n", CURRENT_PATH);
	#endif

	SDL_Init(SDL_INIT_EVERYTHING);
	
	core_t *core = core_create();
	game_t *game = game_create(core);

	SDL_AddEventWatch(&main_event_watch, game);
	
	double ms_per_frame = 16.6; // 16.6ms per frame = 60 frames per second
	double curr_ms = SDL_GetTicks();
	double prev_ms = curr_ms;
	double ms_delta = 0;
	double ms_accum = 0;
	
	while(core->running){
		prev_ms = curr_ms;
		curr_ms = SDL_GetTicks();
		ms_delta = curr_ms - prev_ms;
		ms_accum += ms_delta;
		
		if(ms_accum > ms_per_frame){
			ms_accum -= ms_per_frame;

			controller_poll_events(game->controller);
			
			if(ms_accum > ms_per_frame){
				game_fast_frame(game);
			}else{
				game_full_frame(game);

				core_window_redraw(core);
			}
		}
	}

	game_delete(game);
	core_delete(core);

	SDL_Quit();
	
	return 0;
}


