//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "Unit19.h"
#include "MainWindow.h"
#include <IdURI.hpp>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "FMX.TMSFNCCustomControl"
#pragma link "FMX.TMSFNCGoogleMaps"
#pragma link "FMX.TMSFNCGraphics"
#pragma link "FMX.TMSFNCGraphicsTypes"
#pragma link "FMX.TMSFNCMaps"
#pragma link "FMX.TMSFNCTypes"
#pragma link "FMX.TMSFNCUtils"
#pragma link "FMX.TMSFNCWebBrowser"
#pragma link "FMX.TMSFNCOpenLayers"
#pragma link "FMX.TMSFNCMapsCommonTypes"
#pragma resource "*.fmx"
TFrame19 *Frame19;
//---------------------------------------------------------------------------
__fastcall TFrame19::TFrame19(TComponent* Owner, String baseurl, String resource, String titulo)
	: TFrame(Owner), baseurl(baseurl), resource(resource), titulo(titulo)
{
}
//---------------------------------------------------------------------------
void __fastcall TFrame19::ButtonCloseClick(TObject *Sender)
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
					Frame19->DisposeOf();
				});
		}
	)->Start();
}
//---------------------------------------------------------------------------


