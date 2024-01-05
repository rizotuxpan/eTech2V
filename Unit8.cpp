//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "Unit8.h"
#include "MainWindow.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Unit1"
#pragma resource "*.fmx"
TFrame8 *Frame8;
//---------------------------------------------------------------------------
__fastcall TFrame8::TFrame8(TComponent* Owner, String baseurl, String resource, String titulo)
	: TFrame1(Owner, baseurl, resource, titulo), baseurl(baseurl), resource(resource), titulo(titulo)
{
}
//---------------------------------------------------------------------------
void __fastcall TFrame8::ButtonCloseClick(TObject *Sender)
{
    Form1->EnableMenu(true);
	TThread::CreateAnonymousThread(
		[]()
		{
			Sleep(100);
			TThread::Queue(NULL,
				[]()
				{
					Frame8->DisposeOf();
				});
		}
	)->Start();
}
//---------------------------------------------------------------------------
