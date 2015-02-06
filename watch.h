/*
 * watch.h
 *
 * Created: 1/13/2015 12:58:07 AM
 *  Author: cospan
 */ 


#ifndef WATCH_H_
#define WATCH_H_

#include "stdint.h"



class Watch{
  private:

    void init_watch_rtc(void);

    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;

    bool configure_mode;

  public:

    Watch();
    void begin();

    void initialize_watch();

    void RED_LED_ON(uint8_t value);
    void RED_LED_OFF(uint8_t value);

    void GREEN_LED_ON(uint8_t value);
    void GREEN_LED_OFF(uint8_t value);

    void BLUE_LED_ON(uint8_t value);
    void BLUE_LED_OFF(uint8_t value);

    void ALL_LEDS_OFF();
    void ALL_LEDS_ON();

    //Buttons
    bool is_button_pressed(uint8_t button);

    //Time Functions
    void set_configure_mode(bool enable);
    bool is_configure_mode();

    void configure_hour();
    void increment_hour();
    void configure_minute();
    void increment_minute();

    void set_time_callback(   uint8_t hours,
                              uint8_t minutes,
                              uint8_t seconds,
                              void * func);

    void set_timer_callback ( uint8_t hours,
                              uint8_t minutes,
                              uint8_t seconds,
                              void * func);


    void get_time(uint8_t *hours, uint8_t *minutes, uint8_t *seconds);
    uint16_t debug_get_seconds();
};
#endif /* WATCH_H_ */
