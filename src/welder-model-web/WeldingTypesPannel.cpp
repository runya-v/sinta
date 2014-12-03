#include <Wt/WVBoxLayout>
#include <Wt/WString>
#include <Wt/WText>
#include <Wt/WCssDecorationStyle>
#include <Wt/WBorder>
#include <Wt/WColor>
#include <Wt/WPushButton>

#include "LightDiode.hpp"
#include "WeldingTypesPannel.hpp"

using namespace Web;


WeldingTypesPannel::WeldingTypesPannel() {
    this->setStyleClass("welding-type");

    Wt::WVBoxLayout *vlayout = new Wt::WVBoxLayout(this);
    vlayout->addWidget(new Wt::WText(Wt::WString::tr("WeldingTypesPannel")));
    Wt::WPushButton *button = new Wt::WPushButton(Wt::WString::tr("gas_check_button"));
    button->clicked().connect(std::bind([=] () {
        //canvas->clear();
    }));
    vlayout->addWidget(button);
    vlayout->addWidget(new LightDiode("indication_standart_welding"));
    vlayout->addWidget(new LightDiode("indication_pulse_welding"));
    button = new Wt::WPushButton(Wt::WString::tr("welding_type_button"));
    button->clicked().connect(std::bind([=] () {
        //canvas->clear();
    }));
    vlayout->addWidget(button);
}
