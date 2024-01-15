//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "Unit12.h"
#include "MainWindow.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TFrame12 *Frame12;
//---------------------------------------------------------------------------
__fastcall TFrame12::TFrame12(TComponent* Owner, String baseurl, String resource, String titulo)
	: TFrame(Owner), baseurl(baseurl), resource(resource), titulo(titulo)
{
    RellenarComboBoxMarca(ComboBoxMarca, "switchmodelomarca");
	PopulateStringGrid();

    // Oculta identificadores
	StringGrid->Columns[0]->Visible  = false; // id
	StringGrid->Columns[1]->Visible  = false; // marca
	StringGrid->Columns[2]->Visible  = false; // tipo
	StringGrid->Columns[3]->Visible  = false; // modelo

	StringGrid->Columns[2]->Width = 180;
	ButtonNew->OnClick(ButtonNew);
}
//---------------------------------------------------------------------------
void __fastcall TFrame12::ButtonCloseClick(TObject *Sender)
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
					Frame12->DisposeOf();
				});
		}
	)->Start();
}
//---------------------------------------------------------------------------
void TFrame12::PopulateStringGrid()
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
					TJSONValue* JSONObjectMarcaId      = JSONObject->GetValue("marca_id");
					TJSONValue* JSONObjectTipoId       = JSONObject->GetValue("tipo_id");
					TJSONValue* JSONObjectMarcaClave   = JSONObject->GetValue("marcaclave");
					TJSONValue* JSONObjectMarcaDescr   = JSONObject->GetValue("marcadescr");
                    TJSONValue* JSONObjectPuertos      = JSONObject->GetValue("puertos");
					//TJSONValue* JSONObjectCostoFactura = JSONObject->GetValue("costofactura");
					StringGrid->RowCount = i+1;

					StringGrid->Cells[0][i]  = JSONObjectId->Value();
					StringGrid->Cells[1][i]  = JSONObjectMarcaId->Value();
					StringGrid->Cells[2][i]  = JSONObjectTipoId->Value();
					StringGrid->Cells[3][i]  = JSONObjectModeloId->Value();

					StringGrid->Cells[4][i]  = JSONObjectMarcaClave->Value(); // Marca
					StringGrid->Cells[5][i]  = JSONObjectTipoClave->Value(); // Tipo
					StringGrid->Cells[6][i]  = JSONObjectModeloClave->Value(); // Modelo
					StringGrid->Cells[7][i]  = JSONObjectSerie->Value(); // Serie
					StringGrid->Cells[8][i]  = JSONObjectPuertos->Value(); // Puertos

					StringGrid->Cells[9][i] = JSONObjectMarcaDescr->Value();
					StringGrid->Cells[10][i]  = JSONObjectTipoDescr->Value();
					StringGrid->Cells[11][i]  = JSONObjectModeloDescr->Value();

				}
			}

		}
	} catch(const Exception &e) {
		ShowMessage(e.Message);
	}
}
//---------------------------------------------------------------------------
void TFrame12::RellenarComboBoxMarca(TComboBox *ComboBox, const UnicodeString &resource)
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

