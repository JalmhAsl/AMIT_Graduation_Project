#ifndef		BIT_MATH_H
#define		BIT_MATH_H

	#define		SET_BIT(REG,BIT_NUM)		REG	|=	(1<<BIT_NUM)
	#define		CLR_BIT(REG,BIT_NUM)		REG	&= ~(1<<BIT_NUM)
	#define		TOG_BIT(REG,BIT_NUM)		REG	^= 	(1<<BIT_NUM)
	#define		GET_BIT(REG,BIT_NUM)		((REG>>BIT_NUM)	&1)
	
	#define		SET_REG(REG)	REG = (0xFF)
	#define		CLR_REG(REG)	REG &= (0x00)
	#define		ASG_REG(REG, VAL)	REG = VAL

	/*	Your Tasks											*/
	
	#define		CRCL_SHIFT(REG,BIT_NUM, ISLEFT)		REG = ( (ISLEFT) == (1) ? (REG<<BIT_NUM) | (REG>>8-BIT_NUM) : (REG>>BIT_NUM) | (REG<<8-BIT_NUM) )
	#define		SET_NIBBLE(REG,ISLEFT)	REG |= ( (ISLEFT) == (1) ? (11110000) : (00001111) )
	#define		CLR_NIBBLE(REG,ISLEFT)	REG &= ( (ISLEFT) == (1) ? (00001111) : (11110000) )
	
#endif