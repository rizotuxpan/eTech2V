//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "Unit18.h"
#include "MainWindow.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TFrame18 *Frame18;
//---------------------------------------------------------------------------
__fastcall TFrame18::TFrame18(TComponent* Owner, String baseurl, String resource, String titulo)
	: TFrame(Owner), baseurl(baseurl), resource(resource), titulo(titulo)
{
    RellenarComboBoxMarca(ComboBoxMarca, "radiomodelomarca");
    PopulateStringGrid();
}
//---------------------------------------------------------------------------
void __fastcall TFrame18::ButtonCloseClick(TObject *Sender)
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
					Frame18->DisposeOf();
				});
		}
	)->Start();
}
//---------------------------------------------------------------------------
void TFrame18::PopulateStringGrid()
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
					TJSONValue* JSONObjectDescr        = JSONObject->GetValue("descr");
                    TJSONValue* JSONObjectMarcaId      = JSONObject->GetValue("marca_id");
					TJSONValue* JSONObjectMarcaClave   = JSONObject->GetValue("marcaclave");
					TJSONValue* JSONObjectMarcaDescr   = JSONObject->GetValue("marcadescr");
					TJSONValue* JSONObjectModeloId     = JSONObject->GetValue("modelo_id");
					TJSONValue* JSONObjectModeloClave  = JSONObject->GetValue("modeloclave");
					TJSONValue* JSONObjectModeloDescr  = JSONObject->GetValue("modelodescr");
					//TJSONValue* JSONObjectCostoFactura = JSONObject->GetValue("costofactura");
					StringGrid->RowCount = i+1;

					StringGrid->Cells[0][i]  = JSONObjectId->Value();
					StringGrid->Cells[1][i]  = JSONObjectMarcaId->Value();
					StringGrid->Cells[2][i]  = JSONObjectModeloId->Value();

					StringGrid->Cells[3][i]  = JSONObjectMarcaClave->Value(); // Marca
					StringGrid->Cells[4][i]  = JSONObjectModeloClave->Value(); // Modelo
					StringGrid->Cells[5][i]  = JSONObjectSerie->Value(); // Serie
					StringGrid->Cells[6][i]  = JSONObjectDescr->Value(); // Descripcion
					StringGrid->Cells[7][i]  = JSONObjectMarcaDescr->Value();
					StringGrid->Cells[8][i]  = JSONObjectModeloDescr->Value();

				}
			}

		}
	} catch(const Exception &e) {
		ShowMessage(e.Message);
	}
}
//---------------------------------------------------------------------------
void TFrame18::RellenarComboBoxMarca(TComboBox *ComboBox, const UnicodeString &resource)
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
void __fastcall TFrame18::StringGridSelectCell(TObject *Sender, const int ACol,
          const int ARow, bool &CanSelect)
{
	LabelId->Text = StringGrid->Cells[0][ARow];
	EditSerie->Text = StringGrid->Cells[5][ARow];
	MemoDescr->Text = StringGrid->Cells[6][ARow];

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

	// Selecciona en ComboBoxModelo el modelo que corresponde al elemento seleccionado en el StrinGrid
	try {
		int x = StrToInt(StringGrid->Cells[2][ARow]);

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
	ComboBoxModelo->Enabled = false;
	EditSerie->Enabled = false;
	MemoDescr->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TFrame18::ComboBoxMarcaChange(TObject *Sender)
{
    TComboBox *comboBox = dynamic_cast<TComboBox*>(Sender);
	if (comboBox != nullptr && comboBox->ItemIndex != -1)
	{
		// Accediendo al elemento seleccionado
		TListBoxItem* selectedItem = static_cast<TListBoxItem*>(comboBox->ListItems[comboBox->ItemIndex]);
		if (selectedItem != nullptr) {
			int marca_id = selectedItem->Tag;
			RellenarComboBoxModelo(ComboBoxModelo, "radiomodelo", marca_id);
		}
	}
}
//---------------------------------------------------------------------------
void TFrame18::RellenarComboBoxModelo(TComboBox *ComboBox, const UnicodeString &resource, int marca_id)
{
    ComboBox->Items->Clear();
	TRESTClient *RESTClient = new TRESTClient(nullptr);
	TRESTRequest *RESTRequest = new TRESTRequest(nullptr);
	TRESTResponse *RESTResponse = new TRESTResponse(nullptr);
	RESTRequest->Client = RESTClient;
	RESTRequest->Response = RESTResponse;

	RESTClient->BaseURL = baseurl;
	RESTRequest->Resource = resource+"?radiomodelomarca_id="+IntToStr(marca_id);
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
void __fastcall TFrame18::ButtonNewClick(TObject *Sender)
{
    ComboBoxMarca->ItemIndex = -1;
	ComboBoxMarca->Enabled = true;
	ComboBoxModelo->ItemIndex = -1;
	ComboBoxModelo->Enabled = -1;
	EditSerie->Text = "";
	EditSerie->Enabled = true;
	MemoDescr->Text = "";
	MemoDescr->Enabled = true;
	ComboBoxMarca->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TFrame18::ButtonEditClick(TObject *Sender)
{
    if (LabelButtonEdit->Text == "Editar") {
		ComboBoxMarca->Enabled = true;
		ComboBoxModelo->Enabled = true;
		EditSerie->Enabled = true;
		MemoDescr->Enabled = true;
		LabelButtonEdit->Text = "Cancelar";
	}
	else
	{
		ComboBoxMarca->Enabled = false;
		ComboBoxModelo->Enabled = false;
		EditSerie->Enabled = false;
        MemoDescr->Enabled = false;
		LabelButtonEdit->Text = "Editar";
	}
}
//---------------------------------------------------------------------------

void __fastcall TFrame18::ButtonDeleteClick(TObject *Sender)
{
	DeleteRecord();
}
//---------------------------------------------------------------------------
void TFrame18::DeleteRecord()
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
	MemoDescr->Text = "";
	ComboBoxMarca->ItemIndex  = -1;
	ComboBoxModelo->ItemIndex = -1;

	//PopulateStringGrid();
    eliminarFila(StringGrid, StringGrid->Selected);
}
//---------------------------------------------------------------------------
void __fastcall TFrame18::ButtonSaveClick(TObject *Sender)
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
	ComboBoxModelo->Enabled = false;
	EditSerie->Enabled = false;
    MemoDescr->Enabled = "";
}
//---------------------------------------------------------------------------
void TFrame18::CreateRecord()
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
		RESTRequest->Resource = resource+"?serie="+EditSerie->Text+"&radiomodelo_id="+modeloSeleccionado->Tag+"&descr="+MemoDescr->Text;
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
void TFrame18::eliminarFila(TStringGrid *grid, int numeroFila) {
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
void TFrame18::UpdateRecord()
{
	TRESTClient *RESTClient = new TRESTClient(NULL);
	TRESTRequest *RESTRequest = new TRESTRequest(NULL);
	TRESTResponse *RESTResponse = new TRESTResponse(NULL);

	auto modeloSeleccionado = ComboBoxModelo->ListItems[ComboBoxModelo->ItemIndex];
	RESTClient->BaseURL = baseurl;
	RESTRequest->Response = RESTResponse;
	RESTRequest->Client = RESTClient;
	RESTRequest->Resource = resource+"?id="+LabelId->Text+"&serie="+EditSerie->Text+"&radiomodelo_id="+modeloSeleccionado->Tag+"&descr="+MemoDescr->Text;
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
