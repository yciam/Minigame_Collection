//
// Created by Raphael Straub on 15.09.18.
//

#include <menue/header/menue.hpp>

#include "Minigames/Testgame/test.hpp"

menue::menue() {
    //SDL init stuff
    if(SDL_Init(SDL_INIT_VIDEO) != 0){std::cout << "error: " << SDL_GetError() << std::endl; return;}
    this->win = SDL_CreateWindow("Titel",100,200,600,800,SDL_WINDOW_SHOWN);
    if(win == nullptr){std::cout << "winerror: " << SDL_GetError() << std::endl; SDL_Quit(); return;}
    this->renner = SDL_CreateRenderer(this->win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(renner == nullptr){SDL_DestroyWindow(this->win); std::cout << "renderererror: " << SDL_GetError() << std::endl; SDL_Quit(); return;}
    SDL_SetWindowResizable(this->win, SDL_TRUE);
    SDL_SetWindowFullscreen(this->win, SDL_GetWindowFlags(this->win) & SDL_WINDOW_FULLSCREEN_DESKTOP ? 0
                                                                                                     : SDL_WINDOW_FULLSCREEN_DESKTOP);
    SDL_SetWindowFullscreen(this->win, SDL_GetWindowFlags(this->win) & SDL_WINDOW_FULLSCREEN_DESKTOP ? 0
                                                                                                     : SDL_WINDOW_FULLSCREEN_DESKTOP);
    this->gameVector.emplace_back(0, "Testgame", "This is a Testgame", "testgame");
    this->gameVector.emplace_back(0, "Testgame2", "This is another Testgame", "testgame");
}

menue::~menue() {
    SDL_DestroyRenderer(this->renner);
    SDL_DestroyWindow(this->win);
    SDL_Quit();
}

void menue::display() {
    while(this->running){
        SDL_SetRenderDrawColor(this->renner, 0, 0, 0, 0);
        SDL_RenderClear(this->renner);

        this->handleEvents();
        this->displayGamePreview();

        SDL_RenderPresent(this->renner);\
        SDL_Delay(1);
    }
}

void menue::handleEvents() {
    while (SDL_PollEvent(&this->event)) {
        switch(this->event.type){
            case SDL_QUIT: this->running = false; break;
            case SDL_KEYDOWN: this->keys[this->event.key.keysym.sym] = 1; break;
            case SDL_KEYUP: this->keys[this->event.key.keysym.sym] = 0; break;
            case SDL_MOUSEWHEEL:
                if (event.wheel.y < 0) {
                    if (this->selection < this->gameVector.size() - 1)this->selection++;
                } else if (event.wheel.y > 0) {
                    if (this->selection > 0)this->selection--;
                }
                break;
            default: break;
        }
    }
    if(this->keys[SDLK_p]){
        this->executeGame();
    }
}

void menue::executeGame() {
    switch (this->selection) {
        case 0:
            this->spiel = new test(this->win, this->renner, &this->running);
    }
    this->spiel->run();
    delete this->spiel;
}

void menue::displayGamePreview() {

}