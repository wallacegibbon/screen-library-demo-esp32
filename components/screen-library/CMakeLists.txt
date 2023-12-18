idf_component_register(
	REQUIRES driver SRCS
	"screen-library-mcu/sc_painter.c"
	"screen-library-mcu/sc_ssd1306.c"
	"screen-library-mcu/sc_st7735.c"
	"screen-library-mcu/sc_point_iterator.c"
	"screen-library-mcu/sc_common.c"
	"screen-library-mcu/esp32/sc_ssd1306_esp32_i2c.c"
	"screen-library-mcu/esp32/sc_st7735_esp32_softspi.c"
	"screen-library-mcu/esp32/sc_common_esp32.c"
	INCLUDE_DIRS
	"screen-library-mcu"
	"screen-library-mcu/esp32"
)
