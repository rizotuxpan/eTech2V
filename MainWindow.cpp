//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "MainWindow.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TForm1* Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner) {}
//---------------------------------------------------------------------------

void __fastcall TForm1::MenuCatalogosSwitchesMarcasClick(TObject* Sender)
{
	resource = SwitchModeloMarca;
	Frame1 = new TFrame1(this, baseurl, resource, "Marcas de Switches");
	Frame1->Parent = PanelMain;
	Frame1->Align = TAlignLayout::Client;
	Frame1->Visible = true;
	Menu->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject* Sender)
{
	TIniFile* iniFile = new TIniFile("etech2v.ini");
	baseurl = iniFile->ReadString("REST", "BaseURL", "");
	SwitchModeloMarca = iniFile->ReadString("REST", "SwitchModeloMarca", "");
	SwitchModeloTipo  = iniFile->ReadString("REST", "SwitchModeloTipo", "");
	RadioModeloMarca  = iniFile->ReadString("REST", "RadioModeloMarca", "");
	CamaraModeloMarca = iniFile->ReadString("REST", "CamaraModeloMarca", "");
	CamaraModeloTipo  = iniFile->ReadString("REST", "CamaraModeloTipo", "");
	Gabinete          = iniFile->ReadString("REST", "Gabinete", "");
	PmiPosteMaterial  = iniFile->ReadString("REST", "PmiPosteMaterial", "");
    ArcoEstructura    = iniFile->ReadString("REST", "ArcoEstructura", "");
	delete iniFile;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MenuCatalogosSwitchesTiposClick(TObject* Sender)
{
	resource = SwitchModeloTipo;
	Frame2 = new TFrame2(this, baseurl, resource, "Tipos de Switches");
	Frame2->Parent = PanelMain;
	Frame2->Align = TAlignLayout::Client;
	Frame2->Visible = true;
	Menu->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MenuCatalogosRadiosMarcasClick(TObject* Sender)
{
	resource = RadioModeloMarca;
	Frame3 = new TFrame3(this, baseurl, resource, "Marcas de radios");
	Frame3->Parent = PanelMain;
	Frame3->Align = TAlignLayout::Client;
	Frame3->Visible = true;
	Menu->Enabled = false;
}
//---------------------------------------------------------------------------
void TForm1::EnableMenu(bool enable)
{
	Menu->Enabled = enable;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MenuArchivoSalirClick(TObject *Sender)
{
	// Crear un hilo anónimo para cerrar la aplicación
	TThread::CreateAnonymousThread(
		[]()
		{
			// Dormir brevemente para permitir que la operación de clic del botón se complete
			Sleep(100);

			// Terminar la aplicación
			TThread::Queue(NULL,
				[]()
				{
					Application->Terminate();
				});
		}
	)->Start();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MenuCatalogosCamarasMarcasClick(TObject *Sender)
{
	resource = CamaraModeloMarca;
	Frame4 = new TFrame4(this, baseurl, resource, "Marcas de cámaras");
	Frame4->Parent = PanelMain;
	Frame4->Align = TAlignLayout::Client;
	Frame4->Visible = true;
	EnableMenu(false);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MenuCatalogosCamarasTiposClick(TObject *Sender)
{
	resource = CamaraModeloTipo;
	Frame5 = new TFrame5(this, baseurl, resource, "Tipos de cámaras");
	Frame5->Parent = PanelMain;
	Frame5->Align = TAlignLayout::Client;
	Frame5->Visible = true;
	EnableMenu(false);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MenuCatalogosGabineteClick(TObject *Sender)
{
	resource = Gabinete;
	Frame6 = new TFrame6(this, baseurl, resource, "Gabinetes");
	Frame6->Parent = PanelMain;
	Frame6->Align = TAlignLayout::Client;
	Frame6->Visible = true;
	EnableMenu(false);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MenuCatalogosPMIPostesMaterialClick(TObject *Sender)

{
	resource = PmiPosteMaterial;
	Frame7 = new TFrame7(this, baseurl, resource, "Material de postes");
	Frame7->Parent = PanelMain;
	Frame7->Align = TAlignLayout::Client;
	Frame7->Visible = true;
	EnableMenu(false);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MenuCatalogosArcosEstructurasClick(TObject *Sender)
{
	resource = ArcoEstructura;
	Frame8 = new TFrame8(this, baseurl, resource, "Estructuras de los Arcos carreteros2");
	Frame8->Parent = PanelMain;
	Frame8->Align = TAlignLayout::Client;
	Frame8->Visible = true;
    EnableMenu(false);
}
//---------------------------------------------------------------------------

