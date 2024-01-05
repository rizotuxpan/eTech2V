//---------------------------------------------------------------------------

#ifndef ComboBoxH
#define ComboBoxH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <System.JSON.hpp>
#include <REST.Client.hpp>

//---------------------------------------------------------------------------
class TDataModule10 : public TDataModule
{
__published:	// IDE-managed Components
private:	// User declarations
public:		// User declarations
	__fastcall TDataModule10(TComponent* Owner);
};

class Objeto4Combo : public TObject
{
  private:
	UnicodeString Id;
	UnicodeString Clave;
	UnicodeString Descr;
  public:
	Objeto4Combo(const UnicodeString &id, UnicodeString clave, UnicodeString descr) :
		Id(id),Clave(clave), Descr(descr)
	{
	}

	UnicodeString getId();
	UnicodeString getDescr();

	};

Objeto4Combo* ToObject(TJSONObject* jsonObject);

void PopulateComboBox(TComboBox* combobox, TRESTClient* client, TRESTRequest* request, TRESTResponse* response, UnicodeString getUrl);
//---------------------------------------------------------------------------
extern PACKAGE TDataModule10 *DataModule10;
//---------------------------------------------------------------------------
#endif
