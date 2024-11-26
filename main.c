#include <stdio.h>
#include <stdint.h>

#include "hw.h"
#include "pin.h"
#include "lcd.h"
#include "status.h"
#include "screen.h"
#include "config.h"
//#include "nav.h"

#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

static const char *TAG = "lab07";

#define PER_MS ((uint32_t)(CONFIG_GAME_TIMER_PERIOD*1000))
#define TIME_OUT 500 // ms


TimerHandle_t update_timer;
volatile bool interrupt_flag;
uint32_t isr_triggered_count;
uint32_t isr_handled_count;

void update()
{
	interrupt_flag = true;
	isr_triggered_count++;
}

// Main application
void app_main(void)
{
	ESP_LOGI(TAG, "Starting");

	lcd_init();
	lcd_fillScreen(CONFIG_COLOR_BACKGROUND);
	//nav_init(PER_MS);
	happy_init();
	
	pin_reset(HW_BTN_A);
	pin_input(HW_BTN_A, true);
	pin_reset(HW_BTN_B);
	pin_input(HW_BTN_B, true);
	pin_reset(HW_BTN_MENU);
	pin_input(HW_BTN_MENU, true);
	pin_reset(HW_BTN_OPTION);
	pin_input(HW_BTN_OPTION, true);
	pin_reset(HW_BTN_SELECT);
	pin_input(HW_BTN_SELECT, true);
	pin_reset(HW_BTN_START);
	pin_input(HW_BTN_START, true);

	update_timer = xTimerCreate(
		"update_timer",        // Text name for the timer.
		pdMS_TO_TICKS(PER_MS), // The timer period in ticks.
		pdTRUE,                // Auto-reload the timer when it expires.
		NULL,                  // No need for a timer ID.
		update                 // Function called when timer expires.
	);
	if (update_timer == NULL) {
		ESP_LOGE(TAG, "Error creating update timer");
		return;
	}
	if (xTimerStart(update_timer, pdMS_TO_TICKS(TIME_OUT)) != pdPASS) {
		ESP_LOGE(TAG, "Error starting update timer");
		return;
	}

	// Main game loop
	uint64_t t1, t2, tmax = 0; // For hardware timer values
	//int8_t r, c; // For navigator location
	while (pin_get_level(HW_BTN_MENU)) // while MENU button not pressed
	{
		while (!interrupt_flag) ;
		t1 = esp_timer_get_time();
		interrupt_flag = false;
		isr_handled_count++;
		default_background();
		happy_tick();

		t2 = esp_timer_get_time() - t1;
		if (t2 > tmax) tmax = t2;
	}
	printf("Handled %lu of %lu interrupts\n", isr_handled_count, isr_triggered_count);
	printf("WCET us:%llu\n", tmax);

}

/*
	
// Main application
void app_main(void)
{
	ESP_LOGI(TAG, "Starting");
	lcd_init();
	// uint16_t i = 0;
	// const uint8_t pidx[] = {0, 1, 2, 1};
	// lcd_drawRGBBitmap(10, 10, pict, 150, 150);

	//default_background();


	lcd_fillRect(0, 0, 140, 20, GREEN);

}
*/
/*
void app_main(void)
{
	ESP_LOGI(TAG, "Starting");
	lcd_init();
	// uint16_t i = 0;
	// const uint8_t pidx[] = {0, 1, 2, 1};
	// lcd_drawRGBBitmap(10, 10, pict, 150, 150);
	//lcd_drawRGBBitmap(50, 50, tmgt, 150, 135);
	// lcd_fillRect(0, 0, 140, 20, GREEN);
	// lcd_fillRect(150, 0, 140, 20, YELLOW);
	// lcd_fillRect(0, 25, 140, 20, BLUE);
	//lcd_fillRect(5, 5, 238, 160, PURPLE);
	//lcd_fillRect(250, 5, 65, 160, BLUE);
	//lcd_fillRect(5, 175, 310, 70, YELLOW);
	default_background();
	
}
*/