//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "Unit17.h"
#include "MainWindow.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Unit1"
#pragma resource "*.fmx"
TFrame17 *Frame17;
//---------------------------------------------------------------------------
__fastcall TFrame17::TFrame17(TComponent* Owner, String baseurl, String resource, String titulo)
	: TFrame1(Owner, baseurl, resource, titulo), baseurl(baseurl), resource(resource), titulo(titulo)
{
	RellenarComboBoxMarca(ComboBoxMaterial, "pmipostematerial");
	PopulateStringGrid();
}
//---------------------------------------------------------------------------
void __fastcall TFrame17::ButtonCloseClick(TObject *Sender)
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
					Frame17->DisposeOf();
				});
		}
	)->Start();
}
//---------------------------------------------------------------------------
void TFrame17::PopulateStringGrid() {
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
					TJSONValue* JSONObjectAltura = JSONObject->GetValue("altura");
					TJSONValue* JSONObjectMaterialId = JSONObject->GetValue("material_id");
					TJSONValue* JSONObjectMaterial = JSONObject->GetValue("material");
					TJSONValue* JSONObjectMaterialDescr = JSONObject->GetValue("materialdescr");

					StringGrid->RowCount = i+1;
					StringGrid->Cells[0][i] = JSONObjectId->Value();
					StringGrid->Cells[1][i] = JSONObjectClave->Value();
					StringGrid->Cells[2][i] = JSONObjectDescr->Value();
					StringGrid->Cells[3][i] = JSONObjectAltura->Value();
					StringGrid->Cells[4][i] = JSONObjectMaterialId->Value();
					StringGrid->Cells[5][i] = JSONObjectMaterial->Value();
					StringGrid->Cells[6][i] = JSONObjectMaterialDescr->Value();
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
void TFrame17::RellenarComboBoxMarca(TComboBox *ComboBox, const UnicodeString &resource)
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
void __fastcall TFrame17::StringGridSelectCell(TObject *Sender, const int ACol,
          const int ARow, bool &CanSelect)
{
    LabelId->Text = StringGrid->Cells[0][ARow];
	EditClave->Text = StringGrid->Cells[1][ARow];
	MemoDescr->Text = StringGrid->Cells[2][ARow];
	EditAltura->Text = StringGrid->Cells[3][ARow];
    LabelMaterialDescr->Text = StringGrid->Cells[6][ARow];
	// Selecciona en ComboBoxMarca la marca que corresponde al elemento seleccionado en el StrinGrid
	try {
		int x = StrToInt(StringGrid->Cells[4][ARow]);

		for (int i = 0; i < ComboBoxMaterial->Items->Count; i++) {
			TListBoxItem* selectedItem = static_cast<TListBoxItem*>(ComboBoxMaterial->ListItems[i]);
			if (selectedItem->Tag == x) {
				ComboBoxMaterial->ItemIndex = i;
			}
		}
	} catch (...) {
	}
	ButtonDelete->Enabled = true;
	ButtonNew->Enabled = true;
	ButtonSave->Enabled = false;
	ButtonEdit->Enabled = true;

	EditClave->Enabled = false;
	MemoDescr->Enabled = false;
	EditAltura->Enabled = false;
	ComboBoxMaterial->Enabled = false;
	ButtonSave->Enabled = false;
	ButtonNew->Enabled = true;
	ButtonDelete->Enabled = true;
	ButtonEdit->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TFrame17::ButtonNewClick(TObject *Sender)
{
    NewRecord();
}
//---------------------------------------------------------------------------
void TFrame17::NewRecord() {
	LabelId->Text = "";
	EditClave->Text = "";
	MemoDescr->Text = "";
	EditAltura->Text = "";
	ComboBoxMaterial->ItemIndex = -1;

	EditClave->Enabled = true;
	MemoDescr->Enabled = true;
	EditAltura->Enabled = true;
	ComboBoxMaterial->Enabled = true;
	EditClave->SetFocus();
	ButtonSave->Enabled = true;
	ButtonNew->Enabled = false;
	ButtonDelete->Enabled = false;
	ButtonEdit->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TFrame17::ButtonEditClick(TObject *Sender)
{
    if (LabelButtonEdit->Text == "Editar") {
		ComboBoxMaterial->Enabled = true;
		EditClave->Enabled = true;
		MemoDescr->Enabled = true;
		EditAltura->Enabled = true;
		LabelButtonEdit->Text = "Cancelar";
	}
	else
	{
		ComboBoxMaterial->Enabled = false;
		EditClave->Enabled = false;
		MemoDescr->Enabled = false;
        EditAltura->Enabled = false;
		LabelButtonEdit->Text = "Editar";
	}

	ButtonSave->Enabled = true;
}
//---------------------------------------------------------------------------
void TFrame17::DeleteRecord()
{
    TRESTClient *RESTClient = new TRESTClient(NULL);
	TRESTRequest *RESTRequest = new TRESTRequest(NULL);
	TRESTResponse *RESTResponse = new TRESTResponse(NULL);

	RESTClient->BaseURL = baseurl;
	RESTRequest->Response = RESTResponse;
	RESTRequest->Client = RESTClient;

	RESTRequest->Resource = resource+"?id="+LabelId->Text;
	RESTRequest->Method= TRESTRequestMethod::rmDELETE;
	RESTRequest->Execute();

	TJSONValue *jValue = RESTResponse->JSONValue;
	TJSONArray *JSONArray = dynamic_cast<TJSONArray*>(jValue);
	LabelMsg->Text = JSONArray->Items[1]->ToString() == "\"ok\"" ? "Registro borrado correctamente" : "El registro no se pudo guardar";

	EditClave->Text = "";
	MemoDescr->Text = "";
	EditAltura->Text = "";
	ComboBoxMaterial->ItemIndex  = -1;

	//PopulateStringGrid();
    eliminarFila(StringGrid, StringGrid->Selected);
}
//---------------------------------------------------------------------------
void __fastcall TFrame17::ButtonDeleteClick(TObject *Sender)
{
    DeleteRecord();
}
//---------------------------------------------------------------------------
void TFrame17::eliminarFila(TStringGrid *grid, int numeroFila) {
    if (grid == nullptr || numeroFila < 0 || numeroFila >= grid->RowCount) {
        // Verifica si el grid es válido y el número de fila está en rango
        return;
    }

    grid->BeginUpdate(); // Comienza la actualización del grid
    try {
        // Mover los datos de las filas siguientes hacia arriba
        for (int i = numeroFila; i < grid->RowCount - 1; i++) {
            for (int j = 0; j < grid->ColumnCount; j++) {
                grid->Cells[j][i] = grid->Cells[j][i + 1];
            }
        }
        grid->RowCount--; // Disminuir el conteo de filas
    } catch (const Exception& e) {
        ShowMessage(e.Message); // Mostrar mensaje de error si ocurre una excepción
    }
    grid->EndUpdate(); // Finalizar la actualización del grid

    // Opcional: Actualizar el grid si es necesario
    grid->Repaint();
}
void __fastcall TFrame17::ButtonSaveClick(TObject *Sender)
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
	ComboBoxMaterial->Enabled = false;
	EditClave->Enabled = false;
	MemoDescr->Enabled = false;
	EditAltura->Enabled = false;
}
//---------------------------------------------------------------------------
void TFrame17::CreateRecord()
{
	//Validar que haya seleccionado el modelo
	if (ComboBoxMaterial->ItemIndex != -1)
	{
		TRESTClient *RESTClient = new TRESTClient(NULL);
		TRESTRequest *RESTRequest = new TRESTRequest(NULL);
		TRESTResponse *RESTResponse = new TRESTResponse(NULL);

		//Obtiene tag de los elementos seccionados en Marca y Tipo
		auto materialSeleccionado = ComboBoxMaterial->ListItems[ComboBoxMaterial->ItemIndex];

		RESTClient->BaseURL = baseurl;
		RESTRequest->Response = RESTResponse;
		RESTRequest->Client = RESTClient;
		RESTRequest->Resource = resource+"?clave="+EditClave->Text+"&descr="+MemoDescr->Text+"&altura="+EditAltura->Text+"&postematerial_id="+materialSeleccionado->Tag;
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
void TFrame17::UpdateRecord()
{
	TRESTClient *RESTClient = new TRESTClient(NULL);
	TRESTRequest *RESTRequest = new TRESTRequest(NULL);
	TRESTResponse *RESTResponse = new TRESTResponse(NULL);

	auto materialSeleccionado = ComboBoxMaterial->ListItems[ComboBoxMaterial->ItemIndex];
	RESTClient->BaseURL = baseurl;
	RESTRequest->Response = RESTResponse;
	RESTRequest->Client = RESTClient;
	RESTRequest->Resource = resource+"?id="+LabelId->Text+"&clave="+EditClave->Text+"&postematerial_id="+materialSeleccionado->Tag+"&descr="+MemoDescr->Text+"&altura="+EditAltura->Text;
	//RESTRequest->Response->ContentType = "application/json";
	RESTRequest->Response->ContentEncoding = "UTF-8";
	RESTRequest->Method= TRESTRequestMethod::rmPUT;
	RESTRequest->Execute();

	TJSONValue *jValue = RESTResponse->JSONValue;
	TJSONArray *JSONArray = dynamic_cast<TJSONArray*>(jValue);
	LabelMsg->Text = JSONArray->Items[1]->ToString() == "\"ok\"" ? "Registro actualizado correctamente" : "El registro no se pudo actualizar";

	PopulateStringGrid();
}