void __fastcall TFrame12::ComboBoxMarcaChange(TObject *Sender)
{
    TComboBox *comboBox = dynamic_cast<TComboBox*>(Sender);
	if (comboBox != nullptr && comboBox->ItemIndex != -1)
	{
		// Accediendo al elemento seleccionado
		TListBoxItem* selectedItem = static_cast<TListBoxItem*>(comboBox->ListItems[comboBox->ItemIndex]);
		if (selectedItem != nullptr) {
			int marca_id = selectedItem->Tag;

			RellenarComboBoxTipo(ComboBoxTipo, "switchmodelotipo", marca_id);
		}
	}
}
//---------------------------------------------------------------------------
void TFrame12::RellenarComboBoxTipo(TComboBox *ComboBox, const UnicodeString &resource, int marca_id)
{
	ComboBox->Items->Clear();
	TRESTClient *RESTClient = new TRESTClient(nullptr);
	TRESTRequest *RESTRequest = new TRESTRequest(nullptr);
	TRESTResponse *RESTResponse = new TRESTResponse(nullptr);
	RESTRequest->Client = RESTClient;
	RESTRequest->Response = RESTResponse;

	RESTClient->BaseURL = baseurl;
	RESTRequest->Resource = resource+"?switchmodelomarca_id="+IntToStr(marca_id);
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
void TFrame12::RellenarComboBoxModelo(TComboBox *ComboBox, const UnicodeString &resource, int marca_id, int tipo_id)
{
    ComboBox->Items->Clear();
	TRESTClient *RESTClient = new TRESTClient(nullptr);
	TRESTRequest *RESTRequest = new TRESTRequest(nullptr);
	TRESTResponse *RESTResponse = new TRESTResponse(nullptr);
	RESTRequest->Client = RESTClient;
	RESTRequest->Response = RESTResponse;

	RESTClient->BaseURL = baseurl;
	RESTRequest->Resource = resource+"?switchmodelomarca_id="+IntToStr(marca_id)+"&switchmodelotipo_id="+IntToStr(tipo_id);
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

void __fastcall TFrame12::ComboBoxTipoChange(TObject *Sender)
{
    TComboBox *comboBox = dynamic_cast<TComboBox*>(Sender);
	if (comboBox != nullptr && comboBox->ItemIndex != -1)
	{
		// Accediendo al elemento seleccionado
		TListBoxItem* selectedItemMarca = static_cast<TListBoxItem*>(ComboBoxMarca->ListItems[ComboBoxMarca->ItemIndex]);
		TListBoxItem* selectedItemTipo  = static_cast<TListBoxItem*>(comboBox->ListItems[comboBox->ItemIndex]);

		if (selectedItemMarca != nullptr && selectedItemTipo != nullptr)
		{
			RellenarComboBoxModelo(ComboBoxModelo, "switchmodelo", selectedItemMarca->Tag, selectedItemTipo->Tag);
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TFrame12::ButtonNewClick(TObject *Sender)
{
	ComboBoxMarca->ItemIndex = -1;
	ComboBoxMarca->Enabled = true;
	ComboBoxTipo->ItemIndex = -1;
	ComboBoxTipo->Enabled = true;
	ComboBoxModelo->ItemIndex = -1;
    ComboBoxModelo->Enabled = -1;
	EditSerie->Text = "";
    EditSerie->Enabled = true;
    ComboBoxMarca->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TFrame12::ButtonSaveClick(TObject *Sender)
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
	ComboBoxTipo->Enabled = false;
	ComboBoxModelo->Enabled = false;
	EditSerie->Enabled = false;
}
//---------------------------------------------------------------------------
void TFrame12::CreateRecord()
{
	//Validar que haya seleccionado el modelo
	if (ComboBoxModelo->ItemIndex != -1)
	{
		TRESTClient *RESTClient = new TRESTClient(NULL);
		TRESTRequest *RESTRequest = new TRESTRequest(NULL);
		TRESTResponse *RESTResponse = new TRESTResponse(NULL);

		//Obtiene tag de los elementos seccionados en Marca y Tipo
		auto modeloSeleccionado = ComboBoxModelo->ListItems[ComboBoxModelo->ItemIndex];

		RESTClient->BaseURL = baseurl;
		RESTRequest->Response = RESTResponse;
		RESTRequest->Client = RESTClient;
		RESTRequest->Resource = resource+"?serie="+EditSerie->Text+"&switchmodelo_id="+modeloSeleccionado->Tag+"&puertos="+EditPuertos->Text;
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

void __fastcall TFrame12::StringGridSelectCell(TObject *Sender, const int ACol,
		  const int ARow, bool &CanSelect)
{
	LabelId->Text = StringGrid->Cells[0][ARow];
	EditSerie->Text = StringGrid->Cells[7][ARow];
	EditPuertos->Text = StringGrid->Cells[8][ARow];

	// Selecciona en ComboBoxMarca la marca que corresponde al elemento seleccionado en el StrinGrid
	try {
		int x = StrToInt(StringGrid->Cells[1][ARow]);

		for (int i = 0; i < ComboBoxMarca->Items->Count; i++) {
			TListBoxItem* selectedItem = static_cast<TListBoxItem*>(ComboBoxMarca->ListItems[i]);
			if (selectedItem->Tag == x) {
				ComboBoxMarca->ItemIndex = i;
			}
		}
	} catch (...) {
	}

	// Selecciona en ComboBoxTipo el tipo que corresponde al elemento seleccionado en el StrinGrid
	try {
		int x = StrToInt(StringGrid->Cells[2][ARow]);

		for (int i = 0; i < ComboBoxTipo->Items->Count; i++) {
			TListBoxItem* selectedItem = static_cast<TListBoxItem*>(ComboBoxTipo->ListItems[i]);
			if (selectedItem->Tag == x) {
				ComboBoxTipo->ItemIndex = i;
			}
		}
	} catch (...) {
	}

	// Selecciona en ComboBoxModelo el modelo que corresponde al elemento seleccionado en el StrinGrid
	try {
		int x = StrToInt(StringGrid->Cells[3][ARow]);

		for (int i = 0; i < ComboBoxModelo->Items->Count; i++) {
			TListBoxItem* selectedItem = static_cast<TListBoxItem*>(ComboBoxModelo->ListItems[i]);
			if (selectedItem->Tag == x) {
				ComboBoxModelo->ItemIndex = i;
			}
		}
	} catch (...) {
	}

	LabelMsg->Text = "";
	//Desactiva los controles excepto el Grid
	ComboBoxMarca->Enabled = false;
	ComboBoxTipo->Enabled = false;
	ComboBoxModelo->Enabled = false;
	EditSerie->Enabled = false;
	EditPuertos->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TFrame12::ButtonDeleteClick(TObject *Sender)
{
	DeleteRecord();
}
//---------------------------------------------------------------------------
void TFrame12::DeleteRecord()
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

	EditSerie->Text = "";
	ComboBoxMarca->ItemIndex  = -1;
	ComboBoxTipo->ItemIndex   = -1;
	ComboBoxModelo->ItemIndex = -1;

	//PopulateStringGrid();
    eliminarFila(StringGrid, StringGrid->Selected);
}
//---------------------------------------------------------------------------
void TFrame12::eliminarFila(TStringGrid *grid, int numeroFila) {
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
//---------------------------------------------------------------------------

void __fastcall TFrame12::ButtonEditClick(TObject *Sender)
{
    if (LabelButtonEdit->Text == "Editar") {
		ComboBoxMarca->Enabled = true;
		ComboBoxTipo->Enabled = true;
		ComboBoxModelo->Enabled = true;
		EditSerie->Enabled = true;
		EditPuertos->Enabled = true;
		LabelButtonEdit->Text = "Cancelar";
	}
	else
	{
		ComboBoxMarca->Enabled = false;
		ComboBoxTipo->Enabled = false;
		ComboBoxModelo->Enabled = false;
		EditSerie->Enabled = false;
        EditPuertos->Enabled = false;
		LabelButtonEdit->Text = "Editar";
	}
}
//---------------------------------------------------------------------------
void TFrame12::UpdateRecord()
{
	TRESTClient *RESTClient = new TRESTClient(NULL);
	TRESTRequest *RESTRequest = new TRESTRequest(NULL);
	TRESTResponse *RESTResponse = new TRESTResponse(NULL);

	auto modeloSeleccionado = ComboBoxModelo->ListItems[ComboBoxModelo->ItemIndex];
	RESTClient->BaseURL = baseurl;
	RESTRequest->Response = RESTResponse;
	RESTRequest->Client = RESTClient;
	RESTRequest->Resource = resource+"?id="+LabelId->Text+"&serie="+EditSerie->Text+"&switchmodelo_id="+modeloSeleccionado->Tag;
	RESTRequest->Response->ContentType = "application/json";
	RESTRequest->Response->ContentEncoding = "UTF-8";
	RESTRequest->Method= TRESTRequestMethod::rmPUT;
	RESTRequest->Execute();

	TJSONValue *jValue = RESTResponse->JSONValue;
	TJSONArray *JSONArray = dynamic_cast<TJSONArray*>(jValue);
	LabelMsg->Text = JSONArray->Items[1]->ToString() == "\"ok\"" ? "Registro actualizado correctamente" : "El registro no se pudo actualizar";

	PopulateStringGrid();

}
//---------------------------------------------------------------------------
