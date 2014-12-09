#include <Wt/WVBoxLayout>
#include <Wt/WString>
#include <Wt/WText>
#include <Wt/WCssDecorationStyle>
#include <Wt/WBorder>
#include <Wt/WColor>
#include <Wt/WPushButton>

#include "LightDiode.hpp"
#include "DynamikParamsPannel.hpp"

using namespace Web;


DynamikParamsPannel::DynamikParamsPannel() {
    this->setStyleClass("welding-type");

    Wt::WVBoxLayout *vlayout = new Wt::WVBoxLayout(this);
	vlayout->setContentsMargins(5, 5, 5, 5);
    vlayout->addWidget(new Wt::WText(Wt::WString::tr("DynamikParamsPannel")));

    vlayout->addWidget(new LightDiode("indication_drossel_dynamik_parameter"));
    vlayout->addWidget(new LightDiode("indication_gas_purge_time_dynamik_parameter"));
    vlayout->addWidget(new LightDiode("indication_dot_welding_time_dynamik_parameter"));
    vlayout->addWidget(new LightDiode("indication_pulse_time_dynamik_parameter"));
    Wt::WPushButton *button = new Wt::WPushButton(Wt::WString::tr("dynamik_params_button"));
    button->clicked().connect(std::bind([=] () {
        //canvas->clear();
    }));
    vlayout->addWidget(button);
}
