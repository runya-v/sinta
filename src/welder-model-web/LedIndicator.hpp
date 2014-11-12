/*!
 * \brief  Модуль моделирующий LED индекатор.
 * \author Rostislav Velichko.
 * \date   09.11.2014
 */


#include <Wt/WContainerWidget>
#include <Wt/WTable>


namespace Web {
    class LedIndicator
        : public Wt::WContainerWidget
    {
        Wt::WTable *_symbols_table;

    public:
        LedIndicator();
    };
}
