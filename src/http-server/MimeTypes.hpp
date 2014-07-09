/*!
 * \brief  ASIO сервер обслуживающий TCP соединения.
 * \author Rostislav Velichko. e: rostislav.vel@gmail.com
 * \date   02.03.2013
 */

#pragma once

#include <string>


namespace http_server {
	/// Convert a file extension into a MIME type.
	
	class MimeTypes {
	public:
		static std::string ExtensionToType(const std::string& extension);
	};
} // namespace http_server
