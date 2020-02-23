#include "RTOS_Examples.h"

void exampleInit(void)
{
#if (queueExample == 1)

#if (dTestSimpleQueue == 1)
simpleQueueExampleInit();
#endif
#if (dTestPointereQueue == 1)
pointerQueueExampleInit();
#endif
#endif


}