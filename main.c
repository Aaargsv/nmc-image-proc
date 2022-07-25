#pragma data_section ".data_shared_src.bss"
	long input_text[100 * 100 / 8 + 15 / 8 + 1];
#pragma data_section ".data_shared_dst.bss"
	long output_text[100 * 100 / 8 + 15 / 8 + 1];
	
#include "nmc_support.h"
#include "ppm_control.h"
#include <string.h>

int main()
{
	//ppm_header_t image1;
	ppm_header_t image2;
	
	//int pos_raw1 = ppm_read_header(input_text, &image1);
	
	strcpy(image2.format, "P6");
	image2.width = 100;
	image2.height = 100;
	image2.depth = 255;
	
	int pos_raw2 = ppm_save_header(output_text, &image2, "");
	
	
	unsigned char val;
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			//val = get_byte(input_text, pos_raw1++);
			set_byte(output_text, pos_raw2++, (unsigned char)128);
		}
	}
	
	
	
	return 0; 
} 

