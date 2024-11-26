#include <stdio.h>
#include <stdint.h>
#include "lcd.h"
void default_background()
{
    //character box
    lcd_drawRect(5, 5, 238, 160, WHITE);
    lcd_drawRect(250, 5, 65, 160, WHITE);
    lcd_drawRect(5, 175, 310, 60, WHITE);

}