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
#include "Unit2.h"
#include "Unit3.h"
#include "Unit4.h"
#include "Unit5.h"
#include "Unit6.h"
#include "Unit7.h"
#include "Unit8.h"
#include "Unit9.h"
#include "Unit10.h"
#include "Unit11.h"

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
	TMenuItem *MenuCatalogosSwitchesTipos;
	TMenuItem *MenuCatalogosRadios;
	TMenuItem *MenuCatalogosRadiosMarcas;
	TMenuItem *MenuArchivo;
	TMenuItem *MenuArchivoSalir;
	TMenuItem *MenuCatalogosCamaras;
	TMenuItem *MenuCatalogosCamarasMarcas;
	TMenuItem *MenuCatalogosCamarasTipos;
	TMenuItem *MenuCatalogosGabinete;
	TMenuItem *MenuCatalogosPMIs;
	TMenuItem *MenuCatalogosArcos;
	TMenuItem *MenuCatalogosPMIPostesMaterial;
	TMenuItem *MenuCatalogosArcosEstructuras;
	TMenuItem *MenuCatalogosCamarasSep1;
	TMenuItem *MenuCatalogosCamarasModelos;
	TMenuItem *MenuCatalogosSwitchesSep1;
	TMenuItem *MenuCatalogosSwitchesModelos;
	TMenuItem *MenuCatalogosCamarasSep2;
	TMenuItem *MenuCatalogosCamarasCamaras;
	void __fastcall MenuCatalogosSwitchesMarcasClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall MenuCatalogosSwitchesTiposClick(TObject *Sender);
	void __fastcall MenuCatalogosRadiosMarcasClick(TObject *Sender);
	void __fastcall MenuArchivoSalirClick(TObject *Sender);
	void __fastcall MenuCatalogosCamarasMarcasClick(TObject *Sender);
	void __fastcall MenuCatalogosCamarasTiposClick(TObject *Sender);
	void __fastcall MenuCatalogosGabineteClick(TObject *Sender);
	void __fastcall MenuCatalogosPMIPostesMaterialClick(TObject *Sender);
	void __fastcall MenuCatalogosArcosEstructurasClick(TObject *Sender);
	void __fastcall MenuCatalogosCamarasModelosClick(TObject *Sender);
	void __fastcall MenuCatalogosSwitchesModelosClick(TObject *Sender);
	void __fastcall MenuCatalogosCamarasCamarasClick(TObject *Sender);
private:	// User declarations
	String baseurl = "";
	String resource = "";
	String SwitchModeloMarca = "";
	String SwitchModeloTipo = "";
	String RadioModeloMarca = "";
	String CamaraModeloMarca = "";
	String CamaraModeloTipo = "";
	String Gabinete = "";
    String PmiPosteMaterial = "";
	String ArcoEstructura = "";
	String CamaraModelo = "";
	String SwitchModelo = "";
    String Camara = "";
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
   void EnableMenu(bool enable);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
