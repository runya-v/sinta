#include <Wt/WVBoxLayout>
#include <Wt/WHBoxLayout>
#include <Wt/WString>
#include <Wt/WText>
#include <Wt/WCssDecorationStyle>
#include <Wt/WBorder>
#include <Wt/WColor>
#include <Wt/WPushButton>

#include "JobListPannel.hpp"
#include "LightDiode.hpp"

using namespace Web;


JobListPannel::JobListPannel() {
    this->decorationStyle().setBorder(Wt::WBorder(Wt::WBorder::Solid, Wt::WBorder::Thin, Wt::WColor(0, 0, 0, 255)));

    Wt::WVBoxLayout *vlayout = new Wt::WVBoxLayout(this);
    vlayout->addWidget(new Wt::WText(Wt::WString::tr("JobListPannel")));

    Wt::WHBoxLayout *hlayout = new Wt::WHBoxLayout();
    vlayout->addLayout(hlayout);

    Wt::WVBoxLayout *vbox = new Wt::WVBoxLayout();
    hlayout->addLayout(vbox);
    vbox->addWidget(new LightDiode("job_list_diode"));
    Wt::WPushButton *button = new Wt::WPushButton(Wt::WString::tr("job_list_button"));
    button->clicked().connect(std::bind([=] () {
        //canvas->clear();
    }));
    vbox->addWidget(button);

    vbox = new Wt::WVBoxLayout();
    hlayout->addLayout(vbox);
    vbox->addWidget(new LightDiode("indication_error"));
    vbox->addWidget(new LightDiode("indication_overheating"));

    vbox = new Wt::WVBoxLayout();
    hlayout->addLayout(vbox);
    vbox->addWidget(new LightDiode("indication_positive_polarity"));
    vbox->addWidget(new LightDiode("indication_negative_polarity"));
}
