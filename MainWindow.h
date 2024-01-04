//---------------------------------------------------------------------------

#ifndef MainWindowH
#define MainWindowH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <FMX.TabControl.hpp>
#include <FMX.Skia.hpp>
#include <System.Skia.hpp>
#include <FMX.ImgList.hpp>
#include <System.ImageList.hpp>
#include <FMX.Menus.hpp>

#include <IniFiles.hpp>
#include "Unit1.h"
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TStatusBar *StatusBarMain;
	TPanel *PanelMain;
	TMenuBar *Menu;
	TMenuItem *MenuCatalogos;
	TMenuItem *MenuCatalogosSwitches;
	TMenuItem *MenuCatalogosSwitchesMarcas;
	void __fastcall MenuCatalogosSwitchesMarcasClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
	String baseurl = "";
	String resource = "";
	String SwitchModeloMarca = "";
    String SwitchModeloTipo = "";
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
