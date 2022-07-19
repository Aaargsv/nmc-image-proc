#pragma data_section ".data_shared_src.bss"
	long input_text[32];
#pragma data_section ".data_shared_dst.bss"
	long output_text[32];
	
#include "nmc_support.h"

int main()
{
	unsigned char val;
	
	for (int i = 0; i < 20; i++) {
			val = get_byte(input_text, i);
			set_byte(output_text, i, ++val);
	}
	
	return 0; 
} 

