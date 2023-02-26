idf_component_register(
	REQUIRES driver SRCS
	"screen-library-mcu/common/src/painter.c"
	"screen-library-mcu/common/src/ssd1306.c"
	"screen-library-mcu/common/src/st7735.c"
	"screen-library-mcu/common/src/point_iterator.c"
	"screen-library-mcu/common/src/common.c"
	"screen-library-mcu/esp32/src/ssd1306_esp32_i2c.c"
	"screen-library-mcu/esp32/src/st7735_esp32_softspi.c"
	"screen-library-mcu/esp32/src/common.c"
	INCLUDE_DIRS
	"screen-library-mcu/common/inc"
	"screen-library-mcu/esp32/inc"
)
