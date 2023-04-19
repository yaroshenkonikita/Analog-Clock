#include "SixClockApp.h"

SixClockApp::SixClockApp() { SDL_Init(SDL_INIT_VIDEO); }

SixClockApp::~SixClockApp() {
  if (window) {
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
  }
  SDL_Quit();
}

void SixClockApp::show() {
  if (!window) {
    window = SDL_CreateWindow("Analog Clock", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, x_size_window,
                              y_size_window, SDL_WINDOW_OPENGL);

    // Инициализация OpenGL
    context = SDL_GL_CreateContext(window);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, x_size_window, y_size_window, 0, 1, -1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
  }
}

int SixClockApp::exec() {
  show();
  AnalogClock ClockA{0}, ClockB{-1}, ClockC{0}, ClockD{-2}, ClockE{1},
      ClockF{2};
  ClockA = std::move(ClockD);  // просто демонстрация

  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

  SDL_Event event;
  bool running = true;
  while (running) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) running = false;
    }

    // очистка экрана
    glClear(GL_COLOR_BUFFER_BIT);

    // отрисовка часов
    glBegin(GL_LINES);
    ClockA.DrawClock(100, 100, 90);  // [0][0] local - 2
    ClockB.DrawClock(100, 350, 90);  // [0][1] local - 1
    ClockC.DrawClock(350, 100, 90);  // [1][0] local
    ClockD.DrawClock(350, 350, 90);  // [1][1] local
    ClockE.DrawClock(600, 100, 90);  // [2][0] local + 1
    ClockF.DrawClock(600, 350, 90);  // [2][1] local + 2
    glEnd();

    // отображение экрана
    SDL_GL_SwapWindow(window);

    // задержка для синхронизации с частотой обновления экрана
    SDL_Delay(16);  // 60 кадров в секунду
  }
  return 0;
}
