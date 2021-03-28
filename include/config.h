#ifndef CONFIG_H
#define CONFIG_H

#define         LIGHT_PIN               4
#define         FAN_PIN                 5

#define         TIME_DELAY              2000
#define         BAUDRATE_DEFAULT        115200

#define         TAP_TO_CONFIG_TIME      5

typedef enum {
  ERROR,
  OK
} exec_state_t;

typedef enum {
  SLEEP_MODE,
  WORKING_MODE,
  UPDATE_MODE
} system_state_t;

typedef enum {
  LIGHT_ON,
  LIGHT_OFF
} light_state_t;

typedef enum {
  NONE,
  MAYBE_HAS,
  HAS,
  MAYBE_NOT
} person_detect_state_t;

typedef enum {
  IN,
  MAYBE_IN,
  OUT,
  MAYBE_OUT,
  UNKNOWN
} motion_direct_t;

#endif // CONFIG_H