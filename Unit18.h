//---------------------------------------------------------------------------

#ifndef Unit18H
#define Unit18H
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
//---------------------------------------------------------------------------
class TFrame18 : public TFrame1
{
__published:	// IDE-managed Components
private:	// User declarations
	String baseurl = "";
	String resource = "";
    String titulo = "";
public:		// User declarations
	__fastcall TFrame18(TComponent* Owner, String baseurl, String resource, String titulo);
};
//---------------------------------------------------------------------------
extern PACKAGE TFrame18 *Frame18;
//---------------------------------------------------------------------------
#endif
