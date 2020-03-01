#include "RTOS_Examples.h"

void exampleInit(void)
{
#if (taskExample == 1)
TaskTestingInit();
#endif

#if (queueExample == 1)
#if (dTestSimpleQueue == 1)
simpleQueueExampleInit();
#endif
#if (dTestPointereQueue == 1)
pointerQueueExampleInit();
#endif
#if (dTestQueueSet == 1)
setQueueExampleInit();
#endif
#endif

#if (timerExample == 1)
#if (dTestSimpleTimers == 1)
softwareTimerExampleInit();
#endif
#if (dTestSoftwareTimersId == 1)
softwareTimerExampleWithIdInit();
#endif
#endif

#if (dTestBinarySemaphore == 1)
binarySemaphoreTestInit();
#endif

#if (dTestCountingSemaphore == 1)
countingSemaphoreTestInit();
#endif

#if (dTestSimpleMutex == 1)
simpleMutexTestInit();
#endif

}