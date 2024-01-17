//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "Unit19.h"
#include "MainWindow.h"
#include <IdURI.hpp>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TFrame19 *Frame19;
//---------------------------------------------------------------------------
__fastcall TFrame19::TFrame19(TComponent* Owner, String baseurl, String resource, String titulo)
	: TFrame(Owner), baseurl(baseurl), resource(resource), titulo(titulo)
{
	TMapCoordinate mapCenter = TMapCoordinate::Create(40.712776,-74.005974);
	MapView1->Location = mapCenter;


	TMapMarkerDescriptor myMarker = TMapMarkerDescriptor::Create(mapCenter, "MyMarker");
	// Make a marker draggable
	myMarker.Draggable = true;
	// Make a marker visible
	myMarker.Visible = true;
	MapView1->AddMarker(myMarker);

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

