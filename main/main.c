#include "driver/gpio.h"
#include "esp_log.h"
#include "sc_color.h"
#include "sc_common.h"
#include "sc_painter.h"
#include "sc_ssd1306.h"
#include "sc_ssd1306_esp32_i2c.h"
#include "sc_st7735.h"
#include "sc_st7735_esp32_softspi.h"

void fancy_display(struct painter *painter) {
	static int current_cnt = 0, step = 1;
	struct point p;
	struct point size;
	uint32_t color;
	int i;

	painter_size(painter, &size);
	point_initialize(&p, size.x / 2, size.y / 2);
	for (i = 0; i < 31; i++) {
		color = (ABS(current_cnt - i) < 3) ? BLACK_24bit : CYAN_24bit;
		painter_draw_circle(painter, p, i, color);
	}
	painter_flush(painter);

	if (current_cnt == 31)
		step = -1;
	else if (current_cnt == 0)
		step = 1;

	current_cnt += step;
}

void initialize_screen_1(struct ssd1306_screen *screen, struct ssd1306_adaptor_esp32_i2c *adaptor) {
	printf("initializing SSD1306...\r\n");

	ssd1306_adaptor_esp32_i2c_initialize(adaptor, 0x3C, I2C_NUM_0);

	ssd1306_initialize(
		screen,
		(const struct ssd1306_adaptor_i **)adaptor);

	printf("SSD1306 screen on...\r\n");
	ssd1306_display_on(screen);

	// printf("setting SSD1306 screen to 32-row mode...\r\n");
	// SSD1306_Screen_fix_32row(&screen);
}

void initialize_screen_2(
	struct st7735_screen *screen2,
	struct st7735_adaptor_esp32_soft_spi *adaptor2) {

	/// start the BG LED of T-Dongle-S3
	ESP_ERROR_CHECK(gpio_set_direction(GPIO_NUM_38, GPIO_MODE_OUTPUT));
	ESP_ERROR_CHECK(gpio_set_level(GPIO_NUM_38, 0));

	printf("initializing ST7735...\r\n");

	st7735_adaptor_esp32_soft_spi_initialize(
		adaptor2, GPIO_NUM_3, GPIO_NUM_5, GPIO_NUM_4, GPIO_NUM_1, GPIO_NUM_2);

	st7735_initialize(
		screen2,
		(const struct st7735_adaptor_i **)adaptor2);
}

void graphic_play(struct painter *painter) {
	struct point p1, p2, size;
	struct text_painter text_painter;

	painter_clear(painter, BLACK_24bit);

	/// The default method do not flush, but overridden `clear` can do flush automatically.
	// painter_flush(painter);

	/// text drawing
	text_painter_initialize(&text_painter, painter);

	color_pair_initialize(&text_painter.color, RED_24bit, BLACK_24bit);
	point_initialize(&text_painter.pos, 0, 0);

	text_draw_string(&text_painter, "1.5 Programming!", 32);

	color_pair_initialize(&text_painter.color, GREEN_24bit, BLACK_24bit);
	point_initialize(&text_painter.pos, 0, 32);

	text_draw_string(&text_painter, "1.5 Programming!", 16);

	painter_size(painter, &size);

	point_initialize(&p1, size.x / 2 - 50, size.y / 2 - 20);
	point_initialize(&p2, size.x / 2 + 50, size.y / 2 + 20);
	painter_draw_rectangle(painter, p1, p2, YELLOW_24bit);

	point_initialize(&p1, size.x / 2 - 50, size.y / 2 - 20);
	painter_draw_circle(painter, p1, 5, MAGENTA_24bit);

	point_initialize(&p1, 10, size.y / 2 - 20);
	point_initialize(&p2, 10, size.y / 2 + 20);
	painter_draw_line(painter, p1, p2, WHITE_24bit);

	painter_flush(painter);
}

void app_main() {
	struct ssd1306_adaptor_esp32_i2c adaptor1;
	struct ssd1306_screen screen1;
	struct st7735_adaptor_esp32_soft_spi adaptor2;
	struct st7735_screen screen2;
	struct painter painter;

	// initialize_screen_1(&screen1, &adaptor1);
	initialize_screen_2(&screen2, &adaptor2);

	// ssd1306_screen_set_up_down_invert(&screen1);

	// painter.drawing_board = (struct drawing_i **) &screen1;
	painter.drawing_board = (const struct drawing_i **)&screen2;

	graphic_play(&painter);

	while (1)
		fancy_display(&painter);
}
