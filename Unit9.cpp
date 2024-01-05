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
	RellenarComboBox(ComboBoxMarca, Form1->getCamaraModeloMarca());
    RellenarComboBox(ComboBoxTipo, Form1->getCamaraModeloTipo());
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

