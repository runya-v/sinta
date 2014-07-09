#include "WebViewHandler.hpp"
#include "WebView.hpp"


using namespace webv;


WebView::WebView()
{}


WebView::~WebView()
{}


CefRefPtr<CefBrowserProcessHandler> WebView::GetBrowserProcessHandler() {
	return this;
}


void WebView::OnContextInitialized() {
	CefCurrentlyOn(TID_UI);

	// Check if a "--url=" value was provided via the command-line. If so, use that instead of the default URL.
	CefRefPtr<CefCommandLine> command_line = CefCommandLine::GetGlobalCommandLine();
	std::string url = command_line->GetSwitchValue("url");

	if (url.empty()) {
		url = "www.ya.ru";
	}

	// Create the first browser window.
	CefWindowInfo window_info;
	CefRefPtr<WebViewHandler> handler(new WebViewHandler());
	CefBrowserSettings browser_settings;
	CefBrowserHost::CreateBrowser(window_info, handler.get(), url, browser_settings, nullptr);
}
