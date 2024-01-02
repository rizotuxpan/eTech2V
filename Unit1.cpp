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
__fastcall TFrame1::TFrame1(TComponent* Owner, String parametro)
	: TFrame(Owner)
{
    PopulateStringGrid();
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
	TRESTClient *RESTClient = new TRESTClient(NULL);
	TRESTRequest *RESTRequest = new TRESTRequest(NULL);

	try {
		RESTClient->BaseURL = "http://localhost/etech2v/";
		RESTRequest->Resource = "switchmodelomarca/";
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


