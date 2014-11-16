/*!
 * \brief  Модуль моделирующий LED индекатор.
 * \author Rostislav Velichko.
 * \date   09.11.2014
 */

#include <string>

#include <Wt/WContainerWidget>
#include <Wt/WTable>


namespace Web {
    class LcdIndicator
        : public Wt::WContainerWidget
    {
        Wt::WTable *_symbols_table;

    public:
        LcdIndicator();

        void setText(int row, int column, std::string &text);
    };
}
