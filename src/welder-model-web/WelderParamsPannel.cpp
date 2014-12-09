#include <Wt/WVBoxLayout>
#include <Wt/WString>
#include <Wt/WText>
#include <Wt/WCssDecorationStyle>
#include <Wt/WBorder>
#include <Wt/WColor>
#include <Wt/WPushButton>

#include "LightDiode.hpp"
#include "WelderParamsPannel.hpp"

using namespace Web;


WelderParamsPannel::WelderParamsPannel() {
    this->setStyleClass("welder-params");

    Wt::WVBoxLayout *vlayout = new Wt::WVBoxLayout(this);
    vlayout->setContentsMargins(5, 5, 5, 5);
    vlayout->addWidget(new Wt::WText(Wt::WString::tr("WelderParamsPannel")));

    vlayout->addWidget(new LightDiode("indication_volts"));
    vlayout->addWidget(new LightDiode("indication_ampers"));
    vlayout->addWidget(new LightDiode("indication_thickness"));
    vlayout->addWidget(new LightDiode("indication_feed_speed"));
    Wt::WPushButton *button = new Wt::WPushButton(Wt::WString::tr("welder_params_button"));
    button->clicked().connect(std::bind([=] () {
        //canvas->clear();
    }));
    vlayout->addWidget(button);
}
