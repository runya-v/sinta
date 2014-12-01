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
    namespace bfs = boost::filesystem;


    class WelderApplication : public Wt::WApplication {
    public:
        WelderApplication(const Wt::WEnvironment& env)
            : Wt::WApplication(env)
        {
            bfs::path abs_path = bfs::absolute(bfs::path(this->docRoot()));

            this->useStyleSheet((abs_path / "main.css").string());
            this->messageResourceBundle().use((abs_path / "rus_locale").string());
            this->setTitle(Wt::WString::tr("Title"));

            Wt::WApplication *app = Wt::WApplication::instance();
            app->setLoadingIndicator(new Wt::WOverlayLoadingIndicator());
            app->styleSheet().addRule("body", "margin: 0px");

            Wt::WVBoxLayout *vlayout = new Wt::WVBoxLayout();
            vlayout->addWidget(new IndicatorPannel(), 1);
            vlayout->addWidget(new PotentiometersPannel(), 1);

            Wt::WContainerWidget *container = new Wt::WContainerWidget(this->root());
            container->decorationStyle().setBorder(Wt::WBorder(Wt::WBorder::Solid, Wt::WBorder::Thin, Wt::WColor(0, 0, 0, 255)));
            container->setLayout(vlayout);
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
