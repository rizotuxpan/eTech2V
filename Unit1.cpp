//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "Unit1.h"
#include <System.JSON.hpp>
#include <System.SysUtils.hpp>
#include <REST.Client.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TFrame1 *Frame1;
//---------------------------------------------------------------------------
__fastcall TFrame1::TFrame1(TComponent* Owner, String baseurl, String resource, String titulo)
	: TFrame(Owner), baseurl(baseurl), resource(resource), titulo(titulo) {
	PopulateStringGrid();
	LabelTitulo->Text = titulo;
}
//---------------------------------------------------------------------------
void __fastcall TFrame1::ButtonNewClick(TObject *Sender) {
	NewRecord();
}
//---------------------------------------------------------------------------
void __fastcall TFrame1::ButtonCloseClick(TObject *Sender) {
	this->Visible=false;
}
//---------------------------------------------------------------------------
void TFrame1::PopulateStringGrid() {
	TRESTClient *RESTClient = new TRESTClient(NULL);
	TRESTRequest *RESTRequest = new TRESTRequest(NULL);

	try {
		RESTClient->BaseURL = baseurl;
		RESTRequest->Resource = resource;
		RESTRequest->Method = TRESTRequestMethod::rmGET;
		RESTRequest->Client = RESTClient;
		RESTRequest->Execute();

		if (RESTRequest->Response->StatusCode == 200) {
			TJSONObject* jsonObject = static_cast<TJSONObject*>(RESTRequest->Response->JSONValue);
			TJSONArray* JSONArray = dynamic_cast<TJSONArray*>(jsonObject);

			StringGrid->RowCount = 0;
			for (int i = 0; i < JSONArray->Count; ++i) {
				TJSONObject* JSONObject = dynamic_cast<TJSONObject*>(JSONArray->Items[i]);
				if (JSONObject) {
					TJSONValue* JSONObjectId = JSONObject->GetValue("id");
					TJSONValue* JSONObjectClave = JSONObject->GetValue("clave");
					TJSONValue* JSONObjectDescr = JSONObject->GetValue("descr");
					StringGrid->RowCount = i+1;
					StringGrid->Cells[0][i] = JSONObjectId->Value();
					StringGrid->Cells[1][i] = JSONObjectClave->Value();
					StringGrid->Cells[2][i] = JSONObjectDescr->Value();
					StringGrid->Columns[0]->Visible = false;
					StringGrid->Columns[2]->Width = 180;
				}
			}

		}
	} catch(const Exception &e) {
		ShowMessage(e.Message);
	}

}
//---------------------------------------------------------------------------
void TFrame1::NewRecord() {
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
void TFrame1::InsertRecord() {

}
//---------------------------------------------------------------------------
void TFrame1::UpdateRecord() {
}
//---------------------------------------------------------------------------
void TFrame1::CreateRecord() {
	TRESTClient *RESTClient = new TRESTClient(NULL);
	TRESTRequest *RESTRequest = new TRESTRequest(NULL);
	TRESTResponse *RESTResponse = new TRESTResponse(NULL);

	RESTClient->BaseURL = baseurl;
	RESTRequest->Response = RESTResponse;
    RESTRequest->Client = RESTClient;
	RESTRequest->Resource = resource+"?clave="+EditClave->Text+"&descr="+MemoDescr->Text;
	RESTRequest->Response->ContentType = "application/json";
	RESTRequest->Response->ContentEncoding = "UTF-8";
	RESTRequest->Method = TRESTRequestMethod::rmPOST;
	RESTRequest->Execute();

	TJSONValue *jValue = RESTResponse->JSONValue;
	TJSONArray *JSONArray = dynamic_cast<TJSONArray*>(jValue);
	LabelMsg->Text = JSONArray->Items[1]->ToString() == "\"ok\"" ? "Registro guardado correctamente" : "El registro no se pudo guardar";

	EditClave->Enabled = false;
	MemoDescr->Enabled = false;
	ButtonSave->Enabled = false;
	ButtonNew->Enabled = true;

	PopulateStringGrid();
}
//---------------------------------------------------------------------------
void TFrame1::DeleteRecord() {
}
//---------------------------------------------------------------------------
void __fastcall TFrame1::StringGridSelectCell(TObject *Sender, const int ACol,
		  const int ARow, bool &CanSelect)
{
	LabelId->Text = StringGrid->Cells[0][ARow];
	EditClave->Text = StringGrid->Cells[1][ARow];
	MemoDescr->Text = StringGrid->Cells[2][ARow];
	ButtonDelete->Enabled = true;
	ButtonNew->Enabled = true;
	ButtonSave->Enabled = false;
	ButtonEdit->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TFrame1::ButtonSaveClick(TObject *Sender)
{
    CreateRecord();
}
//---------------------------------------------------------------------------

