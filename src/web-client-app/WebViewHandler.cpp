#include <string>
#include <sstream>

#include <gtk/gtk.h>

#include <cef_runnable.h>
#include <cef_task.h>
#include <cef_app.h>

#include "WebViewHandler.hpp"


using namespace webv;

namespace {
	WebViewHandler *_instance = nullptr;
}


WebViewHandler* WebViewHandler::getInstance() {
	return _instance;
}


WebViewHandler::WebViewHandler() 
	: _is_closing(false)
{
	_instance = this;
}


WebViewHandler::~WebViewHandler() {
	_instance = nullptr;
}


// CefClient methods:
CefRefPtr<CefDisplayHandler> WebViewHandler::GetDisplayHandler() {
	return this;
}


CefRefPtr<CefLifeSpanHandler> WebViewHandler::GetLifeSpanHandler() {
	return this;
}


CefRefPtr<CefLoadHandler> WebViewHandler::GetLoadHandler() {
	return this;
}


void WebViewHandler::OnTitleChange(CefRefPtr<CefBrowser> browser, const CefString &title) {
	CefCurrentlyOn(TID_UI);
	GtkWidget *window = gtk_widget_get_ancestor(GTK_WIDGET(browser->GetHost()->GetWindowHandle()), GTK_TYPE_WINDOW);
	gtk_window_set_title(GTK_WINDOW(window), std::string(title).c_str());
}


void WebViewHandler::OnAfterCreated(CefRefPtr<CefBrowser> browser) {
	CefCurrentlyOn(TID_UI);
	_browser_list.push_back(browser);
}


bool WebViewHandler::DoClose(CefRefPtr<CefBrowser> browser) {
	CefCurrentlyOn(TID_UI);

	if (_browser_list.size() == 1) {
		_is_closing = true;
	}
	return false;
}


void WebViewHandler::OnBeforeClose(CefRefPtr<CefBrowser> browser) {
	CefCurrentlyOn(TID_UI);
	typedef BrowserList::iterator BrowserListIter;
	
	for (BrowserListIter bit = _browser_list.begin(); bit != _browser_list.end(); ++bit) {
		if ((*bit)->IsSame(browser)) {
			_browser_list.erase(bit);
			break;
		}
	}

	if (_browser_list.empty()) {
		CefQuitMessageLoop();
	}
}


void WebViewHandler::OnLoadError(
	CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	ErrorCode error_code,
	const CefString &error_text,
	const CefString &failed_url) {
	CefCurrentlyOn(TID_UI);

	if (ERR_ABORTED != error_code) {
		std::stringstream ss;
		ss << "<html><body bgcolor=\"white\">";
		ss << "<h2>Failed to load URL " << std::string(failed_url) << " with error " << std::string(error_text) << " (" << error_code << ").</h2>";
		ss << "</body></html>";
		frame->LoadString(ss.str(), failed_url);
	}
}


void WebViewHandler::CloseAllBrowsers(bool force_close) {
	if (not CefCurrentlyOn(TID_UI)) {
		CefPostTask(TID_UI, NewCefRunnableMethod(this, &WebViewHandler::CloseAllBrowsers, force_close));
	}
	else if (not _browser_list.empty()) {
		typedef BrowserList::const_iterator BrowserListCiter;

		for (BrowserListCiter it = _browser_list.begin(); it != _browser_list.end(); ++it) {
			(*it)->GetHost()->CloseBrowser(force_close);
		}
	}
}


bool WebViewHandler::IsClosing() const {
	return _is_closing;
}
