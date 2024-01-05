//---------------------------------------------------------------------------

#include <fmx.h>
#ifdef _WIN32
#include <tchar.h>
#endif
#pragma hdrstop
#include <System.StartUpCopy.hpp>
//---------------------------------------------------------------------------
USEFORM("Unit4.cpp", Frame4); /* TFrame: File Type */
USEFORM("Unit5.cpp", Frame5); /* TFrame: File Type */
USEFORM("Unit6.cpp", Frame6); /* TFrame: File Type */
USEFORM("Unit7.cpp", Frame7); /* TFrame: File Type */
USEFORM("Unit8.cpp", Frame8); /* TFrame: File Type */
USEFORM("Unit3.cpp", Frame3); /* TFrame: File Type */
USEFORM("MainWindow.cpp", Form1);
USEFORM("Unit1.cpp", Frame1); /* TFrame: File Type */
USEFORM("Unit2.cpp", Frame2); /* TFrame: File Type */
USEFORM("Unit9.cpp", Frame9); /* TFrame: File Type */
//---------------------------------------------------------------------------
extern "C" int FMXmain()
{
	try
	{
		Application->Initialize();
		Application->CreateForm(__classid(TForm1), &Form1);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
