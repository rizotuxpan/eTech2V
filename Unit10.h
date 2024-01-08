//---------------------------------------------------------------------------

#ifndef Unit10H
#define Unit10H
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
class TFrame10 : public TFrame1
{
__published:	// IDE-managed Components
	TStringColumn *StringColumn4;
	TStringColumn *StringColumn5;
	TLabel *LabelMarca;
	TComboBox *ComboBoxMarca;
	TLabel *LabelMarcaDescr;
	TLabel *LabelTipo;
	TComboBox *ComboBoxTipo;
	TLabel *LabelTipoDescr;
	void __fastcall ButtonCloseClick(TObject *Sender);
	void __fastcall StringGridSelectCell(TObject *Sender, const int ACol, const int ARow,
          bool &CanSelect);
	void __fastcall ButtonDeleteClick(TObject *Sender);
	void __fastcall ButtonNewClick(TObject *Sender);
	void __fastcall ButtonEditClick(TObject *Sender);
	void __fastcall ButtonSaveClick(TObject *Sender);
	void __fastcall ComboBoxMarcaChange(TObject *Sender);
	void __fastcall ComboBoxTipoChange(TObject *Sender);
private:	// User declarations
	String baseurl="";
	String resource="";
	String titulo="";
	void PopulateStringGrid();
	void RellenarComboBox(TComboBox *ComboBox, const UnicodeString &resource);
	void NewRecord();
	void DeleteRecord();
	void UpdateRecord();
    void EditRecord();
    void CreateRecord();
public:		// User declarations
	__fastcall TFrame10(TComponent* Owner, String baseurl, String resource, String titulo);
};
//---------------------------------------------------------------------------
extern PACKAGE TFrame10 *Frame10;
//---------------------------------------------------------------------------
#endif
