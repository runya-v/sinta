/*!
 * \brief  Модуль моделирующий Светодиот инидикации состояния.
 * \author Rostislav Velichko.
 * \date   09.11.2014
 */

#include <string>

#include <Wt/WContainerWidget>


namespace Web {

    class LightDiode
        : public Wt::WContainerWidget
    {
    public:
        LightDiode(const std::string &text);
    };
}
