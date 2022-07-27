#pragma data_section ".data_shared_src.bss"
	long input_text[100 * 100 / 8 + 17 / 8 + 1];
#pragma data_section ".data_shared_dst.bss"
	long output_text[100 * 100 / 8 + 17 / 8 + 1];
	
#include "nmc_support.h"
#include "ppm_control.h"
#include <string.h>

int main()
{
	ppm_header_t image1;
	ppm_header_t image2;
	
	int pos_raw1 = ppm_read_header(input_text, &image1);
	
	image2 = image1;
	
	int pos_raw2 = ppm_save_header(output_text, &image2, "");
	
	
	pixel_t val;
	
	unsigned char red;
	unsigned char green;
	unsigned char blue;
	
	for (int i = 0; i < image1.height; i++) {
		for (int j = 0; j < image1.width; j++) {
			
			red 	= get_byte(input_text, pos_raw1++);
			green 	= get_byte(input_text, pos_raw1++);
			blue 	= get_byte(input_text, pos_raw1++);

			set_byte(output_text, pos_raw2++, (unsigned char)128);
			set_byte(output_text, pos_raw2++, (unsigned char)128);
			set_byte(output_text, pos_raw2++, (unsigned char)128);
		}
	}
	
	
	
	return 0; 
} 

