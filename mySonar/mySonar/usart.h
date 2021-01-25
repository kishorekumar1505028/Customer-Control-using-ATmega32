
#define RECEIVE_BUFF_SIZE 128
volatile char URBuff[RECEIVE_BUFF_SIZE];
volatile int16_t UQFront;
volatile int16_t UQEnd;

#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>


void USARTInit(uint16_t ubrrvalue)
{	
	UQFront=UQEnd=-1;
	
	UBRRH=(unsigned char)(ubrrvalue>>8);
	UBRRL=(unsigned char)ubrrvalue;
	UCSRA = 0 ;
	UCSRC=(1<<URSEL)|(3<<UCSZ0);
	UCSRB=(1<<RXCIE)|(1<<RXEN)|(1<<TXEN);
	
	sei();

}

ISR(USART_RXC_vect)
{
	char data=UDR;
	if(((UQEnd==RECEIVE_BUFF_SIZE-1) && UQFront==0) || ((UQEnd+1)==UQFront))
	{
		UQFront++;
		if(UQFront==RECEIVE_BUFF_SIZE) UQFront=0;
	}
	if(UQEnd==RECEIVE_BUFF_SIZE-1)
		UQEnd=0;
	else
		UQEnd++;

	URBuff[UQEnd]=data;
	if(UQFront==-1) UQFront=0;

}

char UReadData()
{
	char data;
	if(UQFront==-1)
		return 0;
	data=URBuff[UQFront];
	if(UQFront==UQEnd)
		UQFront=UQEnd=-1;	
	else
	{
		UQFront++;
		if(UQFront==RECEIVE_BUFF_SIZE)
		UQFront=0;
	}

	return data;
}

void UWriteData(char data)
{
	while(!(UCSRA & (1<<UDRE)));
	UDR=data;
}

int8_t UDataAvailable()
{
	if(UQFront==-1)
		return 0;
	if(UQFront<UQEnd)
		return(UQEnd-UQFront+1);
	else if(UQFront>UQEnd)
		return (RECEIVE_BUFF_SIZE-UQFront+UQEnd+1);
	else
		return 1;
}

void UWriteString(char *str)
{
	while(*str > 0)
		UWriteData(*str++) ;
}

void UReadBuffer(void *buff,uint16_t len)
{
	for(uint16_t i=0;i<len;i++)
		((char*)buff)[i]=UReadData();
}

void UFlushBuffer()
{
	while(UDataAvailable()>0)
		UReadData();
}
