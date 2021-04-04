#ifndef CONFIG_H
#define CONFIG_H

#define         pinToISR(x)             digitalPinToInterrupt(x)

// #define         DEBUG

#define         LIGHT_PIN               13
#define         FAN_PIN                 5
#define         FAN_CONTROL_PIN         2
#define         SENSOR_IN_PIN           3
#define         SENSOR_OUT_PIN          4

#define         WAKEUP_DELAY            500
#define         TIME_DELAY              2000
#define         BAUDRATE_DEFAULT        115200

#define         TAP_TO_CONFIG_TIME      5

typedef enum {
  ERROR,
  OK
} exec_state_t;

typedef enum {
  OFF,
  ON
} state_t;

typedef enum {
  NOT_DETECTED,
  DETECTED
} motion_sensor_state_t;

typedef enum {
  NONE,
  MAYBE_IN,
  MAYBE_OUT,
  IN,
  OUT
} direction_t;

typedef enum {
  SLEEPING,
  STANDBY,
  WORKING
} system_state_t;

typedef struct {
  motion_sensor_state_t sensor_in;
  motion_sensor_state_t sensor_out;
} motion_sensors_t;

#endif // CONFIG_H