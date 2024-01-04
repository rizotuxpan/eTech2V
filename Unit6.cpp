//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "Unit6.h"
#include "MainWindow.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Unit1"
#pragma resource "*.fmx"
TFrame6 *Frame6;
//---------------------------------------------------------------------------
__fastcall TFrame6::TFrame6(TComponent* Owner, String baseurl, String resource, String titulo)
	: TFrame1(Owner, baseurl, resource, titulo), baseurl(baseurl), resource(resource), titulo(titulo)
{
}
//---------------------------------------------------------------------------
void __fastcall TFrame6::ButtonCloseClick(TObject *Sender)
{
    Form1->EnableMenu(true);
	TThread::CreateAnonymousThread(
		[]()
		{
			Sleep(100);
			TThread::Queue(NULL,
				[]()
				{
					Frame6->DisposeOf();
				});
		}
	)->Start();
}
//---------------------------------------------------------------------------
