/*!
 * \brief  Web приложение реализующее органы управления сварочным аппаратом.
 * \author Rostislav Velichko.
 * \date   09.11.2014
 */


#include <iostream>

#include <boost/filesystem.hpp>

#include <Wt/WContainerWidget>
#include <Wt/WApplication>
#include <Wt/WProgressBar>
#include <Wt/WComboBox>
#include <Wt/WText>
#include <Wt/WString>
#include <Wt/WMenu>
#include <Wt/WLocalizedStrings>
#include <Wt/WHBoxLayout>
#include <Wt/WVBoxLayout>
#include <Wt/WOverlayLoadingIndicator>

#include "IndicatorPannel.hpp"
#include "PotentiometersPannel.hpp"


namespace Web {

    class WelderApplication : public Wt::WApplication {
    public:
        WelderApplication(const Wt::WEnvironment& env)
            : Wt::WApplication(env)
        {
            this->messageResourceBundle().use(this->appRoot() + "rus_locale");
            this->useStyleSheet(this->appRoot() + "main.css");
            this->setTitle(Wt::WString::tr("Title"));

            Wt::WApplication *app = Wt::WApplication::instance();
            app->setLoadingIndicator(new Wt::WOverlayLoadingIndicator());
            app->styleSheet().addRule("body", "margin: 0px");

            Wt::WVBoxLayout *vlayout = new Wt::WVBoxLayout(this->root());
            vlayout->addWidget(new IndicatorPannel(), 0);
            vlayout->addWidget(new PotentiometersPannel(), 1);
        }
    };


    //! \ brief Функция генерации web приложения
    Wt::WApplication* CreateApp(const Wt::WEnvironment& env) {
        return new WelderApplication(env);
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// Пример запуска: ./companyes-web --docroot . --http-address 0.0.0.0 --http-port=8080
int main(int argc, char **argv) {
    return Wt::WRun(argc, argv, Web::CreateApp);
}
