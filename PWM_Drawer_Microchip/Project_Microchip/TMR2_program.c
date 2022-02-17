#include	"Std_Types.h"
#include	"Bit_Math.h"

#include	"TMR2_config.h"
#include	"TMR2_private.h"
#include	"TMR2_interface.h"


#ifndef		NULL
#define		NULL	(void *)0
#endif

static		void (*TMR2_Callback) (void) = NULL;


/*-------------------- TIMER 2 ---------------------*/

void	TMR2_voidInit(void)
{
	/*	Clear last Bit				*/
	CLR_BIT(TCCR2_REG,7);
	/*	Wave Generation Mode		*/
	#if 	TMR2_WAVE_GENER_MODE == TMR_NORMAL_MODE
	CLR_BIT(TCCR2_REG,6);
	CLR_BIT(TCCR2_REG,3);
	#elif	TMR2_WAVE_GENER_MODE == TMR_PWM_PHASE_CORRECT_MODE
	SET_BIT(TCCR2_REG,6);
	CLR_BIT(TCCR2_REG,3);
	#elif	TMR2_WAVE_GENER_MODE == TMR_CTC_MODE
	CLR_BIT(TCCR2_REG,6);
	SET_BIT(TCCR2_REG,3);
	#elif	TMR2_WAVE_GENER_MODE == TMR_FAST_PWM_MODE
	SET_BIT(TCCR2_REG,6);
	SET_BIT(TCCR2_REG,3);
	#else
	#error	"Wave Generation Mode not recognized!"
	#endif

	/*	Compare Output Mode			*/
	#if 	TMR2_COMP_OUTPUT_MODE == TMR_OC_DISCONNECT_OUTPUT
	CLR_BIT(TCCR2_REG,4);
	CLR_BIT(TCCR2_REG,5);
	#elif	TMR2_COMP_OUTPUT_MODE == TMR_OC_TOGGLE_OUTPUT
	SET_BIT(TCCR2_REG,4);
	CLR_BIT(TCCR2_REG,5);
	#elif	TMR2_COMP_OUTPUT_MODE == TMR_OC_CLEAR_OUTPUT
	CLR_BIT(TCCR2_REG,4);
	SET_BIT(TCCR2_REG,5);
	#elif	TMR2_COMP_OUTPUT_MODE == TMR_OC_SET_OUTPUT
	SET_BIT(TCCR2_REG,4);
	SET_BIT(TCCR2_REG,5);
	#else
	#error	"Compare Output Mode not recognized!"
	#endif

	/*	Clock Select Mode			*/
	#if 	TMR2_CLK_SELECT_MODE == TMR_NO_CLOCK_SOURCE
	CLR_BIT(TCCR2_REG,0);
	CLR_BIT(TCCR2_REG,1);
	CLR_BIT(TCCR2_REG,2);
	#elif	TMR2_CLK_SELECT_MODE == TMR_NO_PRESCALER
	SET_BIT(TCCR2_REG,0);
	CLR_BIT(TCCR2_REG,1);
	CLR_BIT(TCCR2_REG,2);
	#elif	TMR2_CLK_SELECT_MODE == TMR_PRESCALER_8
	CLR_BIT(TCCR2_REG,0);
	SET_BIT(TCCR2_REG,1);
	CLR_BIT(TCCR2_REG,2);
	#elif	TMR2_CLK_SELECT_MODE == TMR_PRESCALER_32
	SET_BIT(TCCR2_REG,0);
	SET_BIT(TCCR2_REG,1);
	CLR_BIT(TCCR2_REG,2);
	#elif	TMR2_CLK_SELECT_MODE == TMR_PRESCALER_64
	CLR_BIT(TCCR2_REG,0);
	CLR_BIT(TCCR2_REG,1);
	SET_BIT(TCCR2_REG,2);
	#elif	TMR2_CLK_SELECT_MODE == TMR_PRESCALER_128
	SET_BIT(TCCR2_REG,0);
	CLR_BIT(TCCR2_REG,1);
	SET_BIT(TCCR2_REG,2);
	#elif	TMR2_CLK_SELECT_MODE == TMR_PRESCALER_256
	CLR_BIT(TCCR2_REG,0);
	SET_BIT(TCCR2_REG,1);
	SET_BIT(TCCR2_REG,2);
	#elif	TMR2_CLK_SELECT_MODE == TMR_PRESCALER_1024
	SET_BIT(TCCR2_REG,0);
	SET_BIT(TCCR2_REG,1);
	SET_BIT(TCCR2_REG,2);
	#else
	#error	"Clock Select Mode not recognized!"
	#endif
}

