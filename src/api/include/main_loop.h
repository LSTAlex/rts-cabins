#pragma once

#define MAIN_LOOP_DEFAULT_DELAY 0.3

#include <uv.h>

/**
 * Содержит главный цикл событий кабины
 */
class MainLoop {
  /**
   * Задержка между итерациями цикла
   */
  const float delay;

  /**
   * Указатель на экземпляр цикла
   */
  uv_loop_t *loop;

  /**
   * Полное время прошедшее с момента загрузки кабины
   */
  float time;

  /**
   * Время прошедшее с момента последнего запуска цикла
   */
  float step_time;

public:
  MainLoop(const float delay);
  ~MainLoop();

  /**
   * Выполняет итерацию цикла событий с учётом задержки
   * для сокращения влияния на FPS
   */
  void
  run(const float frame_time);

  /**
   * Возвращает указатель на экземпляр цикла
   */
  uv_loop_t*
  get_loop();

  /**
   * Возвращает сырое время прошедшее с момента загрузки кабины
   *
   * Время имеет некоторую погрешность из-за того, что считается не на каждом
   * кадре.
   */
  float
  cabin_time_raw();

  /**
   * Возвращает округлённое время в секундах прошедшее с момента загрузки кабины
   */
  unsigned long
  cabin_time();

  /**
   * Устанавливает ф-цию для периодического выполнения
   *
   * Память возвращаемого таймера выделяется в куче.
   * Эта память должна быть освобождена вручную ЕСЛИ таймер был отменён ручным
   * вызовом api LibUV.
   */
  uv_timer_t*
  setInterval(uv_timer_cb cb, uint64_t interval, void *data = NULL, int *uv_res = NULL);

  /**
   * Отменяет ф-цию выполняемую периодически
   *
   * Память переданного указателя освобождается
   * Не забудь освободить память данных интервала!
   */
  void
  clearInterval(uv_timer_t *timer, int *libuv_res = NULL);

  /**
   * Обновляет интервал времени через который происходит запуск ф-ции
   */
  void
  setIntervalRepeat(uv_timer_t *timer, uint64_t new_repeat);

  /**
   * Устанавливает ф-цию для выполнения с задержкой
   *
   * Память возвращаемого таймера выделяется в куче.
   * Эта память должна быть освобождена вручную ЕСЛИ таймер был отменён ручным
   * вызовом api LibUV.
   */
  uv_timer_t*
  setTimeout(uv_timer_cb cb, uint64_t interval, void *data = NULL, int *uv_res = NULL);

  /**
   * Отменяет ф-цию запланированную к выполнению позднее
   *
   * Память переданного указателя освобождается
   * Не забудь освободить память данных интервала!
   */
  void
  clearTimeout(uv_timer_t *timer, int *libuv_res = NULL);
};
