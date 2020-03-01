/* External API for RTOS features examples files */

//CONFIGURATION SECTION

#define queueExample (1)           //Examples of queues

#if (queueExample == 1)
#define dTestSimpleQueue      (0)    //Simple queue example with cpoing data into queue, data are copied directly to the queue */
#define dTestPointereQueue    (0)    //Queue with queuing only pointers to data, for larne amount of data queuing (ex. buffers)
#define dTestQueueSet         (0)    // example of queue set usage
#endif

#define taskExample  (1)            //Examples of how tasks works, time slicint, preemption etc.
#define timerExample (1)            //Examples of software timers

#if (timerExample == 1)
#define dTestSimpleTimers     (1)    //Simple software timers test
#define dTestSoftwareTimersId (1)    //Test software timers with its id usage
#endif

#define dTestBinarySemaphore  (1)    //Binary semaphores testing
#define dTestCountingSemaphore (1)   //Counting semaphore testing

#define dTestSimpleMutex      (1)    //Simple mutex testing

// FREE RTOS EXAMPLES PUBLIC API SECTION
void exampleInit(void);

#if (taskExample == 1)
void TaskTestingInit(void);
#endif

#if (queueExample == 1)
#if (dTestSimpleQueue == 1)
void simpleQueueExampleInit(void);
#endif
#if (dTestPointereQueue == 1)
void pointerQueueExampleInit(void);
#endif
#if (dTestQueueSet == 1)
void setQueueExampleInit(void);
#endif
#endif

#if (timerExample == 1)
#if (dTestSimpleTimers == 1)
void softwareTimerExampleInit(void);
#endif
#if (dTestSoftwareTimersId == 1)
void softwareTimerExampleWithIdInit(void);
#endif
#endif

#if (dTestBinarySemaphore == 1)
void binarySemaphoreTestInit(void);
void timer10Callback(void);
#endif

#if (dTestCountingSemaphore == 1)
void countingSemaphoreTestInit(void);
void timer10Callback(void);
#endif

#if (dTestSimpleMutex == 1)
void simpleMutexTestInit(void);
#endif