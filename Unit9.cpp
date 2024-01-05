﻿//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "Unit9.h"
#include "MainWindow.h"
#include <REST.Client.hpp>
#include <System.JSON.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Unit1"
#pragma resource "*.fmx"
TFrame9 *Frame9;
//---------------------------------------------------------------------------
__fastcall TFrame9::TFrame9(TComponent* Owner, String baseurl, String resource, String titulo)
	: TFrame1(Owner, baseurl, resource, titulo), baseurl(baseurl), resource(resource), titulo(titulo)
{
	RellenarComboBox(ComboBoxMarca, Form1->getCamaraModeloMarca());
	RellenarComboBox(ComboBoxTipo, Form1->getCamaraModeloTipo());
	PopulateStringGrid();
}
//---------------------------------------------------------------------------
void __fastcall TFrame9::ButtonCloseClick(TObject *Sender)
{
	Form1->EnableMenu(true);
	TThread::CreateAnonymousThread(
		[]()
		{
			Sleep(100);
			TThread::Queue(NULL,
				[]()
				{
					Frame9->DisposeOf();
				});
		}
	)->Start();
}
//---------------------------------------------------------------------------
void TFrame9::RellenarComboBox(TComboBox *ComboBox, const UnicodeString &resource)
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
void __fastcall TFrame9::ComboBoxMarcaChange(TObject *Sender)
{
	TComboBox *comboBox = dynamic_cast<TComboBox*>(Sender);
	if (comboBox != nullptr && comboBox->ItemIndex != -1)
	{
		// Accediendo al elemento seleccionado
		TListBoxItem* selectedItem = static_cast<TListBoxItem*>(comboBox->ListItems[comboBox->ItemIndex]);
		if (selectedItem != nullptr) {
			UnicodeString tagString = selectedItem->TagString;

			LabelMarcaDescr->Text=tagString;
		}
    }
}
//---------------------------------------------------------------------------

void __fastcall TFrame9::ComboBoxTipoChange(TObject *Sender)
{
    TComboBox *comboBox = dynamic_cast<TComboBox*>(Sender);
	if (comboBox != nullptr && comboBox->ItemIndex != -1)
	{
		// Accediendo al elemento seleccionado
		TListBoxItem* selectedItem = static_cast<TListBoxItem*>(comboBox->ListItems[comboBox->ItemIndex]);
		if (selectedItem != nullptr) {
			UnicodeString tagString = selectedItem->TagString;

			LabelTipoDescr->Text=tagString;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TFrame9::ButtonSaveClick(TObject *Sender)
{
	CreateRecord();
}
//---------------------------------------------------------------------------
void TFrame9::NewRecord()
{
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
	ComboBoxMarca->Enabled = true;
    ComboBoxTipo->Enabled = true;
	ComboBoxMarca->ItemIndex = -1;
	ComboBoxTipo->ItemIndex = -1;
	LabelMarcaDescr->Text = "";
	LabelTipoDescr->Text = "";
	LabelMsg->Text = "";
}
//---------------------------------------------------------------------------
void TFrame9::CreateRecord() {
	//Validar que haya seleccionado Marca y Tipo
	if ((ComboBoxMarca->ItemIndex != -1) and (ComboBoxTipo->ItemIndex !=-1))
	{
		TRESTClient *RESTClient = new TRESTClient(NULL);
		TRESTRequest *RESTRequest = new TRESTRequest(NULL);
		TRESTResponse *RESTResponse = new TRESTResponse(NULL);

		//Obtiene tag de los elementos seccionados en Marca y Tipo
		auto marcaSeleccionada = ComboBoxMarca->ListItems[ComboBoxMarca->ItemIndex];
		auto tipoSeleccionado = ComboBoxTipo->ListItems[ComboBoxTipo->ItemIndex];
		RESTClient->BaseURL = baseurl;
		RESTRequest->Response = RESTResponse;
		RESTRequest->Client = RESTClient;
		RESTRequest->Resource = resource+"?clave="+EditClave->Text+"&descr="+MemoDescr->Text+"&camaramodelomarca_id="+marcaSeleccionada->Tag+"&camaramodelotipo_id="+tipoSeleccionado->Tag;
		RESTRequest->Response->ContentType = "application/json";
		RESTRequest->Response->ContentEncoding = "UTF-8";
		RESTRequest->Method = TRESTRequestMethod::rmPOST;
		RESTRequest->Execute();

		TJSONValue *jValue = RESTResponse->JSONValue;
		TJSONArray *JSONArray = dynamic_cast<TJSONArray*>(jValue);
		LabelMsg->Text = JSONArray->Items[1]->ToString() == "\"ok\"" ? "Registro guardado correctamente" : "El registro no se pudo guardar";

		EditClave->Text = "";
		MemoDescr->Text = "";
		EditClave->Enabled = false;
		MemoDescr->Enabled = false;
		ButtonSave->Enabled = false;
		ButtonNew->Enabled = true;

		PopulateStringGrid();        
	} else
	{
		LabelMsg->Text = "Debe seleccionar Marca y Tipo";
	}
	
}
void __fastcall TFrame9::ButtonNewClick(TObject *Sender)
{
    NewRecord();
}
//---------------------------------------------------------------------------

void __fastcall TFrame9::StringGridSelectCell(TObject *Sender, const int ACol,
          const int ARow, bool &CanSelect)
{
	LabelId->Text = StringGrid->Cells[0][ARow];
	EditClave->Text = StringGrid->Cells[1][ARow];
	MemoDescr->Text = StringGrid->Cells[2][ARow];
	ComboBoxMarca->ItemIndex = -1;	
	for (int i=0; i < ComboBoxMarca->Items->Count; ++i) {
		if (ComboBoxMarca->Items[i]->Tag == i) {
			ComboMarca->ItemIndex = i;
			break;
		}
	}

	ButtonDelete->Enabled = true;
	ButtonNew->Enabled = true;
	ButtonSave->Enabled = false;
	ButtonEdit->Enabled = true;	
}
//---------------------------------------------------------------------------
void TFrame9::PopulateStringGrid()
{
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
					TJSONValue* JSONObjectMarca = JSONObject->GetValue("camaramodelomarca_id");
					TJSONValue* JSONObjectTipo = JSONObject->GetValue("camaramodelotipo_id");
					StringGrid->RowCount = i+1;
					StringGrid->Cells[0][i] = JSONObjectId->Value();
					StringGrid->Cells[1][i] = JSONObjectClave->Value();
					StringGrid->Cells[2][i] = JSONObjectDescr->Value();
					StringGrid->Cells[3][i] = JSONObjectMarca->Value();
					StringGrid->Cells[4][i] = JSONObjectTipo->Value();
					StringGrid->Columns[0]->Visible = false;
					StringGrid->Columns[3]->Visible = false;
					StringGrid->Columns[4]->Visible = false;
					StringGrid->Columns[2]->Width = 180;
				}
			}

		}
	} catch(const Exception &e) {
		ShowMessage(e.Message);
	}
}
