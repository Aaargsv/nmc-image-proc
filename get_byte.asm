/*unsigned char get_byte(unsigned char *data_ptr, int index)*/

global <_get_byte>: label;

begin ".text"
<_get_byte>

	ar5 = ar7 - 2;
	push ar0, gr0;
	ar0 = [--ar5]; //*data_ptr
	gr0 = [--ar5]; //index
	
						with gr7 = gr0 >> 2; // gr7 = index / 4
	gr7 = [ar0+=gr7]	with gr0 =<< 30; 
						with gr0 =>> 28;
	
	/* 
	[----0 byte----][----1 byte----][----2 byte----][----3 byte----] (32 bits)
	
	   if 0 byte then gr1 = 2   (0010)
	   if 1 byte then gr1 = 6   (0110)
	   if 2 byte then gr1 = 10	(1010)
	   if 3 byte then gr1 = 14  (1110)
	*/
	.align;
	
	delayed skip gr0;
		pop ar0, gr0;
		nul;
		nul;
	
	/* ----------------0 BYTE-------------------
	   [AAAAAAAA][XXXXXXXX][XXXXXXXX][XXXXXXXX] -->
	   [00000000][00000000][00000000][AAAAAAAA]
	*/
	
	
	delayed return with gr7 >>= 24;
		nul 		
		nul;
		nul;
	
	/* ----------------1 BYTE---------------------
	   [XXXXXXXX][AAAAAAAA][XXXXXXXX][XXXXXXXX] -->
	   [AAAAAAAA][XXXXXXXX][XXXXXXXX][00000000] -->
	   [00000000][00000000][00000000][AAAAAAAA] -->
	*/
	
	delayed return with gr7 <<= 8;
		nul		   with gr7 >>= 24;
		nul;
		nul;
		
	
	/* -----------------2 BYTE---------------------
	   [XXXXXXXX][XXXXXXXX][AAAAAAAA][XXXXXXXX] -->
	   [AAAAAAAA][XXXXXXXX][00000000][00000000] -->
	   [00000000][00000000][00000000][AAAAAAAA] -->
	*/
						
	delayed return  with gr7 <<= 16;
		nul 	    with gr7 >>= 24;
		nul;
		nul;
	
	
	/* -----------------3 BYTE---------------------
	   [XXXXXXXX][XXXXXXXX][XXXXXXXX][AAAAAAAA] -->
	   [AAAAAAAA][00000000][00000000][00000000] -->
	   [00000000][00000000][00000000][AAAAAAAA] -->
	*/
	
	delayed return  with gr7 <<= 24;
		nul			with gr7 >>= 24;	
		nul;			
		nul;
						
end ".text"