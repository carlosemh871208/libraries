/*******************************************************************************
 * Description:
 *
*******************************************************************************/
#ifndef LIBRARIES_STD_TYPES_H_
#define LIBRARIES_STD_TYPES_H_
/******************************************************************************/
/***********************************Includes***********************************/

/******************************************************************************/
/***************************New types definitions******************************/
/*Unsigned data types*/
typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned long  uint32_t;

/*Signed data types*/
typedef signed char    sint8_t;
typedef signed short   sint16_t;
typedef signed long    sint32_t;

/*Boolean definition*/
#ifndef boolean
typedef uint8_t boolean;
#endif

/*RTOS task states definition*/
#ifndef taskState
typedef uint8_t taskState;
#endif

typedef void (*tCallbackFunction)(void);
/******************************************************************************/
/*****************************Macros definitions*******************************/
/*Boolean macros*/
#define FALSE ((uint8_t) 0U)
#define TRUE  ((uint8_t) 1U)

/*Main program macros*/
#define EXIT_SUCCESS ((uint8_t) 0U)

/*Read only variable macro*/
#define __I  volatile const

/*Write only variable macro*/
#define __O  volatile

/*Read / Write variable macro*/
#define __IO volatile

/*32 bits memory read macro*/
#if !defined(REG_READ32)
  #define REG_READ32(address)               (*(volatile uint32_t*)(address))
#endif

/*32 bits memory write macro*/
#if !defined(REG_WRITE32)
  #define REG_WRITE32(address, value)       ((*(volatile uint32_t*)(address))= (uint32_t)(value))
#endif

/*32 bits setting macro*/
#if !defined(REG_BIT_SET32)
  #define REG_BIT_SET32(address, mask)      ((*(volatile uint32_t*)(address))|= (uint32_t)(mask))
#endif

/*32 bits clearing macro*/
#if !defined(REG_BIT_CLEAR32)
  #define REG_BIT_CLEAR32(address, mask)    ((*(volatile uint32_t*)(address))&= ((uint32_t)~((uint32_t)(mask))))
#endif

/******************************************************************************/


/*******************************************************************************
|   Author    |     Date    |                  Description                     |
|-------------|-------------|--------------------------------------------------|
|  Carlos M   | 21-Dec-2020 | First code version.                              |
|  Carlos M   | 28-Dec-2020 | Added macros for register declaration            |
*******************************************************************************/
#endif /* LIBRARIES_STD_TYPES_H_ */
