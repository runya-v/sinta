#include <iostream>

#include <gtk/gtk.h>

#include "WebView.hpp"


using namespace webv;


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
