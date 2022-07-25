#include "ppm_control.h"
#include "nmc_support.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <limits.h>

int ppm_read_header (void *data_ptr, ppm_header_t *header_info)
{
	int pos = 0;
	unsigned char format[3];
	
	
	/****read format (magic number)***/
	for (int i = 0; i < 3; i++)
		format[i] = get_byte(data_ptr, pos++);
	
	format[2] = '\0';
	
	if ( strcmp("P6", (char const *)format) == 0 )
		strcpy(header_info->format, "P6");
	else if ( strcmp("P5", (char const *)format) == 0 )
		strcpy(header_info->format, "P5");
	else
		return ERR_FORMAT;
	


	unsigned char symbol;
	symbol = get_byte(data_ptr, pos++);
	
	/****read comment***/
	while (symbol == '#') {
		while (symbol != '\n') {
			symbol = get_byte(data_ptr, pos++);
			if (pos > 1024)
				return ERR_COMMENT;
		}
	}
	
	char buf[64];
	
	/****read width****/
	int i;
	for (i = 0; ; i++) {
		if (i > 32)
			return ERR_WIDTH;
		buf[i] = get_byte(data_ptr, pos++);
		
		if (buf[i] == ' ')
			break;
	}
	buf[i] = '\0';
	
	long image_size_param;
	char *end_ptr;
	
	image_size_param = strtol((char const *)buf, &end_ptr, 10);
	
	if (buf == end_ptr || *end_ptr != '\0')
		return ERR_WIDTH;
	
	if (errno == ERANGE)
		return ERR_WIDTH;
	
	if (image_size_param > INT_MAX)
		return ERR_WIDTH;
	
	header_info->width = (int)image_size_param;
	
	/****read height****/
	
	for (i = 0; ; i++) {
		if (i > 32)
			return ERR_HEIGHT;
		buf[i] = get_byte(data_ptr, pos++);
		if (buf[i] == '\n')
			break;
		
	}
	buf[i] = '\0';
	
	image_size_param = strtol((char const *)buf, &end_ptr, 10);
	
	if (buf == end_ptr || *end_ptr != '\0')
		return ERR_HEIGHT;
	
	if (errno == ERANGE)
		return ERR_HEIGHT;
	
	if (image_size_param > INT_MAX)
		return ERR_HEIGHT;
	
	header_info->height = (int)image_size_param;
	
	/****depth****/
	

	for (i = 0; ; i++) {
		if (i > 32)
			return 10;
		buf[i] = get_byte(data_ptr, pos++);
		if (buf[i] == '\n')
			break;
	
	}
	buf[i] = '\0';
	
	image_size_param = strtol((char const *)buf, &end_ptr, 10);
	
	if (buf == end_ptr || *end_ptr != '\0')
		return ERR_DEPTH;
	
	if (errno == ERANGE)
		return ERR_DEPTH;
	
	if (image_size_param > INT_MAX)
		return ERR_DEPTH;
	
	header_info->depth = (int)image_size_param;
	pos++;
	
	header_info->start_raw = pos;
	
	return pos;
	
}

int ppm_save_header(void *data_ptr, ppm_header_t *header_info, const char *comment)
{
	int pos = 0;
	
	/***write format (magic number)***/
	set_byte(data_ptr, pos++, header_info->format[0]);
	set_byte(data_ptr, pos++, header_info->format[1]);
	set_byte(data_ptr, pos++, '\n');
	

	/***write comment***/
	set_byte(data_ptr, pos++, '#');
	
	for (int i = 0; comment[i] != '\0'; i++) {
		if (i > 32)
			break;
		set_byte(data_ptr, pos++, comment[i]);
	}
	
	set_byte(data_ptr, pos++, '\n');
	

	
	char buf[11]; //buffer for width, height and depth
	
	/***write width***/
	sprintf(buf, "%d", header_info->width);
	int len = strlen(buf);
	

	for (int i = 0; i < len; i++) 
		set_byte(data_ptr, pos++, buf[i]);
	
	set_byte(data_ptr, pos++, ' ');
	
	
	/***write height***/
	sprintf(buf, "%d", header_info->height);
	len = strlen(buf);
	

	for (int i = 0; i < len; i++) 
		set_byte(data_ptr, pos++, buf[i]);
	
	set_byte(data_ptr, pos++, '\n');
	
	/***write depth***/
	sprintf(buf, "%d", header_info->depth);
	len = strlen(buf);

	for (int i = 0; i < len; i++) 
		set_byte(data_ptr, pos++, buf[i]);
	
	set_byte(data_ptr, pos++, '\n');
	
	return pos;
}



