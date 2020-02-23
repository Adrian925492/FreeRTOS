/* External API for RTOS features examples files */

//CONFIGURATION SECTION

#define queueExample (1)

#if (queueExample == 1)
#define dTestSimpleQueue      (0)    //Simple queue example with cpoing data into queue, data are copied directly to the queue */
#define dTestPointereQueue    (0)    //Queue with queuing only pointers to data, for larne amount of data queuing (ex. buffers)
#define dTestQueueSet         (1)    // example of queue set usage
#endif

#define taskExample  (1)            //Examples of how tasks works, time slicint, preemption etc.
#define timerExample (1)





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