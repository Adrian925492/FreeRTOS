/* External API for RTOS features examples files */

//CONFIGURATION SECTION

#define queueExample (1)

#if (queueExample == 1)

#define dTestSimpleQueue      (1)    //Simple queue example with cpoing data into queue, data are copied directly to the queue */

#endif

#define taskExample  (1)
#define timerExample (1)





// FREE RTOS EXAMPLES PUBLIC API SECTION
void exampleInit(void);

#if (queueExample == 1)

#if (dTestSimpleQueue == 1)
void simpleQueueExampleInit(void);
#endif

#endif