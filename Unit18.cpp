//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "Unit18.h"
#include "MainWindow.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TFrame18 *Frame18;
//---------------------------------------------------------------------------
__fastcall TFrame18::TFrame18(TComponent* Owner, String baseurl, String resource, String titulo)
	: TFrame(Owner), baseurl(baseurl), resource(resource), titulo(titulo)
{
}
//---------------------------------------------------------------------------
