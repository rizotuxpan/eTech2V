//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "Unit12.h"
#include "MainWindow.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TFrame12 *Frame12;
//---------------------------------------------------------------------------
__fastcall TFrame12::TFrame12(TComponent* Owner, String baseurl, String resource, String titulo)
	: TFrame(Owner), baseurl(baseurl), resource(resource), titulo(titulo)
{
}
//---------------------------------------------------------------------------
