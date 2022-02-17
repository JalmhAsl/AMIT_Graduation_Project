#ifndef		TMR_CONFIG_H
#define		TMR_CONFIG_H



/********************************************************/
/* Wave Generation Mode can be:							*/
/*						TMR_NORMAL_MODE					*/
/*						TMR_PWM_PHASE_CORRECT_MODE		*/
/*						TMR_CTC_MODE					*/
/*						TMR_FAST_PWM_MODE				*/
/********************************************************/
#define		TMR2_WAVE_GENER_MODE			TMR_FAST_PWM_MODE



/********************************************************/
/* Compare Output Mode can be:							*/
/*						TMR_OC_DISCONNECT_OUTPUT		*/
/*						TMR_OC_TOGGLE_OUTPUT*			*/
/*						TMR_OC_CLEAR_OUTPUT				*/
/*						TMR_OC_SET_OUTPUT				*/
/*														*/
/*			*(Only if Non-PWM mode is selected)			*/
/********************************************************/
#define		TMR2_COMP_OUTPUT_MODE			TMR_OC_CLEAR_OUTPUT



/********************************************************/
/* Clock Select Mode can be:							*/
/*						TMR_NO_CLOCK_SOURCE				*/
/*						TMR_NO_PRESCALER				*/
/*						TMR_PRESCALER_8					*/
/*						TMR_PRESCALER_32				*/
/*						TMR_PRESCALER_64				*/
/*						TMR_PRESCALER_128				*/
/*						TMR_PRESCALER_256				*/
/*						TMR_PRESCALER_1024				*/
/********************************************************/
#define		TMR2_CLK_SELECT_MODE			TMR_PRESCALER_64

#endif