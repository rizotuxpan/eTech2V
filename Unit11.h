//---------------------------------------------------------------------------

#ifndef Unit11H
#define Unit11H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <FMX.Grid.hpp>
#include <FMX.Grid.Style.hpp>
#include <FMX.ScrollBox.hpp>
#include <System.Rtti.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.Edit.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.ComboTrackBar.hpp>
#include <FMX.EditBox.hpp>
#include <FMX.NumberBox.hpp>
#include <FMX.Objects.hpp>
//---------------------------------------------------------------------------
class TFrame11 : public TFrame
{
__published:	// IDE-managed Components
	TPanel *Panel4;
	TPanel *Panel1;
	TPanel *Panel2;
	TPanel *Panel3;
	TPanel *Panel5;
	TStringGrid *StringGrid;
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
	TStringColumn *StringColumn1;
	TStringColumn *StringColumn2;
	TStringColumn *StringColumn3;
	TStringColumn *StringColumn4;
	TCurrencyColumn *CurrencyColumn1;
	TPanel *Panel7;
	TStringColumn *StringColumn5;
	TStringColumn *StringColumn6;
	TStringColumn *StringColumn7;
	TStringColumn *StringColumn8;
	TStringColumn *StringColumn9;
	TLabel *LabelId;
	TLabel *Tipo;
	TLabel *Label7;
	TLabel *Label8;
	TComboBox *ComboBoxMarca;
	TComboBox *ComboBoxModelo;
	TComboBox *ComboBoxTipo;
	TEdit *EditSerie;
	TLabel *Label2;
	TLabel *Label9;
	TComboBox *ComboBox1;
	TLabel *Label10;
	TComboBox *ComboBox2;
	TImage *Image1;
	TLabel *LabelMsg;
	TStringColumn *StringColumn10;
	TStringColumn *StringColumn11;
	void __fastcall ButtonCloseClick(TObject *Sender);
	void __fastcall ComboBoxMarcaChange(TObject *Sender);
	void __fastcall ComboBoxTipoChange(TObject *Sender);
	void __fastcall ButtonNewClick(TObject *Sender);
	void __fastcall ButtonSaveClick(TObject *Sender);
	void __fastcall StringGridSelectCell(TObject *Sender, const int ACol, const int ARow,
          bool &CanSelect);
	void __fastcall ButtonDeleteClick(TObject *Sender);
	void __fastcall ButtonEditClick(TObject *Sender);
private:	// User declarations
	String baseurl  = "";
	String resource = "";
	String titulo   = "";
	void PopulateStringGrid();
	void RellenarComboBoxMarca(TComboBox *ComboBox, const UnicodeString &resource);
	void RellenarComboBoxTipo(TComboBox *ComboBox, const UnicodeString &resource, int marca_id);
	void RellenarComboBoxModelo(TComboBox *ComboBox, const UnicodeString &resource, int marca_id, int tipo_id);
	void CreateRecord();
	void DeleteRecord();
    void UpdateRecord();
	void eliminarFila(TStringGrid* grid, int numeroFila);
public:		// User declarations
	__fastcall TFrame11(TComponent* Owner, String baseurl, String resource, String titulo);
};
//---------------------------------------------------------------------------
extern PACKAGE TFrame11 *Frame11;
//---------------------------------------------------------------------------
#endif
