#include <iostream>

#include <gtk/gtk.h>

#include "WebView.hpp"


using namespace webv;


//class Application {
//	int _argc; 
//	char **_argv;
//	int _result;
//	
//public:
//	Application(int argc, char**argv)
//		: _argc(argc)
//		, _argv(argv)
//	{
//		CefMainArgs main_args(argc, argv);
//		CefRefPtr<WebView> wv(new WebView);
//
//		_result = CefExecuteProcess(main_args, wv.get(), nullptr);
//
//		if (0 == _result) {
//			gtk_init(&argc, &argv);
//
//			CefSettings settings;
//			CefInitialize(main_args, settings, wv.get(), nullptr);
//			CefRunMessageLoop();
//		}
//	}
//	
//	~Application() {
//		CefShutdown();
//	}
//	
//	operator int () {
//		return _result;
//	}
//};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int main(int argc, char**argv) {
	CefMainArgs main_args(argc, argv);
	CefRefPtr<WebView> wv(new WebView);

	int result = CefExecuteProcess(main_args, wv.get(), nullptr);

	if (0 > result) {
		gtk_init(&argc, &argv);

		CefSettings settings;
		CefInitialize(main_args, settings, wv.get(), nullptr);
		CefRunMessageLoop();
		CefShutdown();
	}
	return result;
}
