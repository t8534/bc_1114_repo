/*
    FreeRTOS V8.2.1 - Copyright (C) 2015 Real Time Engineers Ltd.
    All rights reserved

    VISIT http://www.FreeRTOS.org TO ENSURE YOU ARE USING THE LATEST VERSION.

    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation >>!AND MODIFIED BY!<< the FreeRTOS exception.

    ***************************************************************************
    >>!   NOTE: The modification to the GPL is included to allow you to     !<<
    >>!   distribute a combined work that includes FreeRTOS without being   !<<
    >>!   obliged to provide the source code for proprietary components     !<<
    >>!   outside of the FreeRTOS kernel.                                   !<<
    ***************************************************************************

    FreeRTOS is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.  Full license text is available on the following
    link: http://www.freertos.org/a00114.html

    ***************************************************************************
     *                                                                       *
     *    FreeRTOS provides completely free yet professionally developed,    *
     *    robust, strictly quality controlled, supported, and cross          *
     *    platform software that is more than just the market leader, it     *
     *    is the industry's de facto standard.                               *
     *                                                                       *
     *    Help yourself get started quickly while simultaneously helping     *
     *    to support the FreeRTOS project by purchasing a FreeRTOS           *
     *    tutorial book, reference manual, or both:                          *
     *    http://www.FreeRTOS.org/Documentation                              *
     *                                                                       *
    ***************************************************************************

    http://www.FreeRTOS.org/FAQHelp.html - Having a problem?  Start by reading
    the FAQ page "My application does not run, what could be wrong?".  Have you
    defined configASSERT()?

    http://www.FreeRTOS.org/support - In return for receiving this top quality
    embedded software for free we request you assist our global community by
    participating in the support forum.

    http://www.FreeRTOS.org/training - Investing in training allows your team to
    be as productive as possible as early as possible.  Now you can receive
    FreeRTOS training directly from Richard Barry, CEO of Real Time Engineers
    Ltd, and the world's leading authority on the world's leading RTOS.

    http://www.FreeRTOS.org/plus - A selection of FreeRTOS ecosystem products,
    including FreeRTOS+Trace - an indispensable productivity tool, a DOS
    compatible FAT file system, and our tiny thread aware UDP/IP stack.

    http://www.FreeRTOS.org/labs - Where new FreeRTOS products go to incubate.
    Come and try FreeRTOS+TCP, our new open source TCP/IP stack for FreeRTOS.

    http://www.OpenRTOS.com - Real Time Engineers ltd. license FreeRTOS to High
    Integrity Systems ltd. to sell under the OpenRTOS brand.  Low cost OpenRTOS
    licenses offer ticketed support, indemnification and commercial middleware.

    http://www.SafeRTOS.com - High Integrity Systems also provide a safety
    engineered and independently SIL3 certified version for use in safety and
    mission critical applications that require provable dependability.

    1 tab == 4 spaces!
*/

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"

/* Demo includes. */
#include "IntQueueTimer.h"
#include "IntQueue.h"

/* Hardware includes. */
//#include "lpc11xx.h"  //arek: old
// TODO replace this file contents with using drivers.
#include "chip.h"

/* The two timer frequencies. */
#define tmrTIMER_2_FREQUENCY	( 2000UL )
#define tmrTIMER_3_FREQUENCY	( 2001UL )

/* The priorities for the two timers.  Note that a priority of 0 is the highest
possible on Cortex-M devices. */
#define tmrMAX_PRIORITY				( 0UL )
#define trmSECOND_HIGHEST_PRIORITY ( tmrMAX_PRIORITY + 1 )

