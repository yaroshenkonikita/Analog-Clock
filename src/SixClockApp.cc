#include "SixClockApp.h"

SixClockApp::SixClockApp() { SDL_Init(SDL_INIT_VIDEO); }

SixClockApp::~SixClockApp() {
  if (window) {
    SDL_DestroyWindow(window);
  }
  SDL_Quit();
}

void SixClockApp::show() {
  if (!window) {
    window =
        SDL_CreateWindow("Analog Clock", SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED, 700, 500, SDL_WINDOW_SHOWN);
  }
}

int SixClockApp::exec() {
  show();
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
  SDL_Event event;

  AnalogClock ClockA{0}, ClockB{-1}, ClockC{0}, ClockD{-2}, ClockE{1},
      ClockF{2};
  ClockA = std::move(ClockD);  // просто демонстрация

  bool running = true;
  while (running) {
    while (SDL_PollEvent(&event) != 0) {
      if (event.type == SDL_QUIT) running = false;
    }

    // очистка экрана
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // отрисовка часов
    ClockA.DrawClock(renderer, 100, 100, 90);  // [0][0] local - 2
    ClockB.DrawClock(renderer, 100, 350, 90);  // [0][1] local - 1
    ClockC.DrawClock(renderer, 350, 100, 90);  // [1][0] local
    ClockD.DrawClock(renderer, 350, 350, 90);  // [1][1] local
    ClockE.DrawClock(renderer, 600, 100, 90);  // [2][0] local + 1
    ClockF.DrawClock(renderer, 600, 350, 90);  // [2][1] local + 2

    // отображение экрана
    SDL_RenderPresent(renderer);

    // задержка для синхронизации с частотой обновления экрана
    SDL_Delay(1000 / 60);
  }
  SDL_DestroyRenderer(renderer);
  return 0;
}
