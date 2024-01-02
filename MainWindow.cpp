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
	/*
	TFrame1 *MyFrame = new TFrame1(this, "xxx");
	MyFrame->Parent = PanelMain;
	MyFrame->Align = TAlignLayout::Client;
	MyFrame->Visible = true;
	*/

	if (!Frame1)
	{
		// Si no existe, crearlo y almacenar la referencia
		Frame1 = std::make_unique<TFrame1>(this, "xxx");
		Frame1->Parent = PanelMain;
		Frame1->Align = TAlignLayout::Client;
	}

	// Mostrar el TFrame
	Frame1->Visible = true;

}
//---------------------------------------------------------------------------


void __fastcall TForm1::FormCreate(TObject *Sender)
{
	TIniFile *iniFile = new TIniFile("etech2v.ini");
	UnicodeString BaseURL = iniFile->ReadString("REST", "BaseURL", "");
    UnicodeString SwitchModeloTipo = iniFile->ReadString("REST", "switchmodelotipo", "");
	delete iniFile;
	ShowMessage(BaseURL);
    ShowMessage(SwitchModeloTipo);
}
//---------------------------------------------------------------------------

