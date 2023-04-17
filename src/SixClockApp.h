#ifndef ANALOG_CLOCK_SRC_SIX_CLOCK_APP_H_
#define ANALOG_CLOCK_SRC_SIX_CLOCK_APP_H_

#include "AnalogClock.h"

/**
 * @brief Приложение для отрисовки шести циферблатов
 */
class SixClockApp {
 public:
  SixClockApp();   ///< Дефолтный конструкор
  ~SixClockApp();  ///< Дефолтный деструктор
  void show();     ///< Метод для иницилизации окна
  int exec();  ///< Функция для запуска приложения
 protected:
  SDL_Window* window{};  ///< Поле окна приложения
};

#endif  // ANALOG_CLOCK_SRC_SIX_CLOCK_APP_H_
