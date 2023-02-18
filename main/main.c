#include "ssd1306.h"
#include "painter.h"
#include "color.h"
#include "driver/i2c.h"
#include "driver/spi_master.h"
#include "esp_log.h"
#include "freertos/task.h"

void i2c_device_init() {
	i2c_config_t config;

	config.mode = I2C_MODE_MASTER;
	config.sda_io_num = GPIO_NUM_41;
	config.scl_io_num = GPIO_NUM_40;
	config.sda_pullup_en = GPIO_PULLUP_ENABLE;
	config.scl_pullup_en = GPIO_PULLUP_ENABLE;
	config.master.clk_speed = 400000;
	config.clk_flags = 0;

	ESP_ERROR_CHECK(i2c_param_config(I2C_NUM_0, &config));
	ESP_ERROR_CHECK(i2c_driver_install(
		I2C_NUM_0, I2C_MODE_MASTER, 0, 0, 0
	));
}

void spi_device_init(spi_device_handle_t *dev) {
	spi_bus_config_t bus_config;
	spi_device_interface_config_t interface_config;

	bus_config.mosi_io_num = GPIO_NUM_3;
	bus_config.miso_io_num = GPIO_NUM_3;
	bus_config.sclk_io_num = GPIO_NUM_5;
	bus_config.quadwp_io_num = -1;
	bus_config.quadhd_io_num = -1;
	bus_config.max_transfer_sz = 160 * 80 * 2 + 8;
	bus_config.flags = 0;
	bus_config.intr_flags = 0;
	ESP_ERROR_CHECK(spi_bus_initialize(
		SPI2_HOST, &bus_config, SPI_DMA_DISABLED
	));

	interface_config.address_bits = 0;
	interface_config.command_bits = 0;
	interface_config.mode = 0;
	interface_config.duty_cycle_pos = 0;
	interface_config.cs_ena_pretrans = 0;
	interface_config.cs_ena_posttrans = 0;
	interface_config.input_delay_ns = 0;
	interface_config.clock_speed_hz = 0;
	interface_config.spics_io_num = GPIO_NUM_4;
	interface_config.flags = SPI_DEVICE_NO_DUMMY;
	interface_config.queue_size = 1;
	interface_config.pre_cb = 0;
	interface_config.post_cb = 0;

	ESP_ERROR_CHECK(spi_bus_add_device(SPI2_HOST, &interface_config, dev));
}

void fancy_display_1(struct Painter *painter) {
	static int current_cnt = 0;
	static int step = 1;
	struct Point p;
	int color;
	int i;

	Point_initialize(&p, 64, 32);
	for (i = 0; i < 31; i++) {
		color = current_cnt == i ? BLACK_1bit : WHITE_1bit;
		Painter_draw_circle(painter, p, i, color);
	}
	Painter_flush(painter);

	if (current_cnt == 31)
		step = -1;
	else if (current_cnt == 0)
		step = 1;

	current_cnt += step;
}

void fancy_display_2(struct Painter *painter) {
	static unsigned short current_color = 0;
	static int color = 0;
	struct Point p;
	int i;

	Point_initialize(&p, 64, 32);
	for (i = 0; i < 31; i++) {
		current_color += 20;
		Painter_draw_circle(painter, p, i, color);
		color = !color;
		Painter_flush(painter);
	}

	vTaskDelay(10 / portTICK_PERIOD_MS);
}

void app_main() {
	struct SSD1306_Screen screen;
	struct Painter painter;
	struct Point p1;
	struct Point p2;

	printf("initializing i2c device...\n");
	i2c_device_init();

	SSD1306_Screen_initialize(&screen, 0x3C, I2C_NUM_0);
	SSD1306_Screen_describe(&screen);

	printf("SSD1306 screen on...\n");
	SSD1306_Screen_display_on(&screen);

	printf("setting SSD1306 screen to 32-row mode...\n");
	//SSD1306_Screen_fix_32row(&screen);

	painter.screen = &screen;

	printf("clearing screen (from painter)...\n");
	Point_initialize(&p1, 0, 0);
	Point_initialize(&p2, 128, 64);
	Painter_clear(&painter, p1, p2, BLACK_1bit);

	printf("drawing a rectangle...\n");
	Point_initialize(&p1, 64 - 50, 32 - 20);
	Point_initialize(&p2, 64 + 50, 32 + 20);
	Painter_draw_rectangle(&painter, p1, p2, WHITE_1bit);

	printf("drawing a circle on top left...\n");
	Point_initialize(&p1, 64 - 50, 32 - 20);
	Painter_draw_circle(&painter, p1, 5, WHITE_1bit);

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
