idf_component_register(
	REQUIRES driver SRCS
	"screen-library-mcu/screen_painter.c"
	"screen-library-mcu/ssd1306.c"
	"screen-library-mcu/st7735.c"
	"screen-library-mcu/point_iterator.c"
	"screen-library-mcu/screen_common.c"
	"screen-library-mcu/esp32/ssd1306_esp32_i2c.c"
	"screen-library-mcu/esp32/st7735_esp32_softspi.c"
	"screen-library-mcu/esp32/screen_common.c"
	INCLUDE_DIRS
	"screen-library-mcu"
	"screen-library-mcu/esp32"
)
