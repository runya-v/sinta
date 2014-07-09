/*!
 * \brief  Класс реализующий отображения окна и веб страници в нём.
 * \author Rostislav Velichko. e: rostislav.vel@gmail.com
 * \date   09.07.2014
 */

#pragma once

#include <cef_app.h>


namespace webv {

	class WebView 
		: public CefApp
        , public CefBrowserProcessHandler 
    {
		IMPLEMENT_REFCOUNTING(WebView)
		
	public:
		WebView();
		virtual ~WebView();
		
		virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler();
		virtual void OnContextInitialized();
	};
}

