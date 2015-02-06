/*
 * watch.c
 *
 * Created: 1/13/2015 12:59:22 AM
 *  Author: cospan
 */ 
#include <stdint.h>
#include "watch.h"
#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned long rtc_second_count;

ISR (TIMER2_OVF_vect){
  //This second counter needs to be processed within 18 hours
  rtc_second_count++;
}

Watch::Watch(){
}

void Watch::init_watch_rtc(){
  rtc_second_count = 0;

  //Disable timer 2 interrupt
  TIMSK2 = 0;

  //Enable asynchronous mode, setup TOSC1/TOSC2 ports
  ASSR = (1 << AS2);

  //Set prescaller to 128
  TCCR2B = (1 << CS22);
  //TCCR2B = (1 << CS20);

  //Wait for register update
  while (ASSR & ((1 << TCN2UB) | (1 << TCR2BUB)));

  //bitSet(TIMSK2, TOIE2);
  TIMSK2 |= (1 << TOIE2);

}

void Watch::begin(){
  this->initialize_watch();
}

void Watch::initialize_watch(){
	uint8_t *pin;
	pin = (uint8_t*) 0x21;		//Port A
	*pin = 0x0F;
	pin = (uint8_t*) 0x24;		//Port B
	*pin = 0xF0;
	pin = (uint8_t*) 0x27;		//Port C
	*pin = 0x00;
	pin = (uint8_t*) 0x2A;		//Port D
	*pin = 0x00;
	pin = (uint8_t*) 0x2D;		//Port E
	*pin = 0xF8;
	pin = (uint8_t*) 0x30;		//Port F
	*pin = 0xFF;
	pin = (uint8_t*) 0x33;		//Port G
	*pin = 0x00;
	pin = (uint8_t*) 0x101;	  //Port H
	*pin = 0xEF;
	pin = (uint8_t*) 0x104;	  //Port J
	*pin = 0x00;
	pin = (uint8_t*) 0x107;	  //Port K
	*pin = 0x0F;
	pin = (uint8_t*) 0x10A;	  //Port L
	*pin = 0x39;

  //Set the pullup for the buttons
  //PORTE = 0x104;
  init_watch_rtc();

  configure_mode = true;

  hours = 0;
  minutes = 0;
  seconds = 0;
}

void Watch::RED_LED_ON(uint8_t value){
	switch (value){
		case 1:
			PORTK &= ~(0x04);
			break;
		case 2:
			PORTF &= ~(0x10);
			break;
		case 3:
			PORTF &= ~(0x02);
			break;
		case 4:
			PORTB &= ~(0x20);
			break;
		case 5:
			PORTE &= ~(0x08);
			break;
		case 6:
			PORTE &= ~(0x40);
			break;
		case 7:
			PORTH &= ~(0x08);
			break;
		case 8:
			PORTE &= ~(0x80);
			break;
		case 9:
			PORTF &= ~(0x80);
			break;
		case 10:
			PORTH &= ~(0x80);
			break;
		case 11:
			PORTL &= ~(0x08);
			break;
		case 12:
			PORTA &= ~(0x02);
			break;
		default:
			break;
	}
}

void Watch::RED_LED_OFF(uint8_t value){
	switch (value){
		case (1):
		PORTK |= (0x04);
		break;
		case (2):
		PORTF |= (0x10);
		break;
		case (3):
		PORTF |= (0x02);
		break;
		case (4):
		PORTB |= (0x20);
		break;
		case (5):
		PORTE |= (0x08);
		break;
		case (6):
		PORTE |= (0x40);
		break;
		case (7):
		PORTH |= (0x08);
		break;
		case (8):
		PORTE |= (0x80);
		break;
		case (9):
		PORTF |= (0x80) ;
		break;
		case (10):
		PORTH |= (0x80);
		break;
		case (11):
		PORTL |= (0x08);
		break;
		case (12):
		PORTA |= (0x02);
		break;
		default:
		break;
	}
}

void Watch::GREEN_LED_ON(uint8_t value){
	switch (value){
		case 1:
		PORTA &= ~(0x01);
		break;
		case 2:
		PORTK &= ~(0x02);
		break;
		case 3:
		PORTF &= ~(0x08);
		break;
		case 4:
		PORTF &= ~(0x01);
		break;
		case 5:
		PORTE &= ~(0x10);
		break;
		case 6:
		PORTH &= ~(0x04);
		break;
		case 7:
		PORTH &= ~(0x40);
		break;
		case 8:
		PORTH &= ~(0x02);
		break;
		case 9:
		PORTF &= ~(0x40);
		break;
		case 10:
		PORTL &= ~(0x01);
		break;
		case 11:
		PORTL &= ~(0x20);
		break;
		case 12:
		PORTA &= ~(0x08);
		break;
		default:
		break;
	}
}

