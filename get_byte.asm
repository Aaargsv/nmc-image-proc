/*unsigned char get_byte(unsigned char *data_ptr, int index)*/

global <_get_byte>: label;

begin ".text"
<_get_byte>

	ar5 = ar7 - 2;
	
	push ar0, gr0;
	
	ar0 = [--ar5];
	gr0 = [--ar5];
	
	
						with gr7 = gr0 >> 2;
	gr7 = [ar0+=gr7]	with gr0 =<< 30;
						with
	

	skip
	
	gr0 = FF000000h;
	delayed return;
		pop ar0, gr0 with gr7 = gr7 and gr0;
					 with gr7 >>= 24;
		nul;
	
	
	gr0 = 00FF0000h;
	delayed return;
		pop ar0, gr0 with gr7 = gr7 and gr0;
					 with gr7 >>= 16;
		nul;
	
							
	gr0 = 0000FF00h;
	delayed return;
		pop ar0, gr0 with gr7 = gr7 and gr0;
					 with gr7 >>= 8;
		nul;
	
	gr0 = 000000FFh;
	delayed return;
		pop ar0, gr0 with gr7 = gr7 and gr0;
		nul;
		nul;
						
end ".text"