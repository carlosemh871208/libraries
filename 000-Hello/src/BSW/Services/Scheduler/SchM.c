/*******************************************************************************
 * Description:
 *
*******************************************************************************/
/******************************************************************************/
/***********************************Includes***********************************/
#include "SchM.h"
/******************************************************************************/
/***************************New types definitions******************************/

/******************************************************************************/
/*****************************Macros definitions*******************************/
#define NUM_OF_TASKS ((uint8_t) 6U)
/******************************************************************************/
/***************************Constants definitions******************************/
const SchM_ConfigType *SchM_ConfigGlobal; /*Check number of task & their configuration*/
/******************************************************************************/
/*****************************Exported Variables*******************************/
SchM_ControlType          SchM_Control = {0U, SCHM_UNINIT}; /*Checks tick counter & scheduler start state*/
SchM_TaskControlBlockType SchM_TaskControlBlock [NUM_OF_TASKS]; /*Check task state & call task callback*/
/******************************************************************************/
/*************************Private Function Prototypes**************************/
static void SchM_OsTick     (void);
static void SchM_Background (void);

tCallbackFunction GlbSysTickCallback; /*Generic void callback: Handles the OsTick Function and every tick process the scheduler*/
static void SysTick_Init (tCallbackFunction Callback);
/******************************************************************************/
/************************Exported Function Prototypes**************************/
/*******************************************************************************
 *  Name                 : SchM_Init
 *  Description          : Initializes the scheduler
 *  Parameters           : [const SchM_ConfigType *SchM_Config]
 *  Return               : void
 *  Critical/explanation : No
 ******************************************************************************/
void SchM_Init(const SchM_ConfigType *SchM_Config)
{
	SchM_ConfigGlobal = SchM_Config;
	uint8_t LocTaskIdx;
	SchM_Control.SchM_State = SCHM_UNINIT; /*SchM_Control checks number of ticks and scheduler status*/
	for(LocTaskIdx = 0U; LocTaskIdx < SchM_ConfigGlobal->SchM_NumOfTasks; LocTaskIdx++){
		SchM_TaskControlBlock[LocTaskIdx].SchM_TaskState = SCHM_TASK_STATE_SUSPENDED; /*All 6 task state are set up in suspended state */
	}
	SysTick_Init(SchM_OsTick);           /* Initialize PIT0 for 781.25 micro-seconds timeout & Callback Install */
	SchM_Control.SchM_State = SCHM_INIT; /*Scheduler is initialized*/
}
/*******************************************************************************
 *  Name                 : SchM_Start
 *  Description          : Starts the scheduler
 *  Parameters           : [void]
 *  Return               : void
 *  Critical/explanation : No
 ******************************************************************************/
void SchM_Start(void)
{
	//interrupts_EnableSysTickIRQ();
	SchM_Background();
}
/*******************************************************************************
 *  Name                 : SchM_Stop
 *  Description          : Stops the scheduler
 *  Parameters           : [void]
 *  Return               : void
 *  Critical/explanation : No
 ******************************************************************************/
void SchM_Stop(void){
	//interrupts_DisableSysTickIRQ();
}
/***********************Private Function Implementation************************/
/*******************************************************************************
 *  Name                 : SchM_OsTick
 *  Description          : OS Tick Function
 *  Parameters           : [void]
 *  Return               : void
 *  Critical/explanation : No
 ******************************************************************************/
static void SchM_OsTick     (void)
{
	uint8_t lub_Index;
	for(lub_Index = 0U; lub_Index < SchM_ConfigGlobal->SchM_NumOfTasks; lub_Index++){
	   if(((uint32_t)(SchM_ConfigGlobal->SchM_TaskDescriptor[lub_Index].SchM_TaskMask) & (SchM_Control.SchM_OsTickCounter)) /*if((Counter & Mask) == Offset)*/
			== SchM_ConfigGlobal->SchM_TaskDescriptor[lub_Index].SchM_TaskOffset)
	   {
		   if(SCHM_RUNNING == SchM_Control.SchM_State) /*Review if there is any Task in Running or Start State before activating other task*/
		   {
			   SchM_Control.SchM_State = SCHM_OVERLOAD;      // Set Overload Flag
			   //leds_TurnOnDownLED();
		   }
	       SchM_TaskControlBlock[lub_Index].SchM_TaskState = SCHM_TASK_STATE_READY;
	   }
	   else {
	      // No-Task to be executed
	   }
	}
	SchM_Control.SchM_OsTickCounter++;
}
/*******************************************************************************
 *  Name                 : SchM_Background
 *  Description          : Background Task
 *  Parameters           : [void]
 *  Return               : void
 *  Critical/explanation : No
 ******************************************************************************/
static void SchM_Background (void)
{
	uint8_t ub_LocTaskIdx;  // Protect this variable due to an interrupt
	for(;;)
	{
	    for(ub_LocTaskIdx = 0U; ub_LocTaskIdx < SchM_ConfigGlobal->SchM_NumOfTasks; ub_LocTaskIdx++)
	    {
	    	if(SCHM_TASK_STATE_READY == SchM_TaskControlBlock[ub_LocTaskIdx].SchM_TaskState)
	    	{
	    		SchM_TaskControlBlock[ub_LocTaskIdx].SchM_TaskState = SCHM_TASK_STATE_RUNNING;
	    		SchM_Control.SchM_State = SCHM_RUNNING;
	    		//leds_TurnOnUpLED();
	    		SchM_ConfigGlobal->SchM_TaskDescriptor[ub_LocTaskIdx].SchM_TaskFunctionPtr();
	    		//leds_TurnOffUpLED();
	    		SchM_TaskControlBlock[ub_LocTaskIdx].SchM_TaskState = SCHM_TASK_STATE_SUSPENDED;
	    		SchM_Control.SchM_State = SCHM_IDLE;
	    	}
	    	else
	    	{
	        // Background Task
	    	}
	    }
	}
}
/*******************************************************************************
 *  Name                 : SysTick_Init
 *  Description          : Initializes the SysTick
 *  Parameters           : [tCallbackFunction Callback]
 *  Return               : void
 *  Critical/explanation : No
 ******************************************************************************/
static void SysTick_Init(tCallbackFunction Callback)
{
	//interrupts_InitIRQ(SysTick_IRQn, 0xA);
	//interrupts_ConfigSysTickIRQ(62500);   // Configure SysTick Clock
	GlbSysTickCallback = Callback;
}

/******************************************************************************/
/*******************************************************************************
|   Author    |     Date    |                  Description                     |
|-------------|-------------|--------------------------------------------------|
|  Carlos M   | 05-Jan-2021 | Scheduler Inital version.                        |
*******************************************************************************/
