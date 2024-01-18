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
#include <FMX.Maps.hpp>
#include <FMX.WebBrowser.hpp>
#include "FMX.TMSFNCCustomControl.hpp"
#include "FMX.TMSFNCGoogleMaps.hpp"
#include "FMX.TMSFNCGraphics.hpp"
#include "FMX.TMSFNCGraphicsTypes.hpp"
#include "FMX.TMSFNCMaps.hpp"
#include "FMX.TMSFNCTypes.hpp"
#include "FMX.TMSFNCUtils.hpp"
#include "FMX.TMSFNCWebBrowser.hpp"
#include "FMX.TMSFNCOpenLayers.hpp"
#include "FMX.TMSFNCMapsCommonTypes.hpp"
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
	TSplitter *Splitter1;
	TGridPanelLayout *GridPanelLayout2;
	TStringGrid *StringGrid1;
	TPanel *Panel8;
	TStringGrid *StringGrid2;
	TSpeedButton *SpeedButton1;
	TSpeedButton *SpeedButton2;
	TStringColumn *StringColumn6;
	TStringColumn *StringColumn8;
	TTabItem *TabItem4;
	TGridPanelLayout *GridPanelLayout3;
	TStringGrid *StringGrid3;
	TStringColumn *StringColumn12;
	TPanel *Panel9;
	TSpeedButton *SpeedButton3;
	TSpeedButton *SpeedButton4;
	TStringGrid *StringGrid4;
	TStringColumn *StringColumn13;
	TGridPanelLayout *GridPanelLayout4;
	TStringGrid *StringGrid5;
	TStringColumn *StringColumn14;
	TPanel *Panel10;
	TSpeedButton *SpeedButton5;
	TSpeedButton *SpeedButton6;
	TStringGrid *StringGrid6;
	TStringColumn *StringColumn15;
	TGridPanelLayout *GridPanelLayout5;
	TStringGrid *StringGrid7;
	TStringColumn *StringColumn16;
	TPanel *Panel11;
	TSpeedButton *SpeedButton7;
	TSpeedButton *SpeedButton8;
	TStringGrid *StringGrid8;
	TStringColumn *StringColumn17;
	TGridPanelLayout *GridPanelLayout6;
	TStringGrid *StringGrid9;
	TStringColumn *StringColumn18;
	TPanel *Panel12;
	TSpeedButton *SpeedButton9;
	TSpeedButton *SpeedButton10;
	TStringGrid *StringGrid10;
	TStringColumn *StringColumn19;
	TPanel *Panel13;
	TPanel *Panel14;
	TSplitter *Splitter2;
	TButton *Button1;
	TTMSFNCMaps *TMSFNCMaps1;
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
