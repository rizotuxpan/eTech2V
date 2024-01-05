//---------------------------------------------------------------------------

#pragma hdrstop

#include "ComboBox.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma classgroup "FMX.Controls.TControl"
#pragma resource "*.dfm"
TDataModule10 *DataModule10;
//---------------------------------------------------------------------------
__fastcall TDataModule10::TDataModule10(TComponent* Owner)
	: TDataModule(Owner)
{
}
//---------------------------------------------------------------------------
UnicodeString Objeto4Combo::getId()
{
	return Id;
}
//---------------------------------------------------------------------------
UnicodeString Objeto4Combo::getDescr()
{
	return Descr;
}
//---------------------------------------------------------------------------
Objeto4Combo* ToObject(TJSONObject* jsonObject)
{
	if (jsonObject)
	{
		UnicodeString id = jsonObject->GetValue("id")->Value();
		UnicodeString clave = jsonObject->GetValue("clave")->Value();
		UnicodeString descr = jsonObject->GetValue("descr")->Value();

		Objeto4Combo* miObjeto = new Objeto4Combo(id, clave, descr);

		return miObjeto;
	}
	return nullptr;
}
//---------------------------------------------------------------------------
void PopulateComboBox(TComboBox* combobox, TRESTClient* client,
		TRESTRequest* request, TRESTResponse* response, UnicodeString getUrl)
{
	client->BaseURL = getUrl;
	request->Execute();

	TJSONObject* jsonObject =
		static_cast<TJSONObject*>(response->JSONValue);

	TJSONArray* JSONArray = dynamic_cast<TJSONArray*>(jsonObject);

	for (int i = 0; i < JSONArray->Count; ++i)
	{
		TJSONObject* JSONObject =
			dynamic_cast<TJSONObject*>(JSONArray->Items[i]);
		if (JSONObject)
		{
			TJSONValue* JSONObjectId = JSONObject->GetValue("id");
			TJSONValue* JSONObjectClave = JSONObject->GetValue("clave");
			TJSONValue* JSONObjectDescr = JSONObject->GetValue("descr");

			if (JSONObjectId && JSONObjectClave && JSONObjectDescr)
			{
				Objeto4Combo* m4c = ToObject(JSONObject);
				//combobox->AddItem(JSONObjectClave->Value(), m4c);
			}
		}
	}
}
//---------------------------------------------------------------------------

