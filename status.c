#include <stdio.h>
#include <stdint.h>
#include "status.h"
#include "lcd.h"

enum{
    STATUS_HAPPY,
    STATUS_UNHAPPY
};
uint16_t hunger;
uint16_t dirty;
uint16_t sleepy;
uint16_t boring;
uint16_t happiness;

void happy_init()
{
    happiness = STATUS_HAPPY;
    hunger = 0;
    dirty = 0;
    sleepy = 0;
    boring = 0;
}

void happy_tick(void)
{
    //transition
    switch(happiness){
        case STATUS_HAPPY:
            if(hunger >= 300 || dirty >= 300 || sleepy >= 300 || boring >= 300)
            {
                printf("happiness transition tick\n");
                printf("h:%d d:%d s:%d b:%d\n",hunger, dirty, sleepy, boring);
                printf("current status: %d\n", happiness);
                happiness = STATUS_UNHAPPY;
            }
        break;
        case STATUS_UNHAPPY:
            if(hunger <= 300 && dirty <= 300 && sleepy <= 300 && boring <= 300)
            {
                printf("happiness transition tick\n");
                printf("h:%d d:%d s:%d b:%d\n",hunger, dirty, sleepy, boring);
                printf("current status: %d\n", happiness);
                happiness = STATUS_HAPPY;
            }
        break;
    }
    //action
    switch(happiness){
        case STATUS_HAPPY:
        lcd_drawRect(25,25,8,8,PURPLE);
        decrease_status();
        printf("happiness action tick\n");
        printf("h:%d d:%d s:%d b:%d\n",hunger, dirty, sleepy, boring);
        printf("current status: %d\n", happiness);
        break;
        case STATUS_UNHAPPY:
        lcd_drawRect(25,25,8,8,RED);
        decrease_status();
        printf("happiness action tick\n");
        printf("h:%d d:%d s:%d b:%d\n",hunger, dirty, sleepy, boring);
        printf("current status: %d\n", happiness);
        break;
    }

}

void decrease_status()
{
    hunger += 4;
    dirty += 3;
    sleepy += 2;
    boring += 1;
}