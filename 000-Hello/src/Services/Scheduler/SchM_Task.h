/*******************************************************************************
 * Description:
 *
*******************************************************************************/
#ifndef SERVICES_SCHEDULER_SCHM_TASK_H_
#define SERVICES_SCHEDULER_SCHM_TASK_H_
/******************************************************************************/
/***********************************Includes***********************************/

/******************************************************************************/
/***************************New types definitions******************************/

/******************************************************************************/
/*****************************Macros definitions*******************************/

/******************************************************************************/
/*****************************Exported Variables*******************************/

/******************************************************************************/
/************************Exported Function Prototypes**************************/
extern void SchM_3p125ms_Task (void);
extern void SchM_6p25ms_Task  (void);
extern void SchM_12p5ms_Task  (void);
extern void SchM_25ms_Task    (void);
extern void SchM_50ms_Task    (void);
extern void SchM_100ms_Task   (void);
/*******************************************************************************
|   Author    |     Date    |                  Description                     |
|-------------|-------------|--------------------------------------------------|
|  Carlos M   | 06-Jan-2021 | Scheduler Inital version.                        |
*******************************************************************************/
#endif /* SERVICES_SCHEDULER_SCHM_TASK_H_ */
