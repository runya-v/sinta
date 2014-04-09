#include "MimeTypes.hpp"


using namespace http_server;


struct Mapping {
	const char *extension;
	const char *mime_type;
}


mappings[] = {
	{ "gif",  "image/gif" },
	{ "htm",  "text/html" },
	{ "html", "text/html" },
	{ "css",  "text/css" },
	{ "jpg",  "image/jpeg" },
	{ "png",  "image/png" },
	{ 0, 0 } // Marks end of list.
};


std::string MimeTypes::ExtensionToType(const std::string& extension) {
	for (Mapping *m = mappings; m->extension; ++m) {
		if (m->extension == extension) {
			return m->mime_type;
		}
	}
	return "text/plain";
}
