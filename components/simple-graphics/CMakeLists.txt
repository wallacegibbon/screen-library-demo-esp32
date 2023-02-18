idf_component_register(
	REQUIRES driver SRCS "painter.c" "ssd1306.c" "st7735.c" "point_iterator.c" "common.c"
	INCLUDE_DIRS "."
)
