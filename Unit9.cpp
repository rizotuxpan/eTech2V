//---------------------------------------------------------------------------

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
	RellenarComboBox(ComboBoxMarca, "camaramodelomarca");
	RellenarComboBox(ComboBoxTipo, "camaramodelotipo");
	PopulateStringGrid();
	ButtonEdit->Enabled = false;
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
//---------------------------------------------------------------------------
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
    if (ButtonEdit->Enabled) {
		UpdateRecord();
	}
	else {
		CreateRecord();
	}
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
		//RESTRequest->Response->ContentType = "application/json";
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
		ComboBoxMarca->Enabled = false;
		ComboBoxTipo->Enabled = false;
		ComboBoxMarca->ItemIndex = -1;
		ComboBoxTipo->ItemIndex = -1;
		LabelMarcaDescr->Text = "";
        LabelTipoDescr->Text = "";

		PopulateStringGrid();        
	} else
	{
		LabelMsg->Text = "Debe seleccionar Marca y Tipo";
	}
}
//---------------------------------------------------------------------------

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

	try { // Al seleccionar un elemento del StrinGrid selecciona el ComboBoxMarca
		int x = StrToInt(StringGrid->Cells[3][ARow]);

		for (int i = 0; i < ComboBoxMarca->Items->Count; i++) {
			TListBoxItem* selectedItem = static_cast<TListBoxItem*>(ComboBoxMarca->ListItems[i]);
			if (selectedItem->Tag == x) {
				ComboBoxMarca->ItemIndex = i;
			}
		}
	} catch (...) {
	}

    try { // Al seleccionar un elemento del StringGrid selecciona el ComboBoxTipo
		int x = StrToInt(StringGrid->Cells[4][ARow]);

		for (int i = 0; i < ComboBoxTipo->Items->Count; i++) {
			TListBoxItem* selectedItem = static_cast<TListBoxItem*>(ComboBoxTipo->ListItems[i]);
			if (selectedItem->Tag == x) {
				ComboBoxTipo->ItemIndex = i;
			}
		}
	} catch (...) {
	}

	ButtonDelete->Enabled = true;
	ButtonNew->Enabled = true;
	ButtonSave->Enabled = false;
	ButtonEdit->Enabled = true;
	LabelMsg->Text = "";
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

//---------------------------------------------------------------------------

void TFrame9::EditRecord()
{
	ButtonSave->Enabled = true;
	ButtonDelete->Enabled = false;
	ButtonNew->Enabled = false;
	EditClave->Enabled = true;
	MemoDescr->Enabled = true;
	ComboBoxMarca->Enabled = true;
	ComboBoxTipo->Enabled = true;
	EditClave->SetFocus();
}

//---------------------------------------------------------------------------

void __fastcall TFrame9::ButtonEditClick(TObject *Sender)
{
	if (LabelButtonEdit->Text == "Editar")
	{
		LabelButtonEdit->Text = "Cancelar";
		EditRecord();
	}
	else
	{
		LabelButtonEdit->Text = "Editar";
		EditClave->Enabled = false;
		MemoDescr->Enabled = false;
		EditClave->SetFocus();
		ButtonSave->Enabled = true;
		ButtonNew->Enabled = false;
		ButtonDelete->Enabled = false;
		ComboBoxMarca->Enabled = false;
		ComboBoxTipo->Enabled = false;
		LabelMsg->Text = "";

	}
}

//---------------------------------------------------------------------------

void __fastcall TFrame9::ButtonDeleteClick(TObject *Sender)
{
	DeleteRecord();
}
//---------------------------------------------------------------------------ç
void TFrame9::DeleteRecord()
{
    TRESTClient *RESTClient = new TRESTClient(NULL);
	TRESTRequest *RESTRequest = new TRESTRequest(NULL);
	TRESTResponse *RESTResponse = new TRESTResponse(NULL);

	RESTClient->BaseURL = baseurl;
	RESTRequest->Response = RESTResponse;
	RESTRequest->Client = RESTClient;

	RESTRequest->Resource = resource+"?id="+LabelId->Text;
	RESTRequest->Response->ContentType = "application/json";
	RESTRequest->Response->ContentEncoding = "UTF-8";
	RESTRequest->Method= TRESTRequestMethod::rmDELETE;
	RESTRequest->Execute();

	TJSONValue *jValue = RESTResponse->JSONValue;
	TJSONArray *JSONArray = dynamic_cast<TJSONArray*>(jValue);
	LabelMsg->Text = JSONArray->Items[1]->ToString() == "\"ok\"" ? "Registro borrado correctamente" : "El registro no se pudo guardar";

	EditClave->Text = "";
	MemoDescr->Text = "";
	ComboBoxMarca->ItemIndex = -1;
	ComboBoxTipo->ItemIndex = -1;
	LabelMarcaDescr->Text = "";
    LabelTipoDescr->Text = "";
	EditClave->Enabled = false;
	MemoDescr->Enabled = false;
	ButtonSave->Enabled = false;
	ComboBoxMarca->Enabled = false;
    ComboBoxTipo->Enabled = false;
	ButtonNew->Enabled = true;

	PopulateStringGrid();
}

//---------------------------------------------------------------------------

void TFrame9::UpdateRecord()
{
	TRESTClient *RESTClient = new TRESTClient(NULL);
	TRESTRequest *RESTRequest = new TRESTRequest(NULL);
	TRESTResponse *RESTResponse = new TRESTResponse(NULL);

	auto marcaSeleccionada = ComboBoxMarca->ListItems[ComboBoxMarca->ItemIndex];
	auto tipoSeleccionado = ComboBoxTipo->ListItems[ComboBoxTipo->ItemIndex];
	RESTClient->BaseURL = baseurl;
	RESTRequest->Response = RESTResponse;
	RESTRequest->Client = RESTClient;
	RESTRequest->Resource = resource+"?id="+LabelId->Text+"&clave="+EditClave->Text+"&descr="+MemoDescr->Text+"&camaramodelomarca_id="+marcaSeleccionada->Tag+"&camaramodelotipo_id="+tipoSeleccionado->Tag;;
	RESTRequest->Response->ContentType = "application/json";
	RESTRequest->Response->ContentEncoding = "UTF-8";
	RESTRequest->Method= TRESTRequestMethod::rmPUT;
	RESTRequest->Execute();

	TJSONValue *jValue = RESTResponse->JSONValue;
	TJSONArray *JSONArray = dynamic_cast<TJSONArray*>(jValue);
	LabelMsg->Text = JSONArray->Items[1]->ToString() == "\"ok\"" ? "Registro actualizado correctamente" : "El registro no se pudo actualizar";

	EditClave->Enabled = false;
	MemoDescr->Enabled = false;
	ButtonSave->Enabled = false;
	ButtonNew->Enabled = true;
	ComboBoxMarca->Enabled = false;
	ComboBoxTipo->Enabled = false;
	LabelButtonEdit->Text = "Editar";

	PopulateStringGrid();
}
