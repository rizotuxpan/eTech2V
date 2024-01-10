//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "Unit13.h"
#include "MainWindow.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Unit1"
#pragma resource "*.fmx"
TFrame13 *Frame13;
//---------------------------------------------------------------------------
__fastcall TFrame13::TFrame13(TComponent* Owner, String baseurl, String resource, String titulo)
	: TFrame1(Owner, baseurl, resource, titulo), baseurl(baseurl), resource(resource), titulo(titulo)
{
	RellenarComboBoxMarca(ComboBoxMarca, "radiomodelomarca");

    PopulateStringGrid();
	LabelTitulo->Text = titulo;
}
//---------------------------------------------------------------------------
void __fastcall TFrame13::ButtonCloseClick(TObject *Sender)
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
					Frame13->DisposeOf();
				});
		}
	)->Start();
}
//---------------------------------------------------------------------------
void TFrame13::PopulateStringGrid() {
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
					TJSONValue* JSONObjectId = JSONObject->GetValue("id");
					TJSONValue* JSONObjectClave = JSONObject->GetValue("clave");
					TJSONValue* JSONObjectDescr = JSONObject->GetValue("descr");
					TJSONValue* JSONObjectMarca = JSONObject->GetValue("marca");
					TJSONValue* JSONObjectMarcaId = JSONObject->GetValue("marca_id");
					StringGrid->RowCount = i+1;
					StringGrid->Cells[0][i] = JSONObjectId->Value();
					StringGrid->Cells[1][i] = JSONObjectClave->Value();
					StringGrid->Cells[2][i] = JSONObjectDescr->Value();
					StringGrid->Cells[3][i] = JSONObjectMarca->Value();
					StringGrid->Cells[4][i] = JSONObjectMarcaId->Value();
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
void TFrame13::RellenarComboBoxMarca(TComboBox *ComboBox, const UnicodeString &resource)
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
void __fastcall TFrame13::StringGridSelectCell(TObject *Sender, const int ACol,
		  const int ARow, bool &CanSelect)
{
	LabelId->Text = StringGrid->Cells[0][ARow];
	EditClave->Text = StringGrid->Cells[1][ARow];
	MemoDescr->Text = StringGrid->Cells[2][ARow];
    // Selecciona en ComboBoxMarca la marca que corresponde al elemento seleccionado en el StrinGrid
	try {
		int x = StrToInt(StringGrid->Cells[4][ARow]);

		for (int i = 0; i < ComboBoxMarca->Items->Count; i++) {
			TListBoxItem* selectedItem = static_cast<TListBoxItem*>(ComboBoxMarca->ListItems[i]);
			if (selectedItem->Tag == x) {
				ComboBoxMarca->ItemIndex = i;
			}
		}
	} catch (...) {
	}
	ButtonDelete->Enabled = true;
	ButtonNew->Enabled = true;
	ButtonSave->Enabled = false;
	ButtonEdit->Enabled = true;
}
//---------------------------------------------------------------------------
void TFrame13::NewRecord() {
	LabelId->Text = "";
	EditClave->Text = "";
	MemoDescr->Text = "";
	ComboBoxMarca->ItemIndex = -1;
    ComboBoxMarca->Enabled = true;

	EditClave->Enabled = true;
	MemoDescr->Enabled = true;
	EditClave->SetFocus();
	ButtonSave->Enabled = true;
	ButtonNew->Enabled = false;
	ButtonDelete->Enabled = false;
	ButtonEdit->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TFrame13::ButtonNewClick(TObject *Sender)
{
    NewRecord();
}
//---------------------------------------------------------------------------
void __fastcall TFrame13::ButtonEditClick(TObject *Sender)
{
	if (LabelButtonEdit->Text == "Editar") {
		ComboBoxMarca->Enabled = true;
		EditClave->Enabled = true;
		MemoDescr->Enabled = true;
		LabelButtonEdit->Text = "Cancelar";
	}
	else
	{
		ComboBoxMarca->Enabled = false;
		EditClave->Enabled = false;
		MemoDescr->Enabled = false;
		LabelButtonEdit->Text = "Editar";
	}

	ButtonSave->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TFrame13::ButtonSaveClick(TObject *Sender)
{
	if (LabelButtonEdit->Text == "Cancelar") {
		// Actualiza
		UpdateRecord();
	}
	else
	{
		// Inserta
        CreateRecord();
	}

	LabelButtonEdit->Text = "Editar";
	ComboBoxMarca->Enabled = false;
	EditClave->Enabled = false;
	MemoDescr->Enabled = false;
}
//---------------------------------------------------------------------------
void TFrame13::CreateRecord()
{
	//Validar que haya seleccionado el modelo
	if (ComboBoxMarca->ItemIndex != -1)
	{
		TRESTClient *RESTClient = new TRESTClient(NULL);
		TRESTRequest *RESTRequest = new TRESTRequest(NULL);
		TRESTResponse *RESTResponse = new TRESTResponse(NULL);

		//Obtiene tag de los elementos seccionados en Marca y Tipo
		auto marcaSeleccionada = ComboBoxMarca->ListItems[ComboBoxMarca->ItemIndex];

		RESTClient->BaseURL = baseurl;
		RESTRequest->Response = RESTResponse;
		RESTRequest->Client = RESTClient;
		RESTRequest->Resource = resource+"?clave="+EditClave->Text+"&descr="+MemoDescr->Text+"&radiomodelomarca_id="+marcaSeleccionada->Tag;
		RESTRequest->Response->ContentType = "application/json";
		RESTRequest->Response->ContentEncoding = "UTF-8";
		RESTRequest->Method = TRESTRequestMethod::rmPOST;
		RESTRequest->Execute();

		TJSONValue *jValue = RESTResponse->JSONValue;
		TJSONArray *JSONArray = dynamic_cast<TJSONArray*>(jValue);
		LabelMsg->Text = JSONArray->Items[1]->ToString() == "\"ok\"" ? "Registro guardado correctamente" : "El registro no se pudo guardar";

		PopulateStringGrid();
	} else
	{
		LabelMsg->Text = "Debe seleccionar Marca y Tipo";
	}
}
//---------------------------------------------------------------------------
void TFrame13::UpdateRecord()
{
	TRESTClient *RESTClient = new TRESTClient(NULL);
	TRESTRequest *RESTRequest = new TRESTRequest(NULL);
	TRESTResponse *RESTResponse = new TRESTResponse(NULL);

	auto marcaSeleccionada = ComboBoxMarca->ListItems[ComboBoxMarca->ItemIndex];
	RESTClient->BaseURL = baseurl;
	RESTRequest->Response = RESTResponse;
	RESTRequest->Client = RESTClient;
	RESTRequest->Resource = resource+"?id="+LabelId->Text+"&clave="+EditClave->Text+"&radiomodelomarca_id="+marcaSeleccionada->Tag+"&descr="+MemoDescr->Text;
	//RESTRequest->Response->ContentType = "application/json";
	RESTRequest->Response->ContentEncoding = "UTF-8";
	RESTRequest->Method= TRESTRequestMethod::rmPUT;
	RESTRequest->Execute();

	TJSONValue *jValue = RESTResponse->JSONValue;
	TJSONArray *JSONArray = dynamic_cast<TJSONArray*>(jValue);
	LabelMsg->Text = JSONArray->Items[1]->ToString() == "\"ok\"" ? "Registro actualizado correctamente" : "El registro no se pudo actualizar";

	PopulateStringGrid();
}