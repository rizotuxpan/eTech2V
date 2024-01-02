//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TFrame1 *Frame1;
//---------------------------------------------------------------------------
__fastcall TFrame1::TFrame1(TComponent* Owner, String parametro)
	: TFrame(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFrame1::ButtonNewClick(TObject *Sender)
{
	Nuevo();
}
//---------------------------------------------------------------------------
void TFrame1::Nuevo() {
	LabelId->Text = "";
	EditClave->Text = "";
	MemoDescr->Text = "";
	EditClave->Enabled = true;
	MemoDescr->Enabled = true;
	EditClave->SetFocus();
	ButtonSave->Enabled = true;
	ButtonNew->Enabled = false;
	ButtonDelete->Enabled = false;
	ButtonEdit->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TFrame1::ButtonCloseClick(TObject *Sender)
{
	this->Visible=false;
}
//---------------------------------------------------------------------------

void TFrame1::PopulateStringGrid()
{
	RESTClient1->BaseURL = "http://localhost/etech2v/";
	RESTRequest1->Resource = "switchmodelomarca/";
	RESTRequest1->Response->ContentType = "application/json";
	RESTRequest1->Response->ContentEncoding = "UTF-8";
	RESTRequest1->Method= TRESTRequestMethod::rmGET;
	try {
		RESTRequest1->Execute();
		LabelMsg->Text = RESTResponse1->Content;
	} catch (Exception &e) {
        ShowMessage("Error: " + e.Message);
	}

}
void __fastcall TFrame1::ButtonDeleteClick(TObject *Sender)
{
    PopulateStringGrid();
}
//---------------------------------------------------------------------------

