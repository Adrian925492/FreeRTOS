#include "RTOS_Examples.h"

void exampleInit(void)
{
#if (queueExample == 1)

#if (dTestSimpleQueue == 1)
simpleQueueExampleInit();
#endif

#endif


}