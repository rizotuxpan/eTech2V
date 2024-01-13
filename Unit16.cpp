//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "Unit16.h"
#include "MainWindow.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Unit1"
#pragma resource "*.fmx"
TFrame16 *Frame16;
//---------------------------------------------------------------------------
__fastcall TFrame16::TFrame16(TComponent* Owner, String baseurl, String resource, String titulo)
	: TFrame1(Owner, baseurl, resource, titulo), baseurl(baseurl), resource(resource), titulo(titulo)
{
}
//---------------------------------------------------------------------------
void __fastcall TFrame16::ButtonCloseClick(TObject *Sender)
{
    // Activa el menu
	Form1->EnableMenu(true);
	// Crear un hilo anónimo para cerrar la aplicación
	TThread::CreateAnonymousThread(
		[]()
		{
			// Dormir brevemente para permitir que la operación de clic del botón se complete
			Sleep(100);

			// Cierra el Frame de manera segura evitando problemas de concurrencia
			TThread::Queue(NULL,
				[]()
				{
					Frame16->DisposeOf();
				});
		}
	)->Start();
}
//---------------------------------------------------------------------------
