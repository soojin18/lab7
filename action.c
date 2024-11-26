#include <stdio.h>
#include <stdint.h>
#include "action.h"
#include "status.h"
 
void feeding(uint8_t hunger)
{
    hunger -= 20;
}


void taking_shower(uint8_t dirty)
{
    dirty -= 40;
}

void playing(uint8_t boring)
{
    boring -= 50;
}

void sleep(uint8_t sleepy)
{
    sleepy -= 70;
}