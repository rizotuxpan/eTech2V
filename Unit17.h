//---------------------------------------------------------------------------

#ifndef Unit17H
#define Unit17H
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
#include <FMX.EditBox.hpp>
#include <FMX.NumberBox.hpp>
//---------------------------------------------------------------------------
class TFrame17 : public TFrame1
{
__published:	// IDE-managed Components
	TLabel *Label2;
	TComboBox *ComboBoxMaterial;
	TLabel *LabelMaterialDescr;
	TLabel *Label6;
	TNumberBox *EditAltura;
	TIntegerColumn *IntegerColumn1;
	TStringColumn *StringColumn4;
	TStringColumn *StringColumn5;
	TStringColumn *StringColumn6;
	void __fastcall ButtonCloseClick(TObject *Sender);
	void __fastcall StringGridSelectCell(TObject *Sender, const int ACol, const int ARow,
          bool &CanSelect);
	void __fastcall ButtonNewClick(TObject *Sender);
	void __fastcall ButtonEditClick(TObject *Sender);
	void __fastcall ButtonDeleteClick(TObject *Sender);
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
	void DeleteRecord();
    void eliminarFila(TStringGrid* grid, int numeroFila);
public:		// User declarations
	__fastcall TFrame17(TComponent* Owner, String baseurl, String resource, String titulo);
};
//---------------------------------------------------------------------------
extern PACKAGE TFrame17 *Frame17;
//---------------------------------------------------------------------------
#endif
