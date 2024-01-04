//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "Unit7.h"
#include "MainWindow.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Unit1"
#pragma resource "*.fmx"
TFrame7 *Frame7;
//---------------------------------------------------------------------------
__fastcall TFrame7::TFrame7(TComponent* Owner, String baseurl, String resource, String titulo)
	: TFrame1(Owner, baseurl, resource, titulo), baseurl(baseurl), resource(resource), titulo(titulo)
{
}
//---------------------------------------------------------------------------
void __fastcall TFrame7::ButtonCloseClick(TObject *Sender)
{
    Form1->EnableMenu(true);
	TThread::CreateAnonymousThread(
		[]()
		{
			Sleep(100);
			TThread::Queue(NULL,
				[]()
				{
					Frame7->DisposeOf();
				});
		}
	)->Start();
}
//---------------------------------------------------------------------------
