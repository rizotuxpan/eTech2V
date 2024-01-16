//---------------------------------------------------------------------------

#ifndef Unit19H
#define Unit19H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.Edit.hpp>
#include <FMX.Grid.hpp>
#include <FMX.Grid.Style.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.Memo.hpp>
#include <FMX.Memo.Types.hpp>
#include <FMX.Objects.hpp>
#include <FMX.ScrollBox.hpp>
#include <System.Rtti.hpp>
#include <FMX.TabControl.hpp>
//---------------------------------------------------------------------------
class TFrame19 : public TFrame
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
	TTabControl *TabControl1;
	TTabItem *TabItem1;
	TTabItem *TabItem2;
	TTabItem *TabItem3;
	TTabItem *Gabinetes;
	TTabItem *TabItem5;
	TPanel *Panel8;
	TPanel *Panel9;
	TEdit *Edit1;
	TStringGrid *StringGrid1;
	TSplitter *Splitter1;
	void __fastcall ButtonCloseClick(TObject *Sender);
private:	// User declarations
	String baseurl = "";
	String resource = "";
    String titulo = "";
public:		// User declarations
	__fastcall TFrame19(TComponent* Owner, String baseurl, String resource, String titulo);
};
//---------------------------------------------------------------------------
extern PACKAGE TFrame19 *Frame19;
//---------------------------------------------------------------------------
#endif
