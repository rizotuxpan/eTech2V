//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TFrame1 *Frame1;
//---------------------------------------------------------------------------
__fastcall TFrame1::TFrame1(TComponent* Owner)
	: TFrame(Owner)
{
}
//---------------------------------------------------------------------------


void __fastcall TFrame1::Panel2Resized(TObject *Sender)
{
	if (!resizing)  // Evitar bucle infinito
	{
		resizing = true;
		try
		{
			if (Panel2->Width < 420) {
				Panel2->Width = 420;
			}
		}
		__finally
		{
			resizing = false;
		}
	}
}
//---------------------------------------------------------------------------
