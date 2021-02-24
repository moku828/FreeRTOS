/*
 * FreeRTOS Kernel V10.3.0
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 4 spaces!
 */

/*-----------------------------------------------------------
 * Simple IO routines to control the LEDs.
 *-----------------------------------------------------------*/

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"

/* Demo includes. */
#include "partest.h"

#define partestNUM_LEDS ( 1 )
#define partestALL_LEDS ( usLEDMasks[ 0 ] )

static const unsigned short usLEDMasks[ partestNUM_LEDS ] = { ( 1 << 8 ) };
/*-----------------------------------------------------------*/

void vParTestInitialise( void )
{
	/* Select port functions for PE9 to PE15. */
	PCCR2 &= ( unsigned short ) ~partestALL_LEDS;

	/* Turn all LEDs off. */
	PCDR0 &= ( unsigned short ) ~partestALL_LEDS;
	
	/* Set all LEDs to output. */
	PCIOR0 |= ( unsigned short ) partestALL_LEDS;
}
/*-----------------------------------------------------------*/

void vParTestSetLED( unsigned portBASE_TYPE uxLED, signed portBASE_TYPE xValue )
{
	if( uxLED < partestNUM_LEDS )
	{
		if( xValue )
		{
			/* Turn the LED on. */
			taskENTER_CRITICAL();
			{
				PCDR0 |= usLEDMasks[ uxLED ];
			}
			taskEXIT_CRITICAL();
		}
		else
		{
			/* Turn the LED off. */
			taskENTER_CRITICAL();
			{
				PCDR0 &= ( unsigned short ) ~usLEDMasks[ uxLED ];
			}
			taskEXIT_CRITICAL();
		}
	}
}
/*-----------------------------------------------------------*/

void vParTestToggleLED( unsigned portBASE_TYPE uxLED )
{
	if( uxLED < partestNUM_LEDS )
	{
		taskENTER_CRITICAL();
		{
			if( ( PCDR0 & usLEDMasks[ uxLED ] ) != 0x00 )
			{
				PCDR0 &= ( unsigned short ) ~usLEDMasks[ uxLED ];
			}
			else
			{
				PCDR0 |= usLEDMasks[ uxLED ];
			}
		}
		taskEXIT_CRITICAL();
	}
}
/*-----------------------------------------------------------*/
							
long lParTestGetLEDState( void )
{
	/* Returns the state of the first LED. */
	return !( PCDR0 & usLEDMasks[ 0 ] );
}
/*-----------------------------------------------------------*/




							