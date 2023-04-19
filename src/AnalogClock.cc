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

void AnalogClock::DrawClock(int x_position, int y_position,
                            int radius_clock) const {
  DrawMarks(x_position, y_position, radius_clock);
  DrawPointer(x_position, y_position, radius_clock);
}

void AnalogClock::DrawMarks(int x_position, int y_position,
                            int radius_clock) const {
  int x1{}, y1{}, x2{}, y2{};
  double angle{};

  glColor3f(0.0f, 0.0f, 0.0f);

  for (int degree = 0; degree < 360; degree += 6) {  // отрисовка меток минут
    angle = degree * M_PI / 180.0;
    x1 = x_position + (radius_clock)*cos(angle);
    y1 = y_position + (radius_clock)*sin(angle);
    x2 = x_position + (radius_clock - 6) * cos(angle);
    y2 = y_position + (radius_clock - 6) * sin(angle);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
  }

  for (int degree = 0; degree < 360; degree += 30) {  // отрисовка меток часов
    angle = degree * M_PI / 180.0;
    x1 = x_position + (radius_clock - 6) * cos(angle);
    y1 = y_position + (radius_clock - 6) * sin(angle);
    x2 = x_position + (radius_clock - 15) * cos(angle);
    y2 = y_position + (radius_clock - 15) * sin(angle);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
  }
}

void AnalogClock::DrawPointer(int x_position, int y_position,
                              int radius_clock) const {
  std::time_t time_now =
      std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
  auto local_time = *std::localtime(&time_now);

  int x1{}, y1{}, x2{}, y2{};
  double angle{};

  glColor3f(0.31372549f, 0.15686274f, 0.11764705f);

  angle = ((local_time.tm_hour + time_zone) % 12 + local_time.tm_min / 60.f);
  angle = (angle > 12 ? angle - 12 : angle) * M_PI / 6.f - M_PI_2;
  x1 = x_position;
  y1 = y_position;
  x2 = x_position + (radius_clock - 50) * cos(angle);
  y2 = y_position + (radius_clock - 50) * sin(angle);
  glVertex2f(x1, y1);
  glVertex2f(x2, y2);

  glColor3f(0.27450980f, 0.27450980f, 0.27450980f);

  angle = (local_time.tm_min + local_time.tm_sec / 60.f) * M_PI / 30.f - M_PI_2;
  x2 = x_position + (radius_clock - 30) * cos(angle);
  y2 = y_position + (radius_clock - 30) * sin(angle);
  glVertex2f(x1, y1);
  glVertex2f(x2, y2);

  glColor3f(255.f, 0.f, 0.f);

  angle = local_time.tm_sec * M_PI / 30.f - M_PI_2;
  x2 = x_position + (radius_clock - 20) * cos(angle);
  y2 = y_position + (radius_clock - 20) * sin(angle);
  glVertex2f(x1, y1);
  glVertex2f(x2, y2);
}
