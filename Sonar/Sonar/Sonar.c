//#define MAX_VOLTAGE 4

#ifndef F_CPU
#define F_CPU 1000000 // 1 MHz clock speed
#endif


#define D4 eS_PORTA4
#define D5 eS_PORTA5
#define D6 eS_PORTA6
#define D7 eS_PORTA7
#define RS eS_PORTC6
#define EN eS_PORTC7

#define  Trigger_pin	PA0	/* Trigger pin */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <math.h>
#include "lcd.h"

static volatile int pulse = 0 ; // counts pulse width
static volatile int i = 0 ; // current state of pulse
static volatile int j = 0 ; // current state of pulse

int TimerOverflow = 0;
ISR(INT0_vect)
{
	if (i==1){
		TCCR1B=0;
		pulse=TCNT1;
		TCNT1=0;
		i=0;
	}

	if (i==0){
		TCCR1B|=(1<<CS10);
		i=1;
	}
//	GIFR|=(1<<INTF0);
}

ISR(INT1_vect)
{
	if (j==1){
		TCCR1B=0;
		pulse=TCNT1;
		TCNT1=0;
		j=0;
	}

	if (j==0){
		TCCR1B|=(1<<CS10);
		j=1;
	}
	//GIFR|=(1<<INTF1);
}

/*ISR(TIMER1_OVF_vect)
{
	TimerOverflow++;	// Increment Timer Overflow count 
}*/


int main(void)
{
	float distance = 0.0;
	int16_t val = 0 ;
	char num[16]; 
	
	DDRC= 0xFF;
	DDRA= 0xFF;
	DDRD = 0b11111011 ;
	_delay_ms(50) ;
	Lcd4_Init();
	GICR |= (1<<INT0); //using intrupt0
	//GICR |= (1<<INT2);
	MCUCR |= (1<<ISC00) ; //sonar pulse gets high to low or low to high
	//MCUCSR |= (1<<ISC01);
	TCCR1A = 0 ;
	sei (); 
	

	
	while(1)
	{
		
		PORTD |= (1<<PIND0) ;
		_delay_us(15);
		PORTD &= ~(1<<PIND0) ;
		val = pulse / 58 ;
		//ftoa (12.4756565 , num , 3) ;
		itoa  (val, num ,10) ;
		//itoa  (50, num ,10) ;
		Lcd4_Clear();
		Lcd4_Set_Cursor(1,0);
		Lcd4_Write_String("Distance Value: ");
		Lcd4_Set_Cursor(2,0);
		Lcd4_Write_String(num);
		_delay_ms(100);
		
	}

}

/*int main(void)
{
	int distance = 0,count=0;
	int16_t val = 0 ;
	char num[16];
	
	DDRC= 0xFF;
	DDRA= 0xFF;
	DDRD = 0b00000001 ;
	_delay_ms(50) ;
	Lcd4_Init();
	Lcd4_Set_Cursor(1,2);
	Lcd4_Write_String("Distance : ");
	//GICR |= (1<<INT0); //using intrupt0
//	GICR |= (1<<INT1);
	//MCUCR |= (1<<ISC00) ; //sonar pulse gets high to low or low to high
	//TCCR1A = 0 ;
	sei ();
	
	TIMSK = (1 << TOIE1);	
	TCCR1A = 0;	
	
	while(1)
	{
		
		PORTD |= (1<<PA0) ;
		//  PORTD |= (1<<PIND1) ;
		_delay_us(15);
		PORTD &= ~(1<<PA0) ;
		//  PORTD &= ~(1<<PIND1) ;
		TCNT1 = 0;	
		TCCR1B = 0x41;	
		TIFR = 1<<ICF1;	
		TIFR = 1<<TOV1;	

		while ((TIFR & (1 << ICF1)) == 0);  
		TCNT1 = 0;	
		TCCR1B = 0x01;	
		TIFR = 1<<ICF1;	
		TIFR = 1<<TOV1;	
		TimerOverflow = 0;

		while ((TIFR & (1 << ICF1)) == 0);
		count = ICR1 + (65535 * TimerOverflow);	
		// 8MHz Timer freq, sound speed =343 m/s 
		distance = (int)(count / 466);

		itoa  (distance, num ,10) ;
		//itoa  (50, num ,10) ;
		//Lcd4_Clear();
		//Lcd4_Set_Cursor(1,2);
		//Lcd4_Write_String("Distance : ");
		Lcd4_Set_Cursor(2,0);
		Lcd4_Write_String(num);
		_delay_ms(200);
		
	}

}*/
