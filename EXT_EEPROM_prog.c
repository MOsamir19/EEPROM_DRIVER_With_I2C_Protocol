 /*****************************************************************************
 *==================******************************************================*
 *==================**   Author: Mohamed Samir Hashish      **================*
 *==================**               NTI                    **================*
 *==================******************************************================*/
 /*****************************************************************************/

#include "STD_TYPES.h"
//#include "BIT_MATH.h"
#include "util/delay.h"
#include "TWI_int.h"
#include "TWI_private.h"
#include "EXT_EEPROM_int.h"
#include "EXT_EEPROM_private.h"




void H_EXT_EEPROM_void_Init(void)
{
	M_TWI_void_Init();
}



/***************************************************************************/

void H_EXT_EEPROM_void_Write(u16 Copy_u16ByteNo , u8 Copy_u8Data,u8 EP_NUM)
{
/*Copy_u16ByteNo ->user pass num between 0 and 1023
 * for ex 900 ->  00000011 10000100
 * Copy_u8Data -> 'M'
 * EP_NUM EEPROM Number 0 or 1  for ex 1
 * */

M_TWI_u8_StartCondition();
                             /* For ex :      01010000 |   00000011 |00000100   = 01010111     */
M_TWI_u8_SendSlaveAddressWrite( EXT_EEPROM_ADDRESS_SEQ | (u8)(Copy_u16ByteNo>>8)|(EP_NUM<<2)  );

M_TWI_u8_SendByte( (u8)Copy_u16ByteNo);  /* For ex :     10000100    */

M_TWI_u8_SendByte(Copy_u8Data); /* For ex : 'M'   */

M_TWI_void_StopCondition();

	_delay_ms(10);
}

/***************************************************************************/
u8   H_EXT_EEPROM_void_Read(u16 Copy_u16ByteNo,u8 EP_NUM)
{
	/*Copy_u16ByteNo ->user pass num between 0 and 1023
	 * EP_NUM EEPROM Number 0 or 1  for ex 1   */
	u8 data = 0;
	u8 Local_u8Data=0 ;


	data=M_TWI_u8_StartCondition();
	data=M_TWI_u8_SendSlaveAddressWrite(EXT_EEPROM_ADDRESS_SEQ | (u8)(Copy_u16ByteNo>>8)|(EP_NUM<<2));
	data=M_TWI_u8_SendByte((u8)Copy_u16ByteNo);
	data=M_TWI_u8_RepeatedStart();
	data=M_TWI_u8_SendSlaveAddressRead( EXT_EEPROM_ADDRESS_SEQ | (u8)(Copy_u16ByteNo>>8)|(EP_NUM<<2));
	data=M_TWI_u8_ReadByte(&Local_u8Data);

	M_TWI_void_StopCondition();
	//_delay_ms(10);

	return Local_u8Data;
}

/***************************************************************************/
void H_EXT_EEPROM_void_Write_Str(u16 ByteNo , u8* DATA)
{
	s8 i = -1 ;
	u8 BN=ByteNo ;
       BN--;
	do
	{
		i++ ;
		BN++;
		H_EXT_EEPROM_void_Write(BN , DATA[i],0);

	}while( DATA[i] != '\0' ) ;


}

/***************************************************************************/
void H_EXT_EEPROM_void_Read_Str(u16 ByteNo , u8* DATA)
{
	s8 i = -1 ;
	u8 BN=ByteNo ;
       BN--;
	do
	{
		i++ ;
		BN++;
		DATA[i]= H_EXT_EEPROM_void_Read(BN,0);


	}while( DATA[i] != '\0' ) ;


}