void vInitialiseTimerForIntQueueTest( void )
{

#if 0
	/* Enable timer 1 clock */
	Chip_TIMER_Init(LPC_TIMER32_0);

	/* Timer rate is system clock rate */
	timerFreq = Chip_Clock_GetSystemClockRate();

	/* Timer setup for match and interrupt at TICKRATE_HZ */
	Chip_TIMER_Reset(LPC_TIMER32_0);
	Chip_TIMER_MatchEnableInt(LPC_TIMER32_0, 1);
	Chip_TIMER_SetMatch(LPC_TIMER32_0, 1, (timerFreq / TICKRATE_HZ2));
	Chip_TIMER_ResetOnMatchEnable(LPC_TIMER32_0, 1);
	Chip_TIMER_Enable(LPC_TIMER32_0);

	/* Enable timer interrupt */
	NVIC_ClearPendingIRQ(TIMER_32_0_IRQn);
	NVIC_EnableIRQ(TIMER_32_0_IRQn);
#endif

	uint32_t timerFreq;

	/* Enable AHB clock for GPIO and 16-bit timers. */
	//arek old
	// LPC_SYSCON->SYSAHBCLKCTRL |= ( 7 << 6 );  // Seems to be it only enable CT16B0, CT16B1

	/* Enable AHB clock for 16-bit timers. */
	Chip_TIMER_Init(LPC_TIMER16_0);
	Chip_TIMER_Init(LPC_TIMER16_1);



	/* Interrupt and reset on MR0 match. */
	//arek old
	//LPC_TMR16B0->MCR = 0x03;
	//LPC_TMR16B1->MCR = 0x03;
	Chip_TIMER_Reset(LPC_TIMER16_0);
	Chip_TIMER_Reset(LPC_TIMER16_1);
	Chip_TIMER_ResetOnMatchEnable(LPC_TIMER16_0, 0);  //TODO: arek, check is 0
	Chip_TIMER_ResetOnMatchEnable(LPC_TIMER16_1, 0);  //TODO: arek, check is 0
	Chip_TIMER_MatchEnableInt(LPC_TIMER16_0, 0);  //TODO: arek, check is 0
	Chip_TIMER_MatchEnableInt(LPC_TIMER16_1, 0);  //TODO: arek, check is 0


	/* Configure the frequency of the interrupt generated by MR0 matches. */
	//arek old
	//LPC_TMR16B0->MR0 = SystemCoreClock / tmrTIMER_2_FREQUENCY;
	//LPC_TMR16B1->MR0 = SystemCoreClock / tmrTIMER_3_FREQUENCY;
	timerFreq = Chip_Clock_GetSystemClockRate();
	Chip_TIMER_SetMatch(LPC_TIMER16_0, 0, (timerFreq / tmrTIMER_2_FREQUENCY));  //TODO: arek, check is 0
	Chip_TIMER_SetMatch(LPC_TIMER16_1, 0, (timerFreq / tmrTIMER_3_FREQUENCY));  //TODO: arek, check is 0


	/* Don't generate interrupts until the scheduler has been started.
	Interrupts will be automatically enabled when the first task starts
	running. */
	taskDISABLE_INTERRUPTS();

	/* Set the timer interrupts to be above the kernel.  The interrupts are
	assigned different priorities so they nest with each other. */
	NVIC_SetPriority( TIMER_16_0_IRQn, trmSECOND_HIGHEST_PRIORITY );
	NVIC_SetPriority( TIMER_16_1_IRQn, tmrMAX_PRIORITY );

	/* Enable the timer interrupts. */
	NVIC_EnableIRQ( TIMER_16_0_IRQn );
	NVIC_EnableIRQ( TIMER_16_1_IRQn );

	/* Start the timers. */
	//arek old
	//LPC_TMR16B0->TCR = 0x01;
	//LPC_TMR16B1->TCR = 0x01;
	Chip_TIMER_Enable(LPC_TIMER16_0);
	Chip_TIMER_Enable(LPC_TIMER16_1);

}
/*-----------------------------------------------------------*/
void TIMER16_0_IRQHandler(void)
{
#if 0
	if (Chip_TIMER_MatchPending(LPC_TIMER32_0, 1)) {
		Chip_TIMER_ClearMatch(LPC_TIMER32_0, 1);
		Board_LED_Set(0, true);
	}
#endif

	/* Clear the interrupt. */
	//arek: old
	//LPC_TMR16B0->IR = LPC_TMR16B0->IR;
	Chip_TIMER_ClearMatch(LPC_TIMER16_0, 0);  //TODO: arek, check is 0


	/* Call the  standard demo int queue timer function for this first timer. */
	portEND_SWITCHING_ISR( xFirstTimerHandler() );
}
/*-----------------------------------------------------------*/

void TIMER16_1_IRQHandler(void)
{
	/* Clear the interrupt. */
	//arek: old
	//LPC_TMR16B1->IR = LPC_TMR16B1->IR;
	Chip_TIMER_ClearMatch(LPC_TIMER16_1, 0);  //TODO: arek, check is 0


	/* Call the standard demo int queue timer function for this second timer. */
	portEND_SWITCHING_ISR( xSecondTimerHandler() );
}
/*-----------------------------------------------------------*/
