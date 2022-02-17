#ifndef		TMR_INTERFACE_H
#define		TMR_INTERFACE_H


/*------------------ TIMER 2 -----------------------*/

void	TMR2_voidInit(void);

void	TMR2_voidWriteTCNT(u8);
u8		TMR2_u8ReadTCNT(void);

void	TMR2_voidWriteOCR2(u8);
u8		TMR2_u8ReadOCR2(void);

u8		TMR2_u8ReadCompareOuputMode(void);
u16		TMR2_u16ReadPrescalerMode(void);

u8		TMR2_ReadWaveGenerMode(void);

void	TMR2_voidInterruptEnable(void);
void	TMR2_voidInterruptDisable(void);

void	TMR2_voidEnableAsynchronous(void);
void	TMR2_voidDisableAsynchronous(void);

void	TMR2_voidSetCallback(void (*PF)(void));

void	__vector_5(void)	__attribute__((signal,used));



/*			Wave Generation Modes				*/
#define		TMR_NORMAL_MODE					0
#define		TMR_PWM_PHASE_CORRECT_MODE		1
#define		TMR_CTC_MODE					2
#define		TMR_FAST_PWM_MODE				3


/*			Compare Output Modes				*/
#define		TMR_OC_DISCONNECT_OUTPUT		0
#define		TMR_OC_TOGGLE_OUTPUT			1	//Only available for Timer 0
#define		TMR_OC_CLEAR_OUTPUT				2
#define		TMR_OC_SET_OUTPUT				3


/*			Clock Select Modes					*/
#define		TMR_NO_CLOCK_SOURCE				0
#define		TMR_NO_PRESCALER				1
#define		TMR_PRESCALER_8					2
#define		TMR_PRESCALER_32				3
#define		TMR_PRESCALER_64				4
#define		TMR_PRESCALER_128				5
#define		TMR_PRESCALER_256				6
#define		TMR_PRESCALER_1024				7	


#endif