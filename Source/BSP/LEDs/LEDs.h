typedef enum LedId_e
{
    eLed0 = 0,
    eLed1,
    eLed2,
    eLed3,
    eLed4,
    eLed5,

    dLedAmount
}LedId_t;

void LedsInit(void);

void LedOn(LedId_t ledId);
void LedOff(LedId_t ledId);
void LedToggle(LedId_t ledId);