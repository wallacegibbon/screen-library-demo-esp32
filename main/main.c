#include "ssd1306_esp32_i2c.h"
#include "ssd1306.h"
#include "st7735_esp32_softspi.h"
#include "st7735.h"
#include "painter.h"
#include "common.h"
#include "color.h"
#include "driver/gpio.h"
#include "esp_log.h"

void fancy_display_1(struct Painter *painter) {
	static int current_cnt = 0, step = 1;
	struct Point p;
	int color, i;

	Point_initialize(&p, 64, 32);
	for (i = 0; i < 31; i++) {
		color = current_cnt == i ? BLACK_16bit : GREEN_16bit;
		Painter_draw_circle(painter, p, i, color);
	}
	Painter_flush(painter);

	if (current_cnt == 31)
		step = -1;
	else if (current_cnt == 0)
		step = 1;

	current_cnt += step;
}

void initialize_screen_1(
	struct SSD1306_Screen *screen1,
	struct SSD1306_ScreenAdaptorESP32I2C *adaptor1
) {
	printf("initializing SSD1306...\n");

	SSD1306_ScreenAdaptorESP32I2C_initialize(adaptor1, 0x3C, I2C_NUM_0);

	SSD1306_Screen_initialize(
		screen1,
		(struct SSD1306_ScreenAdaptorInterface *) adaptor1
	);

	printf("SSD1306 screen on...\n");
	SSD1306_Screen_display_on(screen1);

	//printf("setting SSD1306 screen to 32-row mode...\n");
	//SSD1306_Screen_fix_32row(&screen);
}

void initialize_screen_2(
	struct ST7735_Screen *screen2,
	struct ST7735_ScreenAdaptorESP32SoftSPI *adaptor2
) {
	/// start the BG LED of T-Dongle-S3
	ESP_ERROR_CHECK(gpio_set_direction(GPIO_NUM_38, GPIO_MODE_OUTPUT));
	ESP_ERROR_CHECK(gpio_set_level(GPIO_NUM_38, 0));

	printf("initializing ST7735...\n");

	ST7735_ScreenAdaptorESP32SoftSPI_initialize(
		adaptor2, GPIO_NUM_3, GPIO_NUM_5, GPIO_NUM_4, GPIO_NUM_1, GPIO_NUM_2
	);

	ST7735_Screen_initialize(
		screen2,
		(struct ST7735_ScreenAdaptorInterface *) adaptor2
	);
}

void app_main() {
	struct SSD1306_ScreenAdaptorESP32I2C adaptor1;
	struct SSD1306_Screen screen1;
	struct ST7735_ScreenAdaptorESP32SoftSPI adaptor2;
	struct ST7735_Screen screen2;
	struct Painter painter;
	struct Point p1;
	struct Point p2;

	initialize_screen_1(&screen1, &adaptor1);
	initialize_screen_2(&screen2, &adaptor2);

	painter.screen = (struct PainterInterface *) &screen1;
	//painter.screen = (struct PainterInterface *) &screen2;

	printf("clearing screen...\n");
	Painter_clear(&painter, BLACK_16bit);

	printf("drawing a rectangle...\n");
	Point_initialize(&p1, 64 - 50, 32 - 20);
	Point_initialize(&p2, 64 + 50, 32 + 20);
	Painter_draw_rectangle(&painter, p1, p2, BLUE_16bit);

	printf("drawing a circle on top left...\n");
	Point_initialize(&p1, 64 - 50, 32 - 20);
	Painter_draw_circle(&painter, p1, 5, RED_16bit);

	/*
	printf("drawing a line...\n");
	Point_initialize(&p1, 30, 10);
	Point_initialize(&p2, 20, 50);
	Painter_draw_line(&painter, p1, p2, WHITE_1bit);
	*/

	printf("flushing the screen...\n");
	Painter_flush(&painter);

	while (1) {
		fancy_display_1(&painter);
	}
}

