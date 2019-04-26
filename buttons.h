typedef struct {
    uint_fast8_t port;
    uint_fast16_t pin;
} ButtonPin;
int time;
int timeseconds;
int changetime;
bool RESET;
bool COUNTDOWN;
bool SETTIME;
void handleStart(void);
void handleUp(void);
void handleButtonPress(void);
void reset(void);
void button_setup(void);
