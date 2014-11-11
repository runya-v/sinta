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

//            std::string absolute_path = boost::filesystem::system_complete(boost::filesystem::path(".")).string();
//            new RegionsCreator(absolute_path, contents, menu);
//
            Wt::WVBoxLayout* layout = new Wt::WVBoxLayout();

            Wt::WHBoxLayout* hlayout = new Wt::WHBoxLayout(this->root());
            //hlayout->addWidget(contents, 1);
//
//            vlayout->addWidget(new Wt::WText(Wt::WString::tr("Header")), 0);
//            vlayout->addLayout(hlayout, 1);
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
