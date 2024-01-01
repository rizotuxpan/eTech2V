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
//---------------------------------------------------------------------------
class TFrame1 : public TFrame
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TStringGrid *StringGrid;
	TPanel *Panel2;
	TPanel *Panel3;
	TLabel *ID;
	TPanel *Panel4;
	TGridPanelLayout *GridPanelLayout1;
	TButton *ButtonNuevo;
	TButton *ButtonEditar;
	TButton *ButtonGuardar;
	TButton *ButtonBorrar;
	TButton *ButtonCerrar;
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
	TLabel *Label6;
	void __fastcall Panel2Resized(TObject *Sender);
private:	// User declarations
    bool resizing = false;
public:		// User declarations
	__fastcall TFrame1(TComponent* Owner, String parametro);
};
//---------------------------------------------------------------------------
extern PACKAGE TFrame1 *Frame1;
//---------------------------------------------------------------------------
#endif
