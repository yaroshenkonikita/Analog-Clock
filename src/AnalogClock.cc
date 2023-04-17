#include "AnalogClock.h"

AnalogClock::AnalogClock(int hour_increment) noexcept
    : time_zone(hour_increment) {
  NormalizeTimeZone();
}

AnalogClock::AnalogClock(AnalogClock& other) noexcept { *this = other; }

AnalogClock::AnalogClock(AnalogClock&& other) noexcept {
  *this = std::move(other);
}

int AnalogClock::GetTimeZone() const noexcept { return time_zone; }

void AnalogClock::SetTimeZone(int hour_increment) noexcept {
  time_zone = hour_increment;
  NormalizeTimeZone();
}

void AnalogClock::NormalizeTimeZone() noexcept {
  while (time_zone < 0) {
    time_zone += 24;
  }
  time_zone %= 12;
}

AnalogClock& AnalogClock::operator=(AnalogClock& other) noexcept {
  time_zone = other.time_zone;
  return *this;
}

AnalogClock& AnalogClock::operator=(AnalogClock&& other) noexcept {
  time_zone = std::exchange(other.time_zone, 0);
  return *this;
}

void AnalogClock::DrawClock(SDL_Renderer* renderer, int x_position,
                            int y_position, int radius_clock) const {
  DrawMarks(renderer, x_position, y_position, radius_clock);
  DrawPointer(renderer, x_position, y_position, radius_clock);
  //    DrawText(renderer, x_position, y_position, radius_clock);
}

void AnalogClock::DrawMarks(SDL_Renderer* renderer, int x_position,
                            int y_position, int radius_clock) const {
  int x1{}, y1{}, x2{}, y2{};
  double angle{};

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // цвет для меток

  for (int degree = 0; degree < 360; degree += 6) {  // отрисовка меток минут
    angle = degree * M_PI / 180.0;
    x1 = x_position + (radius_clock)*cos(angle);
    y1 = y_position + (radius_clock)*sin(angle);
    x2 = x_position + (radius_clock - 6) * cos(angle);
    y2 = y_position + (radius_clock - 6) * sin(angle);
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
  }

  for (int degree = 0; degree < 360; degree += 30) {  // отрисовка меток часов
    angle = degree * M_PI / 180.0;
    x1 = x_position + (radius_clock - 6) * cos(angle);
    y1 = y_position + (radius_clock - 6) * sin(angle);
    x2 = x_position + (radius_clock - 15) * cos(angle);
    y2 = y_position + (radius_clock - 15) * sin(angle);
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
  }
}

void AnalogClock::DrawPointer(SDL_Renderer* renderer, int x_position,
                              int y_position, int radius_clock) const {
  std::time_t time_now =
      std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
  auto local_time = *std::localtime(&time_now);

  int x1{}, y1{}, x2{}, y2{};
  double angle{};

  SDL_SetRenderDrawColor(renderer, 80, 40, 30,
                         255);  // цвет часовой стрелки и часовая стрелка

  angle = ((local_time.tm_hour + time_zone) % 12 + local_time.tm_min / 60.f);
  angle = (angle > 12 ? angle - 12 : angle) * M_PI / 6.f - M_PI_2;
  x1 = x_position;
  y1 = y_position;
  x2 = x_position + (radius_clock - 50) * cos(angle);
  y2 = y_position + (radius_clock - 50) * sin(angle);
  SDL_RenderDrawLine(renderer, x1, y1, x2, y2);

  SDL_SetRenderDrawColor(renderer, 70, 70, 70,
                         255);  // цвет минутной стрелки и минутная стрелка

  angle = (local_time.tm_min + local_time.tm_sec / 60.f) * M_PI / 30.f - M_PI_2;
  x2 = x_position + (radius_clock - 30) * cos(angle);
  y2 = y_position + (radius_clock - 30) * sin(angle);
  SDL_RenderDrawLine(renderer, x1, y1, x2, y2);

  SDL_SetRenderDrawColor(renderer, 255, 0, 0,
                         255);  // цвет секундной стрелки и секундная стрелка

  angle = local_time.tm_sec * M_PI / 30.f - M_PI_2;
  x2 = x_position + (radius_clock - 20) * cos(angle);
  y2 = y_position + (radius_clock - 20) * sin(angle);
  SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

// void AnalogClock::DrawText(SDL_Renderer* renderer, int x_position, int
// y_position, int radius_clock) const {
//     TTF_Font* font = TTF_OpenFont("fonts/font.ttf", 20); // загрузка шрифта
//
//     SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // цвет надписи и
//     надпись
//
//     std::string text_time_zone = "Local +" + std::to_string(time_zone);
//
//     SDL_Color color = {255, 255, 255, 255};
//
//     SDL_Surface* surface = TTF_RenderText_Solid(font, text_time_zone.c_str(),
//     color); SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer,
//     surface);
//
//     // при запуске через g++, а не cmake, сегался на этой строке(объект
//     SDL_Surface не создавался)
//     // скорее всего шрифт не находился
//     SDL_Rect text_rect = {x_position - (surface->w / 2), y_position +
//     radius_clock + 50, surface->w, surface->h}; SDL_RenderCopy(renderer,
//     texture, nullptr, &text_rect);
//
//     SDL_FreeSurface(surface);
//     SDL_DestroyTexture(texture);
//     TTF_CloseFont(font);
// }
