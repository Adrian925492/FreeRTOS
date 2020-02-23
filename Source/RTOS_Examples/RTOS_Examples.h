/* External API for RTOS features examples files */

//CONFIGURATION SECTION

#define queueExample (1)

#if (queueExample == 1)

#define dTestSimpleQueue      (0)    //Simple queue example with cpoing data into queue, data are copied directly to the queue */
#define dTestPointereQueue    (1)    //Queue with queuing only pointers to data, for larne amount of data queuing (ex. buffers)

#endif

#define taskExample  (1)
#define timerExample (1)





// FREE RTOS EXAMPLES PUBLIC API SECTION
void exampleInit(void);

#if (queueExample == 1)

#if (dTestSimpleQueue == 1)
void simpleQueueExampleInit(void);
#endif
#if (dTestPointereQueue == 1)
void pointerQueueExampleInit(void);
#endif
#endif