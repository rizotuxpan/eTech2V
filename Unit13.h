//---------------------------------------------------------------------------

#ifndef Unit13H
#define Unit13H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include "Unit1.h"
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Edit.hpp>
#include <FMX.Grid.hpp>
#include <FMX.Grid.Style.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.Memo.hpp>
#include <FMX.Memo.Types.hpp>
#include <FMX.ScrollBox.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <System.Rtti.hpp>
#include <FMX.ListBox.hpp>
//---------------------------------------------------------------------------
class TFrame13 : public TFrame1
{
__published:	// IDE-managed Components
	TComboBox *ComboBoxMarca;
	TLabel *Label2;
	TStringColumn *StringColumn4;
	TStringColumn *StringColumn5;
	void __fastcall ButtonCloseClick(TObject *Sender);
	void __fastcall StringGridSelectCell(TObject *Sender, const int ACol, const int ARow,
          bool &CanSelect);
	void __fastcall ButtonNewClick(TObject *Sender);
	void __fastcall ButtonEditClick(TObject *Sender);
	void __fastcall ButtonSaveClick(TObject *Sender);
private:	// User declarations
	String baseurl = "";
	String resource = "";
	String titulo = "";
	void PopulateStringGrid();
	void RellenarComboBoxMarca(TComboBox *ComboBox, const UnicodeString &resource);
	void NewRecord();
	void UpdateRecord();
    void CreateRecord();
public:		// User declarations
	__fastcall TFrame13(TComponent* Owner, String baseurl, String resource, String titulo);
};
//---------------------------------------------------------------------------
extern PACKAGE TFrame13 *Frame13;
//---------------------------------------------------------------------------
#endif
