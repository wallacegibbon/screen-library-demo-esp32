idf_component_register(
	REQUIRES driver SRCS
	"simple_graphics/painter.c"
	"simple_graphics/ssd1306.c"
	"simple_graphics/ssd1306_esp32_i2c.c"
	"simple_graphics/st7735.c"
	"simple_graphics/st7735_esp32_softspi.c"
	"simple_graphics/point_iterator.c"
	"simple_graphics/common.c"
	INCLUDE_DIRS "simple_graphics"
)
