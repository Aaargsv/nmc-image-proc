/*void set_byte(unsigned char *data_ptr, int index, unsigned char set_val)*/
global _set_byte: label;

begin ".text"
<_set_byte>

	ar5 = ar7 - 2;
	
	push ar0, gr0;
	push ar1, gr1;
	
	ar0 = [--ar5]; //ar0 = data_ptr
	gr7 = [--ar5]; //gr7 = index
	gr0 = [--ar5] 		with gr1 = gr7 >> 2; //gr0 = set_val with gr1 = index / 4
	
	gr7 = [ar0+=gr1] 	with gr1 = gr7 << 30; //gr7 = required 32_byte_array
	ar5 = ar0			with gr1 =>> 27;
						with gr1++;
						with gr1++;
	.align
	skip gr1;
	
	/* 
	[----0 byte----][----1 byte----][----2 byte----][----3 byte----] (32 bits)
	
	   if 0 byte then gr1 = 2   (00010)
	   if 1 byte then gr1 = 10  (01010)
	   if 2 byte then gr1 = 18	(10010)
	   if 3 byte then gr1 = 26  (11010)
	*/
	

	//if 0 byte
	gr1 = 00FFFFFFh with gr0 <<= 24; //gr1 - mask
	pop ar1, gr1 		with gr7 = gr1 and gr7;
	pop ar0, gr0		with gr7 = gr7 or gr0;
	delayed return;
		[ar5] = gr7;
	
	//if 1 byte
	gr1 = FF00FFFFh with gr0 <<= 16;
	pop ar1, gr1 		with gr7 = gr1 and gr7;
	pop ar0, gr0		with gr7 = gr7 or gr0;
	delayed return;
		[ar5] = gr7;
	
	//if 2 byte
	gr1 = FFFF00FFh with gr0 <<= 8;
	pop ar1, gr1 		with gr7 = gr1 and gr7;
	pop ar0, gr0		with gr7 = gr7 or gr0;
	delayed return;
		[ar5] = gr7;
	
	//if 3 byte
	gr1 = FFFFFF00h;
	pop ar1, gr1 		with gr7 = gr1 and gr7;
	pop ar0, gr0		with gr7 = gr7 or gr0;
	delayed return;
		[ar5] = gr7;


end ".text"