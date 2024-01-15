//---------------------------------------------------------------------------

#ifndef Unit18H
#define Unit18H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Edit.hpp>
#include <FMX.EditBox.hpp>
#include <FMX.Grid.hpp>
#include <FMX.Grid.Style.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.NumberBox.hpp>
#include <FMX.Objects.hpp>
#include <FMX.ScrollBox.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <System.Rtti.hpp>
#include <FMX.Memo.hpp>
#include <FMX.Memo.Types.hpp>
//---------------------------------------------------------------------------
class TFrame18 : public TFrame
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TPanel *Panel6;
	TGridPanelLayout *GridPanelLayout1;
	TButton *ButtonNew;
	TButton *ButtonEdit;
	TButton *ButtonSave;
	TButton *ButtonDelete;
	TButton *ButtonClose;
	TLabel *LabelButtonEdit;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label1;
	TPanel *Panel2;
	TPanel *Panel3;
	TLabel *LabelId;
	TLabel *Label7;
	TLabel *Label8;
	TComboBox *ComboBoxMarca;
	TComboBox *ComboBoxModelo;
	TEdit *EditSerie;
	TLabel *Label2;
	TLabel *LabelMsg;
	TLabel *LabelDescripcion;
	TPanel *Panel5;
	TStringGrid *StringGrid;
	TStringColumn *StringColumn1;
	TStringColumn *StringColumn2;
	TStringColumn *StringColumn3;
	TStringColumn *StringColumn4;
	TStringColumn *StringColumn5;
	TStringColumn *StringColumn7;
	TStringColumn *StringColumn10;
	TStringColumn *StringColumn11;
	TStringColumn *StringColumn9;
	TPanel *Panel4;
	TPanel *Panel7;
	TLabel *Label9;
	TComboBox *ComboBox1;
	TLabel *Label10;
	TComboBox *ComboBox2;
	TImage *Image1;
	TMemo *MemoDescr;
	void __fastcall ButtonCloseClick(TObject *Sender);
	void __fastcall StringGridSelectCell(TObject *Sender, const int ACol, const int ARow,
          bool &CanSelect);
	void __fastcall ComboBoxMarcaChange(TObject *Sender);
	void __fastcall ButtonNewClick(TObject *Sender);
	void __fastcall ButtonEditClick(TObject *Sender);
	void __fastcall ButtonDeleteClick(TObject *Sender);
	void __fastcall ButtonSaveClick(TObject *Sender);
private:	// User declarations
	String baseurl  = "";
	String resource = "";
	String titulo   = "";
	void PopulateStringGrid();
	void RellenarComboBoxMarca(TComboBox *ComboBox, const UnicodeString &resource);
	void RellenarComboBoxModelo(TComboBox *ComboBox, const UnicodeString &resource, int marca_id);
	void CreateRecord();
	void DeleteRecord();
    void UpdateRecord();
	void eliminarFila(TStringGrid* grid, int numeroFila);
public:		// User declarations
	__fastcall TFrame18(TComponent* Owner, String baseurl, String resource, String titulo);
};
//---------------------------------------------------------------------------
extern PACKAGE TFrame18 *Frame18;
//---------------------------------------------------------------------------
#endif
