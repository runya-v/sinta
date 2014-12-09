#include <Wt/WVBoxLayout>
#include <Wt/WString>
#include <Wt/WText>
#include <Wt/WCssDecorationStyle>
#include <Wt/WBorder>
#include <Wt/WColor>
#include <Wt/WPushButton>

#include "LightDiode.hpp"
#include "WorkModePannel.hpp"

using namespace Web;


WorkModePannel::WorkModePannel() {
    this->setStyleClass("welding-type");

    Wt::WVBoxLayout *vlayout = new Wt::WVBoxLayout(this);
    vlayout->setContentsMargins(5, 5, 5, 5);
    vlayout->addWidget(new Wt::WText(Wt::WString::tr("WorkModePannel")));

    vlayout->addWidget(new LightDiode("indication_two_takts_work_mode"));
    vlayout->addWidget(new LightDiode("indication_four_takts_work_mode"));
    vlayout->addWidget(new LightDiode("indication_dot_work_mode"));
    vlayout->addWidget(new LightDiode("indication_interval_work_mode"));
    Wt::WPushButton *button = new Wt::WPushButton(Wt::WString::tr("work_mode_button"));
    button->clicked().connect(std::bind([=] () {
        //canvas->clear();
    }));
    vlayout->addWidget(button);
}
