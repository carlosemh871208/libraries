/*******************************************************************************
 * Description:
 *
*******************************************************************************/
#ifndef SERVICES_SCHEDULER_SCHM_TYPES_H_
#define SERVICES_SCHEDULER_SCHM_TYPES_H_
/******************************************************************************/
/***********************************Includes***********************************/
#include "Std_Types.h"
/******************************************************************************/
/***************************New types definitions******************************/
/* The offset values to generate the task periods */
typedef enum{
  SCHM_OFFSET_ZERO,
  SCHM_OFFSET_ONE,
  SCHM_OFFSET_TWO,
  SCHM_OFFSET_THREE,
  SCHM_OFFSET_FOUR,
  SCHM_OFFSET_FIVE,
  SCHM_OFFSET_SIX
}SchM_TaskOffsetType;

/* The mask values to generate the task periods */
typedef enum{
  SCHM_MASK_3P125MS =  (uint8_t) 3U,
  SCHM_MASK_6P25MS  =  (uint8_t) 7U,
  SCHM_MASK_12P5MS  =  (uint8_t) 15U,
  SCHM_MASK_25MS    =  (uint8_t) 31U,
  SCHM_MASK_50MS    =  (uint8_t) 63U,
  SCHM_MASK_100MS   =  (uint8_t) 127U
}SchM_TaskMaskType;

/* Task ID values */
typedef enum{
  SCHM_TASKID_BKG,
  SCHM_TASKID_3P125MS,
  SCHM_TASKID_6P25MS,
  SCHM_TASKID_12P5MS,
  SCHM_TASKID_25MS,
  SCHM_TASKID_50MS,
  SCHM_TASKID_100MS
}SchM_TaskIDType;

typedef void (*TaskFunctionPtrType)(void);

/* Structure of a single Task for configuration purposes*/
typedef struct{
  SchM_TaskOffsetType SchM_TaskOffset;      /* Offset */
  SchM_TaskMaskType SchM_TaskMask;          /* Mask */
  SchM_TaskIDType SchM_TaskID;              /* Task_ID */
  TaskFunctionPtrType SchM_TaskFunctionPtr;	/* Callback, Function Ptr */
}SchM_TaskConfigType;

/* Task States */
typedef enum{
  SCHM_TASK_STATE_SUSPENDED,
  SCHM_TASK_STATE_READY,
  SCHM_TASK_STATE_RUNNING
}SchM_TaskStateType;

/* Task Control Block Structure */
typedef struct{
  SchM_TaskStateType SchM_TaskState;            /* State */
  TaskFunctionPtrType TaskFunctionControlPtr;   /* Function Pointer */
}SchM_TaskControlBlockType;

/* Scheduler States */
typedef enum{
  SCHM_UNINIT,
  SCHM_INIT,
  SCHM_IDLE,
  SCHM_RUNNING,
  SCHM_OVERLOAD,
  SCHM_HALTED
}SchM_SchedulerStateType;

/* Scheduler Control Structure */
typedef struct{
  uint32_t SchM_OsTickCounter;
  SchM_SchedulerStateType SchM_State;
}SchM_ControlType;

/* Scheduler configuration Structure for configuration purposes*/
typedef struct{
  uint8_t SchM_NumOfTasks;                              /* Number of Tasks */
  const SchM_TaskConfigType *SchM_TaskDescriptor;       /* Tasks Descriptions */
}SchM_ConfigType;
/******************************************************************************/
/*****************************Macros definitions*******************************/

/******************************************************************************/
/*****************************Exported Variables*******************************/
extern const SchM_ConfigType SchM_Config;

/*******************************************************************************
|   Author    |     Date    |                  Description                     |
|-------------|-------------|--------------------------------------------------|
|  Carlos M   | 04-Jan-2021 | Scheduler Inital version.                        |
*******************************************************************************/

#endif /* SCHEDULER_SCHM_TYPES_H_ */
