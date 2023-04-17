#ifndef ANALOG_CLOCK_SRC_ANALOG_CLOCK_H_
#define ANALOG_CLOCK_SRC_ANALOG_CLOCK_H_

#include <SDL2/SDL.h>
//#include <SDL2/SDL_ttf.h>

#include <chrono>
#include <string>
#include <utility>

/**
 * @brief Класс циферблата
 */
class AnalogClock {
 public:
  /**
   * @brief Дефолтный конструктов с вариативным изменением добавочного времени к
   * локальному
   *
   * @param hour_increment Добавочное время к локальному
   */
  AnalogClock(int hour_increment = 0) noexcept;
  /**
   * @brief Конструктор переноса
   */
  AnalogClock(AnalogClock&) noexcept;
  /**
   * @brief Конструктор копирования
   */
  AnalogClock(AnalogClock&&) noexcept;

  /**
   * @brief Геттер к протектед полю time_zone
   *
   * @return Количество часов добавленное к времени
   */
  int GetTimeZone() const noexcept;
  /**
   * @brief Мутатор к протектед полю time_zone
   *
   * @param hour_increment
   */
  void SetTimeZone(int hour_increment) noexcept;

  /**
   * @brief Метод для отрисовки циферблата в SDL_Renderer поле
   *
   * @param renderer Таргет поле для вывода
   * @param x_position Позиция x в окне
   * @param y_position Позиция y в окне
   * @param radius_clock Радиус циферблата
   */
  void DrawClock(SDL_Renderer* renderer, int x_position, int y_position,
                 int radius_clock) const;

  /**
   * @brief Оператор копирования
   *
   * @return this, левый объект
   */
  AnalogClock& operator=(AnalogClock&) noexcept;
  /**
   * @brief Оператор переноса
   *
   * @return this, левый объект
   */
  AnalogClock& operator=(AnalogClock&&) noexcept;

 protected:
  void NormalizeTimeZone() noexcept;  ///< Корректирование поля time_zone для
                                      ///< корректности
  /**
   * @brief Отрисовка меток на периметре циферблата
   */
  void DrawMarks(SDL_Renderer* renderer, int x_position, int y_position,
                 int radius_clock) const;
  /**
   * @brief Отрисовка стрелок на циферблате
   */
  void DrawPointer(SDL_Renderer* renderer, int x_position, int y_position,
                   int radius_clock) const;
  //    void DrawText(SDL_Renderer* renderer, int x_position, int y_position,
  //    int radius_clock) const;

  int time_zone;  ///< Поле хранящее время добавления к циферблату
};

#endif  // ANALOG_CLOCK_SRC_ANALOG_CLOCK_H_
