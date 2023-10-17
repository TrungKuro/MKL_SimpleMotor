/* ------------------------------------------------------------------------- */
/*                                  LIBRARY                                  */
/* ------------------------------------------------------------------------- */

#include "MKL_SimpleMotor.h"

/* ------------------------------------------------------------------------- */
/*                                  HÀM TẠO                                  */
/* ------------------------------------------------------------------------- */

MKL_SimpleMotor::MKL_SimpleMotor(
    int pinIn1, int pinIn2,
    int pinIn3, int pinIn4)
{
  _pinIn1 = pinIn1;
  _pinIn2 = pinIn2; // ~PWM
  _pinIn3 = pinIn3; // ~PWM
  _pinIn4 = pinIn4;

  pinMode(_pinIn1, OUTPUT);
  pinMode(_pinIn2, OUTPUT);
  pinMode(_pinIn3, OUTPUT);
  pinMode(_pinIn4, OUTPUT);
}

/* ------------------------------------------------------------------------- */
/*                            HÀM ĐIỀU KHIỂN MOTOR                           */
/* ------------------------------------------------------------------------- */

/**
 * Điều khiển motor kênh A quay thuận
 *
 * - speed : tốc độ động cơ, đơn vị (%)
 *           phạm vi giá trị từ 0% đến 100%
 */
void MKL_SimpleMotor::motorA_fw(int speed)
{
  // Xử lý giá trị tốc độ nhận được
  speed = calculate_speed(speed);

  // Điều khiển Motor bên TRÁI quay tới
  analogWrite(_pinIn2, speed); // ~PWM
  digitalWrite(_pinIn1, LOW);
}

/**
 * Điều khiển motor kênh B quay thuận
 *
 * - speed : tốc độ động cơ, đơn vị (%)
 *           phạm vi giá trị từ 0% đến 100%
 */
void MKL_SimpleMotor::motorB_fw(int speed)
{
  // Xử lý giá trị tốc độ nhận được
  speed = calculate_speed(speed);

  // Điều khiển Motor bên PHẢI quay tới
  analogWrite(_pinIn3, speed); // ~PWM
  digitalWrite(_pinIn4, LOW);
}

/* ------------------------------------------------------------------------- */

/**
 * Điều khiển motor kênh A quay ngược
 *
 * - speed : tốc độ động cơ, đơn vị (%)
 *           phạm vi giá trị từ 0% đến 100%
 */
void MKL_SimpleMotor::motorA_bw(int speed)
{
  // Xử lý giá trị tốc độ nhận được
  speed = calculate_speed(speed);

  // Điều khiển Motor bên TRÁI quay lùi
  analogWrite(_pinIn2, 255 - PWM); // ~PWM
  digitalWrite(_pinIn1, HIGH);
}

/**
 * Điều khiển motor kênh B quay ngược
 *
 * - speed : tốc độ động cơ, đơn vị (%)
 *           phạm vi giá trị từ 0% đến 100%
 */
void MKL_SimpleMotor::motorB_bw(int speed)
{
  // Xử lý giá trị tốc độ nhận được
  speed = calculate_speed(speed);

  // Điều khiển Motor bên PHẢI quay lùi
  analogWrite(_pinIn3, 255 - PWM); // ~PWM
  digitalWrite(_pinIn4, HIGH);
}

/* ------------------------------------------------------------------------- */

/**
 * Điều khiển motor kênh A dừng lại
 */
void MKL_SimpleMotor::motorA_stop()
{
  // Điều khiển Motor bên TRÁI dừng lại
  digitalWrite(_pinIn2, LOW); // none ~PWM
  digitalWrite(_pinIn1, LOW);
}

/**
 * Điều khiển motor kênh B dừng lại
 */
void MKL_SimpleMotor::motorB_stop()
{
  // Điều khiển Motor bên PHẢI dừng lại
  digitalWrite(_pinIn3, LOW); // none ~PWM
  digitalWrite(_pinIn4, LOW);
}

/* ------------------------------------------------------------------------- */
/*                             HÀM ĐIỀU KHIỂN XE                             */
/* ------------------------------------------------------------------------- */

/**
 * Điều khiển xe đi tới
 *
 * - speedA : tốc độ động cơ kênh A, bên TRÁI của xe
 *            phạm vi giá trị từ 0% đến 100%
 *
 * - speedB : tốc độ động cơ kênh B, bên PHẢI của xe
 *            phạm vi giá trị từ 0% đến 100%
 */
void MKL_SimpleMotor::car_fw(int speedA, int speedB)
{
  // Xử lý giá trị tốc độ nhận được
  speedA = calculate_speed(speedA);
  speedB = calculate_speed(speedB);

  motorA_fw(speedA); // Điều khiển motor kênh A quay thuận
  motorB_fw(speedB); // Điều khiển motor kênh B quay thuận
}

/**
 * Điều khiển xe đi lùi
 *
 * - speedA : tốc độ động cơ kênh A, bên TRÁI của xe
 *            phạm vi giá trị từ 0% đến 100%
 *
 * - speedB : tốc độ động cơ kênh B, bên PHẢI của xe
 *            phạm vi giá trị từ 0% đến 100%
 */
void MKL_SimpleMotor::car_bw(int speedA, int speedB)
{
  // Xử lý giá trị tốc độ nhận được
  speedA = calculate_speed(speedA);
  speedB = calculate_speed(speedB);

  motorA_bw(speedA); // Điều khiển motor kênh A quay ngược
  motorB_bw(speedB); // Điều khiển motor kênh B quay ngược
}

/* ------------------------------------------------------------------------- */

/**
 * Điều khiển xe xoay trái
 *
 * - speed : tốc độ động cơ, đơn vị (%)
 *           phạm vi giá trị từ 0% đến 100%
 */
void MKL_SimpleMotor::car_rotateL(int speed)
{
  // Xử lý giá trị tốc độ nhận được
  speed = calculate_speed(speed);

  motorA_bw(speed); // Điều khiển motor kênh A quay ngược
  motorB_fw(speed); // Điều khiển motor kênh B quay thuận
}

/**
 * Điều khiển xe xoay phải
 *
 * - speed : tốc độ động cơ, đơn vị (%)
 *           phạm vi giá trị từ 0% đến 100%
 */
void MKL_SimpleMotor::car_rotateR(int speed)
{
  // Xử lý giá trị tốc độ nhận được
  speed = calculate_speed(speed);

  motorA_fw(speed); // Điều khiển motor kênh A quay thuận
  motorB_bw(speed); // Điều khiển motor kênh B quay ngược
}

/* ------------------------------------------------------------------------- */

/**
 * Điều khiển xe dừng lại
 */
void MKL_SimpleMotor::car_stop()
{
  motorA_stop(); // Điều khiển motor kênh A dừng lại
  motorB_stop(); // Điều khiển motor kênh B dừng lại
}

/* ------------------------------------------------------------------------- */
/*                               HÀM ĐẶT TỐC ĐỘ                              */
/* ------------------------------------------------------------------------- */

/**
 * Đảm bảo giá trị tốc độ (%) nhận được trong khoảng 0% đến 100%
 * Đồng thời chuyển đổi tốc độ (%) sang thang (PWM) tương ứng
 */
int MKL_SimpleMotor::calculate_speed(int speed)
{
  // Đảm bảo giá trị tốc độ (%) nằm trong khoảng cho phép
  constrain(speed, 0, 100);

  // Chuyển đổi giá trị tốc độ (%) sang (PWM)
  speed = map(speed, 0, 100, 0, 255);

  return speed;
}

/* ------------------------------------------------------------------------- */