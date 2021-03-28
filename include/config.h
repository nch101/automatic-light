#ifndef CONFIG_H
#define CONFIG_H

#define         LIGHT_PIN               4
#define         FAN_PIN                 5
#define         SENSOR_IN_PIN           6
#define         SENSOR_OUT_PIN          7

#define         TIME_DELAY              2000
#define         BAUDRATE_DEFAULT        115200

#define         TAP_TO_CONFIG_TIME      5

typedef enum {
  ERROR,
  OK
} exec_state_t;

typedef enum {
  LIGHT_ON,
  LIGHT_OFF
} light_state_t;

typedef enum {
  NOT_DETECTED,
  DETECTED
} motion_sensor_state_t;

typedef enum {
  IN,
  MAYBE_IN,
  OUT,
  MAYBE_OUT
} direction_t;

typedef struct {
  motion_sensor_state_t sensor_in;
  motion_sensor_state_t sensor_out;
} motion_sensors_t;

#endif // CONFIG_H