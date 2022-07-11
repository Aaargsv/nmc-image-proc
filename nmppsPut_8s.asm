//------------------------------------------------------------------------
//
//  $Workfile:: CharShortAccess.as $
//
//  Векторно-матричная библиотека
//
//  Copyright (c) RC Module Inc.
//
//  $Revision: 1.1 $      $Date: 2004/11/22 13:50:13 $
//
//! \if file_doc
//!
//! \file   CharShortAccess.asm
//! \author Сергей Мушкаев
//! \brief  Функции доступа для векторов.
//!
//! \endif
//!
//------------------------------------------------------------------------

//#include "vConvert.h"

begin ".text_nmplv"
/////////////////////////////////////////////////////////////////////////////////

//! \fn void nmppsPut_8s(int number, int skip) 
//!
//! \perfinclude _nmppsPut_8s.html


global _nmppsPut_8s:label;
<_nmppsPut_8s> 


	ar5 = ar7 - 2;
	
	push ar1,gr1;
	push ar6,gr6;
	push ar3,gr3;
	
	gr3 = 0FFFF0000h;
	gr1 = [--ar5]; //my number
	gr6 = [--ar5];						// skip parameter

					 with gr6++;
					 with gr6++;

	.align;
	delayed skip gr6;
		nul;	//with gr1<<=24; 
		nul;	//with gr1>>=24; 
		with gr3>>=1;
		

	//////////////////////////////////
	gr7 = gr1 >> 1;
	nul;
	pop ar6,gr6;
	pop ar1,gr1;
	delayed return;
		nul;
		nul;
		nul;
	
	//////////////////////////////////
	gr7 = gr1 >> 2;
	nul;
	pop ar6,gr6;
	pop ar1,gr1;
	delayed return;
		nul;
		nul;
		nul;
		
	//////////////////////////////////
	gr7 = gr1 >> 3;
	nul;
	pop ar6,gr6;
	pop ar1,gr1;
	delayed return;
		nul;
		nul;
		nul;
	
	//////////////////////////////////
	gr7 = gr1 >> 4;
	nul;
	pop ar6,gr6;
	pop ar1,gr1;
	delayed return;
		nul;
		nul;
		nul;


end ".text_nmplv";
