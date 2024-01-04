//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Grid.hpp>
#include <FMX.Grid.Style.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.ScrollBox.hpp>
#include <FMX.Types.hpp>
#include <System.Rtti.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Edit.hpp>
#include <FMX.Memo.hpp>
#include <FMX.Memo.Types.hpp>
#include <FMX.Skia.hpp>
#include <System.Skia.hpp>
#include <Data.Bind.Components.hpp>
#include <Data.Bind.ObjectScope.hpp>
#include <Data.DB.hpp>
#include <FireDAC.Comp.Client.hpp>
#include <FireDAC.Comp.DataSet.hpp>
#include <FireDAC.DApt.Intf.hpp>
#include <FireDAC.DatS.hpp>
#include <FireDAC.Phys.Intf.hpp>
#include <FireDAC.Stan.Error.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Stan.Option.hpp>
#include <FireDAC.Stan.Param.hpp>
#include <REST.Client.hpp>
#include <REST.Types.hpp>
//---------------------------------------------------------------------------
class TFrame1 : public TFrame
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TStringGrid *StringGrid;
	TPanel *Panel2;
	TPanel *Panel3;
	TLabel *LabelId;
	TPanel *Panel4;
	TGridPanelLayout *GridPanelLayout1;
	TButton *ButtonNew;
	TButton *ButtonEdit;
	TButton *ButtonSave;
	TButton *ButtonDelete;
	TButton *ButtonClose;
	TPanel *Panel5;
	TLabel *LabelClave;
	TLabel *LabelDescr;
	TEdit *EditClave;
	TMemo *MemoDescr;
	TLabel *LabelMsg;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label1;
	TLabel *LabelTitulo;
	TStringColumn *StringColumn1;
	TStringColumn *StringColumn2;
	TStringColumn *StringColumn3;
	void __fastcall ButtonNewClick(TObject *Sender);
	void __fastcall ButtonCloseClick(TObject *Sender);
	void __fastcall StringGridSelectCell(TObject *Sender, const int ACol, const int ARow,
          bool &CanSelect);
	void __fastcall ButtonSaveClick(TObject *Sender);
	void __fastcall ButtonDeleteClick(TObject *Sender);
	void __fastcall ButtonEditClick(TObject *Sender);
private:	// User declarations
	String baseurl = "";
	String resource = "";
	String titulo = "";
	void PopulateStringGrid();
	void NewRecord();
	void EditRecord();
	void UpdateRecord();
	void CreateRecord();
	void DeleteRecord();


public:		// User declarations
	__fastcall TFrame1(TComponent* Owner, String baseurl, String resource, String titulo);
};
//---------------------------------------------------------------------------
extern PACKAGE TFrame1 *Frame1;
//---------------------------------------------------------------------------
#endif
