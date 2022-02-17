/*
 * GLCD_Microchip.c
 *
 * Created: 12.02.2022 17:05:00
 * Author : Jalal
 */ 

#define		F_CPU		16000000UL

#include "Std_Types.h"
#include "Bit_Math.h"

#include "DIO_interface.h"

#include "GLCD_interface.h"
#include "TMR2_interface.h"

#include <util/delay.h>


typedef		unsigned	long	int		L32 ;


void	DisplayGraph(u8 Scale_Factor, L32 Frequency)
{
	/*---------------------------------- Display PWM Information ---------------------------------*/
	u8 OCR_Val = TMR2_u8ReadOCR2();
	u8 Compare_Output_Mode = TMR2_u8ReadCompareOuputMode();
	u8 Wave_Generation_Mode = TMR2_ReadWaveGenerMode();
	u16 Prescaler = TMR2_u16ReadPrescalerMode();
	
	
	/*	Data displayed on screen	*/
	u16 Frequ = 0;
	u8 Duty_Cycle = 0;
	u16 Time_Period = 0;
	
	
	/*	Keeps track of units of frequency	*/
	u8 isHz;

	
	/*	Checks if timer's wave generation mode is Fast PWM	*/
	if(Wave_Generation_Mode == TMR_FAST_PWM_MODE) 
	{
		if(Frequency/Prescaler/256 > 0)	// Checks if frequency is greater than 1 Hz
		{
			Frequ = Frequency/Prescaler/256;
			Time_Period = 1000/Frequ;
			isHz = 1;
		}
		else
		{
			Frequ = Frequency*1000/Prescaler/256;
			Time_Period = 1000000/Frequ;
			isHz = 0;
		}
		
		if(Compare_Output_Mode == TMR_OC_CLEAR_OUTPUT) {Duty_Cycle = ((OCR_Val + 1)*100)/256;}
		else if(Compare_Output_Mode == TMR_OC_SET_OUTPUT) {Duty_Cycle = ((255 - OCR_Val)*100)/256;}
	}
	
	
	/*	Checks if timer's wave generation mode is Phase Correct PWM	*/
	else if (Wave_Generation_Mode == TMR_PWM_PHASE_CORRECT_MODE) 
	{
		if(Frequency/Prescaler/510 > 0)
		{
			Frequ = Frequency/Prescaler/510;
			Time_Period = 1000/Frequ;
			isHz = 1;
		}
		else
		{
			Frequ = Frequency*1000/Prescaler/510;
			Time_Period = 1000000/Frequ;
			isHz = 0;
		}
		
		if(Compare_Output_Mode == TMR_OC_CLEAR_OUTPUT) {Duty_Cycle = (OCR_Val*100)/255;}
		else if(Compare_Output_Mode == TMR_OC_SET_OUTPUT) {Duty_Cycle = ((255 - OCR_Val)*100)/255;}
	}
	
	
	/*	If wave generation mode is not PWM, writes error message and returns from function	*/
	else
	{
		GLCD_voidSetXY(5,0);
		GLCD_voidWriteStr((u8*) "Please choose a PWM Mode");
		return;
	}
	
	
	/*	Display Frequency Info and checks the units of frequency	*/
	GLCD_voidSetXY(0,0);
	GLCD_voidWriteStr((u8*) "Frequency: ");
	if(isHz)
	{
		GLCD_voidWriteInt(Frequ);
		GLCD_voidWriteStr((u8*) "Hz");
	}
	else
	{
		GLCD_voidWriteInt(Frequ);
		GLCD_voidWriteStr((u8*) "mHz");
	}

	/*	Display Duty Cycle Info		*/
	GLCD_voidSetXY(1,0);
	GLCD_voidWriteStr((u8*) "Duty Cycle: ");
	GLCD_voidWriteInt(Duty_Cycle);
	GLCD_voidWriteStr((u8*) "%");
	
	/*	Display Separation Line		*/
	for (u8 i = 0; i < 128; i++)
	{
		GLCD_voidSetXY(2,i);
		GLCD_voidSendData(0b00011000);
	}

	
	/*----------------------------------- Display PWM Graph ------------------------------------------------*/
	/*																										*/
	/*	A PWM pulse width is made of 256 time units on horizontal axis.										*/
	/*	The amount of periods displayed on the screen can be controlled using the Scale Factor value.		*/
	/*	Scale Factor can take values of 2, 4, 8, 16 and 32. Any other value fails to draw a coherent graph.	*/
	/*	Each period on the graph has a width of 256/Scale Factor.											*/
	/*------------------------------------------------------------------------------------------------------*/
	
	/*	Check if Scale Factor has correct values	*/
	if(Scale_Factor != 2 && Scale_Factor != 4 && Scale_Factor != 8 && Scale_Factor != 16 && Scale_Factor != 32)
	{
		GLCD_voidSetXY(5,0);
		GLCD_voidWriteStr((u8*) "Prescaler must be 2, 4, 8, 16 or 32");
		return;
	}
	
	u8 Pixel_Per_Period = 256 / Scale_Factor;
	u8 Graphical_LCD_Width = 128;
	
	u8 TCNT_Period_Counter = 0;
	
	u8 text_position = 0;
	
	u8 High = 0, Low = 0, Edge = 0;
	
	
	/*	Defines which Compare Output Mode is chosen	*/
	if(Compare_Output_Mode == TMR_OC_CLEAR_OUTPUT)
	{
		High = 0x01;
		Edge = 0xFF;
		Low = 0x80;
	}
	else if(Compare_Output_Mode == TMR_OC_SET_OUTPUT)
	{
		High = 0x80;
		Edge = 0xFF;
		Low = 0x01;
	}
	else if(Compare_Output_Mode == TMR_OC_DISCONNECT_OUTPUT)
	{
		GLCD_voidSetXY(5,0);
		GLCD_voidWriteStr((u8*) "Output Disconnected");
		return;
	}
	else
	{
		GLCD_voidSetXY(5,0);
		GLCD_voidWriteStr((u8*) "Bad Choice of Compare Output Mode");
		return;
	}
	
	
	/*	Outer loop offsets period by X pixels each cycle	*/
	for(u8 Phase_Shift = 0; Phase_Shift < Graphical_LCD_Width; Phase_Shift+=Pixel_Per_Period)
	{
		/*	OCR_Val is calculated to match GLCD scale and period	*/
		u8 OCR_Coord = (OCR_Val/Scale_Factor) + Phase_Shift;
		
		/*	Wave generated by Fast PWM	*/
		if(Wave_Generation_Mode == TMR_FAST_PWM_MODE)
		{
			/*	Inner loop draws the curve according to OCR	*/
			for (u8 i = 0 + Phase_Shift; i < Pixel_Per_Period + Phase_Shift; i++)
			{
				GLCD_voidSetXY(5,i);
				
				if(i < OCR_Coord)
				GLCD_voidSendData(High);
				else if(i == OCR_Coord)
				GLCD_voidSendData(Edge);
				else if(i > OCR_Coord && i < Pixel_Per_Period - 1 + Phase_Shift)
				GLCD_voidSendData(Low);
				else if(i == Pixel_Per_Period - 1 + Phase_Shift)
				GLCD_voidSendData(Edge);
				
				/*	Draws lines of time period	*/
				if(TCNT_Period_Counter == 0)
				{
					GLCD_voidSetXY(6,i);
					if(i == 0 + Phase_Shift || i == Pixel_Per_Period - 1 + Phase_Shift)
					GLCD_voidSendData(0xFC);
					else
					GLCD_voidSendData(0x10);
					
					text_position = i - Phase_Shift;
				}
			}
		}
		
		
		/*	Wave generated by Phase Correct PWM	*/
		else if(Wave_Generation_Mode == TMR_PWM_PHASE_CORRECT_MODE)
		{
			/*	Inner loop draws the curve according to OCR	*/
			for (u8 i = 0 + Phase_Shift; i < Pixel_Per_Period + Phase_Shift; i++)
			{
				GLCD_voidSetXY(5,i);
					
				if(TCNT_Period_Counter%2 == 0)
				{
					if(i < OCR_Coord)
					GLCD_voidSendData(High);
					else if(i == OCR_Coord)
					GLCD_voidSendData(Edge);
					else if(i > OCR_Coord)
					GLCD_voidSendData(Low);
				}
				
				else if(TCNT_Period_Counter%2 == 1)
				{
					if(i - Phase_Shift > Pixel_Per_Period + Phase_Shift - 1 - OCR_Coord)
					GLCD_voidSendData(High);
					else if(i - Phase_Shift == Pixel_Per_Period + Phase_Shift - 1 - OCR_Coord)
					GLCD_voidSendData(Edge);
					else if(i - Phase_Shift < Pixel_Per_Period + Phase_Shift - 1 - OCR_Coord) //32 - 32 = 0 < 32 + 32 - 63 = 1
					GLCD_voidSendData(Low);
				}
				
				
				
				/*	Displays lines of Time Period	*/
				if(TCNT_Period_Counter == 0)
				{
					GLCD_voidSetXY(6,i);
					if(i == 0 + Phase_Shift)
					GLCD_voidSendData(0xFC);
					else
					GLCD_voidSendData(0x10);
					
					text_position = i - Phase_Shift;
				}
				else if(TCNT_Period_Counter == 1)
				{
					GLCD_voidSetXY(6,i);
					if(i == Pixel_Per_Period - 1 + Phase_Shift)
					GLCD_voidSendData(0xFC);
					else
					GLCD_voidSendData(0x10);
				}
			}
		}
		/*	Increment TCNT period counter after each iteration of outer for loop	*/	
		TCNT_Period_Counter++;
	}
	
	/*	Draws period value on last row	*/
	if (Wave_Generation_Mode == TMR_FAST_PWM_MODE || Wave_Generation_Mode == TMR_PWM_PHASE_CORRECT_MODE)
	{
		/*	Position of Period Text		*/
		GLCD_voidSetXY(7,text_position - (Pixel_Per_Period/2));
		GLCD_voidWriteInt(Time_Period);
		GLCD_voidWriteStr((u8*) "ms");
	}
}


