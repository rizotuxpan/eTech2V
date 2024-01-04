//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "MainWindow.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MenuCatalogosSwitchesMarcasClick(TObject *Sender) {
	if (!Frame1)
	{
        resource = SwitchModeloMarca;
		Frame1 = new TFrame1(this, baseurl, resource, "Marcas de Switches");
		Frame1->Parent = PanelMain;
		Frame1->Align = TAlignLayout::Client;
	}

	Frame1->Visible = true;

}
//---------------------------------------------------------------------------


void __fastcall TForm1::FormCreate(TObject *Sender)
{
	TIniFile *iniFile = new TIniFile("etech2v.ini");
	baseurl = iniFile->ReadString("REST", "BaseURL", "");
	SwitchModeloMarca = iniFile->ReadString("REST", "SwitchModeloMarca", "");
	SwitchModeloTipo = iniFile->ReadString("REST", "SwitchModeloTipo", "");
	delete iniFile;
}
//---------------------------------------------------------------------------

