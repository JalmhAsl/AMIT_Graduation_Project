#ifndef		GLCD_INTERFACE_H
#define		GLCD_INTERFACE_H

void	GLCD_voidInit(void);
void	GLCD_voidSendCMD(u8);
void	GLCD_voidSendData(u8);

void	GLCD_voidWriteStr(u8*);
void	GLCD_voidWriteInt(u16);

void	GLCD_voidSelectStartLine(u8);
void	GLCD_voidSelectPage(u8);
void	GLCD_voidSelectColumn(u8);
void	GLCD_voidSelectScreen(u8);

void	GLCD_voidSetXY(u8,u8);

void	GLCD_voidClearPage(u8);
void	GLCD_voidClearAll(void);


#endif