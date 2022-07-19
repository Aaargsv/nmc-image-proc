#include "ppm_contol.h"
#include "nmc_support.h"
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int ppm_read_header (void *data_ptr, ppm_header_t *header_info)
{
	int pos = 0;
	unsigned char format[5];
	
	
	/****read format (magic number)***/
	for (int i = 0; i < 4; i++, pos++)
		format[i] = get_byte(data_ptr, pos);
	
	format[5] = '\0';
	
	
	
	if ( strcmp("P6\n", format) == 0 )
		strcpy(header_info->format, "P6")
	else if ( strcmp("P5\n", format) == 0 )
		strcpy(header_info->format, "P5")
	else
		return 0;
	


	unsigned char symbol;
	symbol = get_byte(data_ptr, ++pos);
	
	/****read comment***/
	while (symbol == '#') {
		while (symbol != '\n') {
			symbol = get_byte(data_ptr, ++pos);
			if (pos > 1024)
				return 0;
		}
	}
	
	unsigned char buf[64];
	
	/****read width****/
	int i;
	for (i = 0; buf[i] != ' '; i++, pos++) {
		if (i > 32)
			return 0;
		buf[i] = get_byte(data_ptr, pos);
	}
	buf[i] = '\0';
	
	long image_size_param;
	char *end_ptr;
	
	image_size_param = strtol(buf, &end_ptr, 10);
	
	if (buf == end_ptr || *end_ptr != '\0')
		return 0;
	
	if (errno == ERANGE)
		return 0;
	
	if (image_size_param > INT_MAX)
		return 0;
	
	header_info->width = (int)image_size_param;
	
	/****read height****/
	pos++;
	for (i = 0; buf[i] != '\n'; i++, pos++) {
		if (i > 32)
			return 0;
		buf[i] = get_byte(data_ptr, pos);
	}
	buf[i] = '\0';
	
	image_size_param = strtol(buf, &end_ptr, 10);
	
	if (buf == end_ptr || *end_ptr != '\0')
		return 0;
	
	if (errno == ERANGE)
		return 0;
	
	if (image_size_param > INT_MAX)
		return 0;
	
	header_info->height = (int)image_size_param;
	
	/****depth****/
	
	pos++;
	for (i = 0; buf[i] != '\n'; i++, pos++) {
		if (i > 32)
			return 0;
		buf[i] = get_byte(data_ptr, pos);
	}
	buf[i] = '\0';
	
	image_size_param = strtol(buf, &end_ptr, 10);
	
	if (buf == end_ptr || *end_ptr != '\0')
		return 0;
	
	if (errno == ERANGE)
		return 0;
	
	if (image_size_param > INT_MAX)
		return 0;
	
	header_info->depth = (int)image_size_param;
	
	pos++;
	
	ppm_header->start_raw = pos;
	
	return pos;
	
}