int main(void)
{
	/*	Timer Pins Directions			*/
	DIO_voidSetPinDirection(PORTC, PIN6, INPUT);	//TOSC1
	DIO_voidSetPinDirection(PORTC, PIN7, INPUT);	//TOSC2
	
	DIO_voidSetPinDirection(PORTD, PIN7, OUTPUT);	//OC2
	
	
	/*	GLCD and TMR2 initialization	*/
    GLCD_voidInit();
	TMR2_voidInit();
	
	/*	Asynchronous Mode Disabled		*/
	TMR2_voidDisableAsynchronous();
	
	/*	Initial value to TCNT2, controls frequency		*/
	TMR2_voidWriteTCNT(0);
	TMR2_voidWriteOCR2(240);
	
	DisplayGraph(8, F_CPU);

	_delay_ms(300);
	GLCD_voidClearAll();
	
	/*	Asynchronous Mode Enabled		*/
	TMR2_voidEnableAsynchronous();
	
	/*	Initial value to TCNT2, controls frequency		*/
	TMR2_voidWriteTCNT(0);
	TMR2_voidWriteOCR2(200);
	
	GLCD_voidClearPage(0);
	GLCD_voidClearPage(1);			// To avoid ghost remaining characters
	
	DisplayGraph(8, 32768);		// 32.768 KHz from Crystal Oscillator
	
    while (1) 
    {	
    }
}
