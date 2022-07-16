#pragma data_section ".data_shared_src.bss"
	long input_text[32];
#pragma data_section ".data_shared_dst.bss"
	long output_text[32];
	
	
extern unsigned char get_byte(unsigned char *data_ptr, int index)
extern void set_byte(unsigned char *data_ptr, int index, unsigned char set_val)


int main()
{
	unsigned char val;
	
	for (int i = 0; i < 20; i++) {
			val = get_byte(input_text, i);
			set_byte(output_text, i, ++val);
	}
	
	return 0; 
} 

