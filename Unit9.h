//---------------------------------------------------------------------------

#ifndef Unit9H
#define Unit9H
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
#include <FMX.ListBox.hpp>
#include <FMX.Memo.hpp>
#include <FMX.Memo.Types.hpp>
#include <FMX.ScrollBox.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <System.Rtti.hpp>
//---------------------------------------------------------------------------
class TFrame9 : public TFrame1
{
__published:	// IDE-managed Components
	TComboBox *ComboBoxMarca;
	TComboBox *ComboBoxTipo;
	TLabel *LabelMarca;
	TLabel *LabelTipo;
	TLabel *LabelMarcaDescr;
	TLabel *LabelTipoDescr;
	TStringColumn *StringColumn4;
	TStringColumn *StringColumn5;
	void __fastcall ButtonCloseClick(TObject *Sender);
	void __fastcall ComboBoxMarcaChange(TObject *Sender);
	void __fastcall ComboBoxTipoChange(TObject *Sender);
	void __fastcall ButtonSaveClick(TObject *Sender);
	void __fastcall ButtonNewClick(TObject *Sender);
	void __fastcall StringGridSelectCell(TObject *Sender, const int ACol, const int ARow,
          bool &CanSelect);
	void __fastcall ButtonEditClick(TObject *Sender);
private:	// User declarations
	String baseurl  = "";
	String resource = "";
	String titulo   = "";
    void PopulateStringGrid();
	void RellenarComboBox(TComboBox *ComboBox, const UnicodeString &resource);
    void NewRecord();
	void CreateRecord();
    void EditRecord();
public:		// User declarations
	__fastcall TFrame9(TComponent* Owner, String baseurl, String resource, String titulo);
};
//---------------------------------------------------------------------------
extern PACKAGE TFrame9 *Frame9;
//---------------------------------------------------------------------------
#endif