void Watch::GREEN_LED_OFF(uint8_t value){
	switch (value){
		case 1:
		PORTA |= (0x01);
		break;
		case 2:
		PORTK |= (0x02);
		break;
		case 3:
		PORTF |= (0x08);
		break;
		case 4:
		PORTF |= (0x01);
		break;
		case 5:
		PORTE |= (0x10);
		break;
		case 6:
		PORTH |= (0x04);
		break;
		case 7:
		PORTH |= (0x40);
		break;
		case 8:
		PORTH |= (0x02);
		break;
		case 9:
		PORTF |= (0x40);
		break;
		case 10:
		PORTL |= (0x01);
		break;
		case 11:
		PORTL |= (0x20);
		break;
		case 12:
		PORTA |= (0x08);
		break;
		default:
		break;
	}
}

void Watch::BLUE_LED_ON(uint8_t value){
	switch (value){
		case 1:
		PORTK &= ~(0x08);
		break;
		case 2:
		PORTK &= ~(0x01);
		break;
		case 3:
		PORTF &= ~(0x04);
		break;
		case 4:
		PORTB &= ~(0x40);
		break;
		case 5:
		PORTB &= ~(0x10);
		break;
		case 6:
		PORTE &= ~(0x20);
		break;
		case 7:
		PORTH &= ~(0x20);
		break;
		case 8:
		PORTH &= ~(0x01);
		break;
		case 9:
		PORTF &= ~(0x20);
		break;
		case 10:
		PORTB &= ~(0x80);
		break;
		case 11:
		PORTL &= ~(0x10);
		break;
		case 12:
		PORTA &= ~(0x04);
		break;
		default:
		break;
	}
}

void Watch::BLUE_LED_OFF(uint8_t value){
	switch (value){
		case 1:
		PORTK |= (0x08);
		break;
		case 2:
		PORTK |= (0x01);
		break;
		case 3:
		PORTF |= (0x04);
		break;
		case 4:
		PORTB |= (0x40);
		break;
		case 5:
		PORTB |= (0x10);
		break;
		case 6:
		PORTE |= (0x20);
		break;
		case 7:
		PORTH |= (0x20);
		break;
		case 8:
		PORTH |= (0x01);
		break;
		case 9:
		PORTF |= (0x20);
		break;
		case 10:
		PORTB |= (0x80);
		break;
		case 11:
		PORTL |= (0x10);
		break;
		case 12:
		PORTA |= (0x04);
		break;
		default:
		break;
	}
}

void Watch::ALL_LEDS_OFF(){
  for (int i = 1; i < 13; i = i + 1){
    BLUE_LED_OFF(i);
    RED_LED_OFF(i);
    GREEN_LED_OFF(i);
  }  
}
void Watch::ALL_LEDS_ON(){
  for (int i = 1; i < 13; i = i + 1){
    BLUE_LED_ON(i);
    RED_LED_ON(i);
    GREEN_LED_ON(i);
  }  
}

//Buttons
bool Watch::is_button_pressed(uint8_t button){
	switch(button){
		case(0):
			if (PINJ & 0x40){
				return true;
			}
			break;
		case (1):
			if (PINJ & 0x20){
				return true;
			}
			break;
		default:
			return false;
	}
	return false;
}

//Time Functions
void Watch::set_time_callback(   uint8_t hours,
                          uint8_t minutes,
                          uint8_t seconds,
                          void * func){
}

void Watch::set_timer_callback ( uint8_t hours,
                          uint8_t minutes,
                          uint8_t seconds,
                          void * func){
}


void Watch::set_configure_mode(bool enable){
  configure_mode = enable;
}
bool Watch::is_configure_mode(){
  return configure_mode;
}
void Watch::configure_hour(){
}
void Watch::increment_hour(){
}
void Watch::configure_minute(){
}
void Watch::increment_minute(){
}



uint16_t Watch::debug_get_seconds(){
  return (uint16_t) rtc_second_count;
}

void Watch::get_time(uint8_t *hours, uint8_t *minutes, uint8_t *seconds){
  uint32_t local_rtc_seconds;

  local_rtc_seconds = rtc_second_count + this->seconds;
  rtc_second_count = 0;

  //Change all seconds into minutes
  while (local_rtc_seconds >= 60){
    //Calculate any minutes have transpired
    this->minutes++;
    if (this->minutes >= 60){
      this->minutes = 0;
      this->hours++;
    }
    local_rtc_seconds -= 60;
  }

  this->seconds = local_rtc_seconds;
  this->hours % 12;


  *hours   = this->hours;
  *minutes = this->minutes;
  *seconds = this->seconds;
}

