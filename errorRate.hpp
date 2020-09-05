/*!
 * @file errorRate.hpp
 * @author iTuMaN4iK (swaga.ituman4ik@gmail.com)
 * @brief Описания класса подсчитывающего отношение ошибочных пакетов к переданным
 * @version 0.1
 * @date 2020-09-05
 *
 * @copyright Copyright (c) 2020
 *
 */
#pragma once
#include <cstdint>
#include <map>
#include <iostream>
struct Frames {
  uint64_t frames = 0;
  uint64_t lost_frames = 0;
};
std::istream& operator>>(std::istream& is, Frames& fr);
/*!
 * @brief Возвращает  ErrorRate для интервала времени
 *
 * @param last Предыдущий frame
 * @param next Следующий frame
 * @return float
 */
double getErrorRateIntervals(const Frames& last, const Frames& next);

class ErrorRate {
 public:
  /*!
   * @brief Добавляет информацию о текущих переданных и потерянных пакетах.
   *
   * @param time Время в секундах.
   * @param transferred Кол-во переданных.
   * @param lost Кол-во принятых.
   */
  void setCurrent(uint64_t time, const Frames& frames);
  /*!
   * @brief Возвращает ErrorRate для временого окна
   *
   * @param duration
   * @return float
   */
  double getErrorRate(uint32_t duration = 0) const;

 private:
  std::map<uint64_t, Frames> mErrorRate;  //<! Карта для хранения пары время и error rate
};