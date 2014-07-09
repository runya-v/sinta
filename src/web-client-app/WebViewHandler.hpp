/*!
 * \brief  Класс реализующий описатель браузера.
 * \author Rostislav Velichko. e: rostislav.vel@gmail.com
 * \date   09.07.2014
 */

#pragma once

#include <list>

#include <cef_client.h>


namespace webv {

	class WebViewHandler 
		: public CefClient
        , public CefDisplayHandler
        , public CefLifeSpanHandler
        , public CefLoadHandler
	{
		IMPLEMENT_REFCOUNTING(WebViewHandler)

		typedef std::list<CefRefPtr<CefBrowser>> BrowserList;
		
		BrowserList _browser_list;
		bool _is_closing;

	public:
		static WebViewHandler* getInstance();

		WebViewHandler();
		virtual ~WebViewHandler();

		// CefClient methods:
		virtual CefRefPtr<CefDisplayHandler> GetDisplayHandler();
		virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler();
		virtual CefRefPtr<CefLoadHandler> GetLoadHandler();

		// CefDisplayHandler methods:
		virtual void OnTitleChange(CefRefPtr<CefBrowser> browser, const CefString &title);

		// CefLifeSpanHandler methods:
		virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser);
		virtual bool DoClose(CefRefPtr<CefBrowser> browser);
		virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser);

		// CefLoadHandler methods:
		virtual void OnLoadError(
			CefRefPtr<CefBrowser> browser,
			CefRefPtr<CefFrame> frame,
			ErrorCode error_code,
			const CefString &error_text,
			const CefString &failed_url);

		// Request that all existing browser windows close.
		void CloseAllBrowsers(bool force_close);

		bool IsClosing() const;
	};
}
