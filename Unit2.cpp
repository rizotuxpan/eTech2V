//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Unit1"
#pragma resource "*.fmx"
TFrame2 *Frame2;
//---------------------------------------------------------------------------
__fastcall TFrame2::TFrame2(TComponent* Owner, String baseurl, String resource, String titulo)
	: TFrame1(Owner, baseurl, resource, titulo), baseurl(baseurl), resource(resource), titulo(titulo) {
    PopulateStringGrid();
	LabelTitulo->Text = titulo;
}
//---------------------------------------------------------------------------
