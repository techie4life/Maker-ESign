typedef struct {
    uint_fast8_t port;
    uint_fast16_t pin;
} ButtonPin;

void handleStart(void);
void handleUP(void);
void handleButtonPress(void);
void Reset(void);
