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

void __fastcall TForm1::MenuCatalogosSwitchesMarcasClick(TObject *Sender)
{
    // Crea una instancia del frame
    TFrame1 *MyFrame = new TFrame1(this);

    // Configura el parent del frame al panel
    MyFrame->Parent = PanelMain;

    // Ajusta el tama�o y la posici�n del frame seg�n tus necesidades
    MyFrame->Align = TAlignLayout::Client;

    // Muestra el frame
    MyFrame->Visible = true;
}
//---------------------------------------------------------------------------

