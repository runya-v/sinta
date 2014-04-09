/*!
 * \brief  Класс реализации функции загрузки содержимого текстового файла.
 * \author Rostislav Velichko.
 * \date   11.01.2014
 */

// Пример использования в шаблоне: <TMPL_var TEXT_FILE_LOAD("full path")>

#include <ctpp2/CTPP2VMSyscall.hpp>
#include <ctpp2/CDT.hpp>


namespace tmplt {

    class TextFileLoader 
        : public CTPP::SyscallHandler
    {
    public:
		TextFileLoader();
        virtual ~TextFileLoader() throw();

        virtual CCHAR_P GetName() const;
        
	private: 
        virtual INT_32 Handler(CTPP::CDT *arguments, const UINT_32 arg_num, CTPP::CDT &ret_val, CTPP::Logger&);
    };
}
