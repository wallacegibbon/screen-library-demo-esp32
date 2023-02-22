idf_component_register(
	REQUIRES driver SRCS
	"screen-library-mcu/painter.c"
	"screen-library-mcu/ssd1306.c"
	"screen-library-mcu/ssd1306_esp32_i2c.c"
	"screen-library-mcu/st7735.c"
	"screen-library-mcu/st7735_esp32_softspi.c"
	"screen-library-mcu/point_iterator.c"
	"screen-library-mcu/common.c"
	INCLUDE_DIRS "screen-library-mcu"
)