void	TMR2_voidWriteTCNT(u8 Val)
{
	ASG_REG(TCNT2_REG, Val);
}

u8		TMR2_u8ReadTCNT(void)
{
	return	TCNT2_REG;
}

void	TMR2_voidWriteOCR2(u8 Val)
{
	ASG_REG(OCR2_REG, Val);
}

u8		TMR2_u8ReadOCR2(void)
{
	return	OCR2_REG;
}

u8		TMR2_u8ReadCompareOuputMode(void)
{	
	return TMR2_COMP_OUTPUT_MODE;
}

u16		TMR2_u16ReadPrescalerMode(void)
{
	u16	Local_Prescaler;
	
	if(TMR2_CLK_SELECT_MODE == TMR_NO_CLOCK_SOURCE)
		Local_Prescaler = 1;
	else if(TMR2_CLK_SELECT_MODE == TMR_NO_PRESCALER)
		Local_Prescaler = 1;
	else if(TMR2_CLK_SELECT_MODE == TMR_PRESCALER_8)
		Local_Prescaler = 8;
	else if(TMR2_CLK_SELECT_MODE == TMR_PRESCALER_32)
		Local_Prescaler = 32;
	else if(TMR2_CLK_SELECT_MODE == TMR_PRESCALER_64)
		Local_Prescaler = 64;
	else if(TMR2_CLK_SELECT_MODE == TMR_PRESCALER_128)
		Local_Prescaler = 128;
	else if(TMR2_CLK_SELECT_MODE == TMR_PRESCALER_256)
		Local_Prescaler = 256;
	else if(TMR2_CLK_SELECT_MODE == TMR_PRESCALER_1024)
		Local_Prescaler = 1024;
	
	return	Local_Prescaler;
}

u8		TMR2_ReadWaveGenerMode(void)
{
	return TMR2_WAVE_GENER_MODE;
}

void	TMR2_voidInterruptEnable(void)
{
	SET_BIT(TIMSK_REG,6);
}

void	TMR2_voidInterruptDisable(void)
{
	CLR_BIT(TIMSK_REG,6);
}

void	TMR2_voidEnableAsynchronous(void)
{
	/*	Disable the Timer/Counter2 interrupts by clearing OCIE2 and TOIE2 */
	CLR_BIT(TIMSK_REG,6);
	CLR_BIT(TIMSK_REG,7);
	/*	Select Appropriate Clock Source		*/
	SET_BIT(ASSR_REG,3);
	/*	Wait for TCN2UB, OCR2UB, and TCR2UB	*/
	while(GET_BIT(ASSR_REG,0) != 0);
	while(GET_BIT(ASSR_REG,1) != 0);
	while(GET_BIT(ASSR_REG,2) != 0);
	/*	Clear Timer 2 Interrupt				*/
	CLR_BIT(TIFR_REG,6);
}

void	TMR2_voidDisableAsynchronous(void)
{
	/*	Disable the Timer/Counter2 interrupts by clearing OCIE2 and TOIE2 */
	CLR_BIT(TIMSK_REG,6);
	CLR_BIT(TIMSK_REG,7);
	/*	Select Appropriate Clock Source		*/
	CLR_BIT(ASSR_REG,3);
	/*	Clear Timer 2 Interrupt				*/
	CLR_BIT(TIFR_REG,6);
}

void	TMR2_voidSetCallback(void (*PF)(void))
{
	TMR2_Callback = PF;
}

void	__vector_5(void)
{
	TMR2_Callback();
}