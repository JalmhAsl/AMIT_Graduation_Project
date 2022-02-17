#include	"Std_Types.h"
#include	"Bit_Math.h"

#include 	"DIO_interface.h"
#include	"DIO_private.h"


void		DIO_voidSetPinDirection(u8 PortID, u8 PinID, u8 Direction)
{
	/*		Range Check		*/
	if(PortID < 4 && PinID < 8)
	{
		if(Direction == OUTPUT)
		{
			switch(PortID)
			{
				case PORTA :	SET_BIT(DDRA_REG, PinID);	break;
				case PORTB :	SET_BIT(DDRB_REG, PinID);	break;
				case PORTC :	SET_BIT(DDRC_REG, PinID);	break;
				case PORTD :	SET_BIT(DDRD_REG, PinID);	break;
			}
		}
		else if(Direction == INPUT)
		{
			switch(PortID)
			{
				case PORTA :	CLR_BIT(DDRA_REG, PinID);	break;
				case PORTB :	CLR_BIT(DDRB_REG, PinID);	break;
				case PORTC :	CLR_BIT(DDRC_REG, PinID);	break;
				case PORTD :	CLR_BIT(DDRD_REG, PinID);	break;
			}
		}
	}
	else
	{
		/*		Return Error		*/
	}
}

void 		DIO_voidSetPortDirection(u8 PortID, u8 Direction)
{
	/*		Range Check		*/
	if(PortID < 4)
	{
		if(Direction == OUTPUT)
		{
			switch(PortID)
			{
				case PORTA :	SET_REG(DDRA_REG);		break;
				case PORTB :	SET_REG(DDRB_REG);		break;
				case PORTC :	SET_REG(DDRC_REG);		break;
				case PORTD :	SET_REG(DDRD_REG);		break;
			}
		}
		else if(Direction == INPUT)
		{
			switch(PortID)
			{
				case PORTA :	CLR_REG(DDRA_REG);		break;
				case PORTB :	CLR_REG(DDRB_REG);		break;
				case PORTC :	CLR_REG(DDRC_REG);		break;
				case PORTD :	CLR_REG(DDRD_REG);		break;
			}
		}
	}
	else
	{
		/*		Return Error		*/
	}
}

u8			DIO_u8GetPinValue(u8 PortID, u8 PinID)
{
	u8 Localu8Value = 0xFF;
	/*		Range Check		*/
	if(PortID < 4 && PinID < 8)
	{
		switch(PortID)
		{
			case PORTA :	Localu8Value = GET_BIT(DDRA_REG, PinID);	break;
			case PORTB :	Localu8Value = GET_BIT(DDRB_REG, PinID);	break;
			case PORTC :	Localu8Value = GET_BIT(DDRC_REG, PinID);	break;
			case PORTD :	Localu8Value = GET_BIT(DDRD_REG, PinID);	break;
		}
	}
	else
	{
		/*		Return Error		*/
	}

	return Localu8Value;
}

u8 			DIO_u8GetPortValue(u8 PortID)
{
	u8 Localu8Value = 0xFF;
	/*		Range Check		*/
	if(PortID < 4)
	{
		switch(PortID)
		{
			case PORTA :	Localu8Value = DDRA_REG;	break;
			case PORTB :	Localu8Value = DDRB_REG;	break;
			case PORTC :	Localu8Value = DDRC_REG;	break;
			case PORTD :	Localu8Value = DDRD_REG;	break;
		}
	}
	else
	{
		/*		Return Error		*/
	}

	return Localu8Value;
}

void 		DIO_voidSetPinValue(u8 PortID, u8 PinID, u8 Value)
{
	/*		Range Check		*/
	if(PortID < 4 && PinID < 8)
	{
		if(Value == HIGH)
		{
			switch(PortID)
			{
				case PORTA :	SET_BIT(PORTA_REG, PinID);	break;
				case PORTB :	SET_BIT(PORTB_REG, PinID);	break;
				case PORTC :	SET_BIT(PORTC_REG, PinID);	break;
				case PORTD :	SET_BIT(PORTD_REG, PinID);	break;
			}
		}
		else if(Value == LOW)
		{
			switch(PortID)
			{
				case PORTA :	CLR_BIT(PORTA_REG, PinID);	break;
				case PORTB :	CLR_BIT(PORTB_REG, PinID);	break;
				case PORTC :	CLR_BIT(PORTC_REG, PinID);	break;
				case PORTD :	CLR_BIT(PORTD_REG, PinID);	break;
			}
		}
	}
	else
	{
		/*		Return Error		*/
	}
}

void 		DIO_voidSetPortValue(u8 PortID, u8 Value)
{
	/*		Range Check		*/
	if(PortID < 4)
	{
		switch(PortID)
			{
				case PORTA :	ASG_REG(PORTA_REG,Value);		break;
				case PORTB :	ASG_REG(PORTB_REG,Value);		break;
				case PORTC :	ASG_REG(PORTC_REG,Value);		break;
				case PORTD :	ASG_REG(PORTD_REG,Value);		break;
			}
	}
	else
	{
		/*		Return Error		*/
	}
}