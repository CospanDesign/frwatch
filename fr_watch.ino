
#include "watch.h"
#define MAX_RATE 50000
#define MIN_RATE 10
#define INC_VAL 500

#define MODE_TIME 0
#define MODE_CONFIG_HOUR 1
#define MODE_CONFIG_MINUTE 2
#define MODE_CONFIG_SECOND 3
#define MODE_CRAZY 4
#define MODE_ALSO_CRAZY 5

uint8_t mode = MODE_CONFIG_HOUR;
//uint8_t mode = MODE_CRAZY;

uint16_t rate = 100;
bool direction = true;


Watch watch;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println ("Start");
  //init_rtc();
  
  watch.begin();
  for (int i = 1; i < 13; i = i + 1){
    watch.BLUE_LED_OFF(i);
    watch.RED_LED_OFF(i);
    watch.GREEN_LED_OFF(i);
  }  
}


void update_clock(){
  uint8_t hours;
  uint8_t minutes;
  uint8_t seconds;

  watch.get_time(&hours, &minutes, &seconds);

  if (seconds < 5){
    seconds = 12;
  }
  else {
    seconds = seconds / 5;
  }

  if (minutes < 5){
    minutes = 12;
  }
  else {
    minutes = minutes / 5;
  }
  if (hours == 0){
    hours = 12;
  }

  Serial.print("Time: ");
  Serial.print(hours);
  Serial.print(":");
  Serial.print(minutes);
  Serial.print(":");
  Serial.println(seconds);
  
  watch.ALL_LEDS_OFF();
  //Red is hours
  watch.RED_LED_ON(hours);
  //Green is minutes
  watch.GREEN_LED_ON(minutes);
  //Blue is seconds
  watch.BLUE_LED_ON(seconds);
}


void set_time(){
}

void crazy_mode(){
  for (int i = 1; i < 13; i = i + 1){
    watch.RED_LED_ON(i);
    watch.GREEN_LED_ON(((i + 6) % 12) + 1);
    watch.BLUE_LED_ON(13 - i);
    
    
    delayMicroseconds(rate);	
    
    
    watch.RED_LED_OFF(i);
    watch.GREEN_LED_OFF(((i + 6) % 12) + 1);
    watch.BLUE_LED_OFF(13 - i);
    delayMicroseconds(rate);	
  }
  
  
  if (direction){
    if (rate >= MAX_RATE){
      direction = false;
    }	
    else {
      rate += INC_VAL;
    }
  }
  else {
    if (rate <= MIN_RATE){
      direction = true;
    }
    else{
      if ((INC_VAL - rate) < INC_VAL){
        rate = MIN_RATE;
      }
      else {
        rate -= INC_VAL;
      }
    }
  }	
}

void loop() {
  // put your main code here, to run repeatedly: 
  if (watch.is_button_pressed(0)){
    Serial.println("Button 0 is pressed");
    for (int i = 1; i < 13; i = i + 1){
      watch.RED_LED_ON(i);
      watch.GREEN_LED_OFF(i);
      watch.BLUE_LED_ON(i);
      rate = (uint8_t) MIN_RATE;
      
    }
  }
  else if (watch.is_button_pressed(1)){
    Serial.println("Button 1 is pressed");
    for (int i = 1; i < 13; i = i + 1){
      watch.RED_LED_OFF(i);
      watch.GREEN_LED_ON(i);
      watch.BLUE_LED_OFF(i);
      rate = MAX_RATE;
    }
  }		
  /*
  crazy_mode();
  */
 
  delay(500);
  Serial.print("Seconds: ");
  Serial.println(watch.debug_get_seconds());
  update_clock();

}


