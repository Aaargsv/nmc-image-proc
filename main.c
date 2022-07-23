#pragma data_section ".data_shared_src.bss"
	long input_text[100 * 100 / 8 + 15 / 8 + 1];
#pragma data_section ".data_shared_dst.bss"
	long output_text[100 * 100 / 8 + 15 / 8 + 1];
	
#include "nmc_support.h"
#include "ppm_control.h"
#include <string.h>
int main()
{

	
	ppm_header_t image1;
	
	strncpy(image1.format, "P6", 3);
	
	image1.width = 100;
	image1.height = 100;
	image1.depth = 255;
	
	int pos_raw = ppm_save_header(output_text, &image1, "");
	
	/*for (int i = 0; i < image1->height; i++) {
		for (int j = 0; j < image1->width; j++) {
			
			if (i < 33) {
				set_byte(output_text, pos_raw++, (unsigned char) 255);
				set_byte(output_text, pos_raw++, (unsigned char) 0);
				set_byte(output_text, pos_raw++, (unsigned char) 0);
			}
			
			if (i < 66) {
				set_byte(output_text, pos_raw++, (unsigned char) 0);
				set_byte(output_text, pos_raw++, (unsigned char) 0);
				set_byte(output_text, pos_raw++, (unsigned char) 255);
			}
			
			if (i < 100) {
				set_byte(output_text, pos_raw++, (unsigned char) 0);
				set_byte(output_text, pos_raw++, (unsigned char) 255);
				set_byte(output_text, pos_raw++, (unsigned char) 0);
			}	
		}
	}*/
	
	return 0; 
} 

