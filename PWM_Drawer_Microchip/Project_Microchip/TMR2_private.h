#ifndef		TMR_PRIVATE_H
#define		TMR_PRIVATE_H

#define		TIMSK_REG		*((volatile u8*) 0x59)
#define		TIFR_REG		*((volatile u8*) 0x58)

/*			Timer 2 - 8 bits					*/
#define		TCCR2_REG		*((volatile u8*) 0x45)
#define		TCNT2_REG		*((volatile u8*) 0x44)
#define		OCR2_REG		*((volatile u8*) 0x43)

#define		ASSR_REG		*((volatile u8*) 0x42)


#endif