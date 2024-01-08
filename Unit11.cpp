//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "Unit11.h"
#include "MainWindow.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TFrame11 *Frame11;
//---------------------------------------------------------------------------
__fastcall TFrame11::TFrame11(TComponent* Owner, String baseurl, String resource, String titulo)
	: TFrame(Owner), baseurl(baseurl), resource(resource), titulo(titulo)
{
	RellenarComboBoxMarca(ComboBoxMarca, "camaramodelomarca");
	PopulateStringGrid();
}
//---------------------------------------------------------------------------
void __fastcall TFrame11::ButtonCloseClick(TObject *Sender)
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
					Frame11->DisposeOf();
				});
		}
	)->Start();
}
//---------------------------------------------------------------------------
void TFrame11::PopulateStringGrid()
{
    try {
		TRESTClient *RESTClient = new TRESTClient(NULL);
		TRESTRequest *RESTRequest = new TRESTRequest(NULL);
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
					TJSONValue* JSONObjectId           = JSONObject->GetValue("id");
					TJSONValue* JSONObjectSerie        = JSONObject->GetValue("serie");
					TJSONValue* JSONObjectModeloId     = JSONObject->GetValue("modelo_id");
					TJSONValue* JSONObjectModeloClave  = JSONObject->GetValue("modeloclave");
					TJSONValue* JSONObjectModeloDescr  = JSONObject->GetValue("modelodescr");
					TJSONValue* JSONObjectTipoClave    = JSONObject->GetValue("tipoclave");
					TJSONValue* JSONObjectTipoDescr    = JSONObject->GetValue("tipodescr");
					TJSONValue* JSONObjectMarcaClave   = JSONObject->GetValue("marcaclave");
					TJSONValue* JSONObjectMarcaDescr   = JSONObject->GetValue("marcadescr");
					TJSONValue* JSONObjectCostoFactura = JSONObject->GetValue("costofactura");
					StringGrid->RowCount = i+1;
					StringGrid->Cells[0][i] = JSONObjectId->Value();
					StringGrid->Cells[1][i] = JSONObjectSerie->Value();
					StringGrid->Cells[2][i] = JSONObjectModeloId->Value();
					StringGrid->Cells[3][i] = JSONObjectModeloClave->Value();
					StringGrid->Cells[4][i] = JSONObjectModeloDescr->Value();
					StringGrid->Cells[5][i] = JSONObjectTipoClave->Value();
					StringGrid->Cells[6][i] = JSONObjectTipoDescr->Value();
					StringGrid->Cells[7][i] = JSONObjectMarcaClave->Value();
					StringGrid->Cells[8][i] = JSONObjectMarcaDescr->Value();
					StringGrid->Cells[9][i] = JSONObjectCostoFactura->Value();

					//StringGrid->Columns[0]->Visible = false;
					StringGrid->Columns[2]->Width = 180;
				}
			}

		}
	} catch(const Exception &e) {
		ShowMessage(e.Message);
	}
}
//---------------------------------------------------------------------------
void TFrame11::RellenarComboBoxMarca(TComboBox *ComboBox, const UnicodeString &resource)
{
	TRESTClient *RESTClient = new TRESTClient(nullptr);
	TRESTRequest *RESTRequest = new TRESTRequest(nullptr);
	TRESTResponse *RESTResponse = new TRESTResponse(nullptr);
	RESTRequest->Client = RESTClient;
	RESTRequest->Response = RESTResponse;

	RESTClient->BaseURL = baseurl;
	RESTRequest->Resource = resource;
	RESTRequest->Execute();

	TJSONArray *jsonArray = (TJSONArray*)TJSONObject::ParseJSONValue(RESTResponse->Content);
	if (jsonArray != nullptr) {
		for (int i = 0; i < jsonArray->Count; i++) {
			TJSONObject *jsonObject = (TJSONObject*)jsonArray->Items[i];
			int id = StrToInt(jsonObject->GetValue("id")->Value());
			String clave = jsonObject->GetValue("clave")->Value();
			String descr = jsonObject->GetValue("descr")->Value();

			TListBoxItem *item = new TListBoxItem(ComboBox);
			item->Text = clave;
			item->Tag = id;
			item->TagString = descr;

			ComboBox->AddObject(item);
		}
	}

	delete jsonArray;
	delete RESTClient;
	delete RESTRequest;
	delete RESTResponse;
}
//---------------------------------------------------------------------------
void __fastcall TFrame11::ComboBoxMarcaChange(TObject *Sender)
{
	TComboBox *comboBox = dynamic_cast<TComboBox*>(Sender);
	if (comboBox != nullptr && comboBox->ItemIndex != -1)
	{
		// Accediendo al elemento seleccionado
		TListBoxItem* selectedItem = static_cast<TListBoxItem*>(comboBox->ListItems[comboBox->ItemIndex]);
		if (selectedItem != nullptr) {
			int marca_id = selectedItem->Tag;

			RellenarComboBoxTipo(ComboBoxTipo, "camaramodelo", marca_id);
		}
	}
}
//---------------------------------------------------------------------------
void TFrame11::RellenarComboBoxTipo(TComboBox *ComboBox, const UnicodeString &resource, int marca_id)
{
    ComboBox->Items->Clear();
	TRESTClient *RESTClient = new TRESTClient(nullptr);
	TRESTRequest *RESTRequest = new TRESTRequest(nullptr);
	TRESTResponse *RESTResponse = new TRESTResponse(nullptr);
	RESTRequest->Client = RESTClient;
	RESTRequest->Response = RESTResponse;

	RESTClient->BaseURL = baseurl;
	RESTRequest->Resource = resource+"?camaramodelomarca_id="+IntToStr(marca_id);
	RESTRequest->Execute();

	TJSONArray *jsonArray = (TJSONArray*)TJSONObject::ParseJSONValue(RESTResponse->Content);
	if (jsonArray != nullptr) {
		for (int i = 0; i < jsonArray->Count; i++) {
			TJSONObject *jsonObject = (TJSONObject*)jsonArray->Items[i];
			int id = StrToInt(jsonObject->GetValue("id")->Value());
			String clave = jsonObject->GetValue("clave")->Value();
			String descr = jsonObject->GetValue("descr")->Value();

			TListBoxItem *item = new TListBoxItem(ComboBox);
			item->Text = clave;
			item->Tag = id;
			item->TagString = descr;

			ComboBox->AddObject(item);
		}
	}

	delete jsonArray;
	delete RESTClient;
	delete RESTRequest;
	delete RESTResponse;
}
//---------------------------------------------------------------------------

