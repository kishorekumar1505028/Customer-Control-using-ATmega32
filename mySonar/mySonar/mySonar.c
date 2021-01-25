/*
C Program for Distance Measurement using Ultrasonic Sensor and AVR Microocntroller
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 1000000
#include <util/delay.h>
#include <stdlib.h>
#include "usart.h"

#define enable            5
#define registerselection 6

void send_a_command(unsigned char command);
void send_a_character(unsigned char character);
void send_a_string(char *string_of_characters);

static volatile int pulse = 0;
static volatile int i = 0;
static volatile int pulse2 = 0;
static volatile int j = 0;

int main(void)
{
    DDRA = 0xFF;
    DDRB = 0xFF;
	
    DDRD = 0b11110011;
	PORTA =0;
    _delay_ms(50);
    
    GICR = (1<<INT0)|(1<<INT1);
    MCUCR=(1<<ISC00)|(1<<ISC10);
    
    TCCR1A = 0;
    
    int16_t COUNTA = 0,COUNTB=0,prevdist=0,visitorCount=0,door2flag=0;
	int opendura = 0,p=0,entryflag=0,opening=0,closing=0,wait=0,current=0;
    char SHOWA [16],SHOWB [16];
	int pattern[10];
	int sum=0;
	for(p=0;p<10;p++)
		pattern[p]= 0;
		
	//bluetooth part
	USARTInit(12);

    send_a_command(0x01); //Clear Screen 0x01 = 00000001
    _delay_ms(50);
    send_a_command(0x38);
    _delay_ms(50);
    send_a_command(0b00001111);
    _delay_ms(50);
    
    sei();
    
    while(1)
    {	
        PORTA|=(1<<PINA1);
        _delay_us(15);
        PORTA &=~(1<<PINA1);
        COUNTA = pulse/58;
		
		PORTA|=(1<<PINA2);
		_delay_us(15);
		PORTA &=~(1<<PINA2);
		COUNTB = pulse2/58;
		
		send_a_string ("vis= ");
		itoa(visitorCount,SHOWA,10);
		
		send_a_string(SHOWA);
		send_a_string("   ");
		send_a_command(0xc0);
		send_a_string ("DISTA=");
		itoa(COUNTA,SHOWA,10);
		send_a_string(SHOWA);
		send_a_string ("cm    ");
		
		send_a_command(0x80 + 0);	
        _delay_ms(10);
		
	
		if(COUNTA>=2&&COUNTA<=15&&opening==0)
		{//gate opening
			if(opening==0)
			{
				sum=0;
				for(p=0;p<10;p++)
				pattern[p]= 0;
			}
			opening=1;
			for(p=0;p<8;p++){
				PORTA |=0b00000001;
				_delay_us(2000);
				PORTA &= 0b11111110;
				_delay_ms(20);
			}	
			//_delay_ms(2000);
		}
		
		if(COUNTA>15)
			opendura++;
		if(COUNTA>15&&opendura>8&&opening==1)
		{//gate closing
			opening=0;
			opendura=0;
			//_delay_ms(3000);
			for(p=0;p<8;p++){
				PORTA |=0b00000001;
				_delay_us(1000);
				PORTA &= 0b11111110;
				_delay_ms(20);
			}
		}
		
		//updating pattern
	
		if(COUNTB>2&&COUNTB<15&&opening==1){
			sum=sum-pattern[9];
			for(p=9;p>0;p--){
				pattern[p]=pattern[p-1];
			}
			pattern[0]= COUNTB;
			sum=sum+COUNTB;
		}
		
		//increasing visitorcount
		if(COUNTB>2&&COUNTB<15&&door2flag==0){	
			visitorCount++;
			UWriteData('1');
			door2flag=1;	
		}
		
		if(COUNTB>15){
			door2flag=0;
		}
		
		char readData=UReadData();
		if(readData)
			visitorCount--;
		
		_delay_ms(100);		
    }
}

ISR(INT0_vect)
{
    if (i==1)
    {
        TCCR1B=0;
        pulse=TCNT1;
        TCNT1=0;
        i=0;
    }
    if (i==0)
    {
        TCCR1B|=(1<<CS10);
        i=1;
    }
}

ISR(INT1_vect)
{
	if (j==1)
	{
		TCCR1B=0;
		pulse2=TCNT1;
		TCNT1=0;
		j=0;
	}
	if (j==0)
	{
		TCCR1B|=(1<<CS10);
		j=1;
	}
}

void send_a_command(unsigned char command)
{
    PORTB = command;
    PORTD &= ~ (1<<registerselection);
    PORTD |= 1<<enable;
    _delay_ms(8);
    PORTD &= ~1<<enable;
    PORTB = 0;
}

void send_a_character(unsigned char character)
{
    PORTB = character;
    PORTD |= 1<<registerselection;
    PORTD |= 1<<enable;
    _delay_ms(8);
    PORTD &= ~1<<enable;
    PORTB = 0;
}
void send_a_string(char *string_of_characters)
{
    while(*string_of_characters > 0)
    {
        send_a_character(*string_of_characters++);
    }
}