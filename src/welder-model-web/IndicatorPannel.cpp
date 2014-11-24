#include <Wt/WHBoxLayout>
#include <Wt/WVBoxLayout>
#include <Wt/WText>

#include "LcdIndicator.hpp"
#include "JobListPannel.hpp"
#include "WelderParamsPannel.hpp"
#include "WeldingTypesPannel.hpp"
#include "IndicatorPannel.hpp"

using namespace Web;


IndicatorPannel::IndicatorPannel() {
    Wt::WVBoxLayout *vbox = new Wt::WVBoxLayout();
    LcdIndicator *lcd_indicator = new LcdIndicator();
    vbox->addWidget(lcd_indicator, 0);
    JobListPannel *job_list_pannel = new JobListPannel();
    vbox->addWidget(job_list_pannel, 1);
    Wt::WHBoxLayout *hbox = new Wt::WHBoxLayout();
    hbox->addLayout(vbox, 0);
    this->setLayout(hbox);
    WelderParamsPannel *welder_params_pannel = new WelderParamsPannel();
    hbox->addWidget(welder_params_pannel, 1);
    WeldingTypesPannel *welding_types_pannel = new WeldingTypesPannel();
    hbox->addWidget(welding_types_pannel, 2);
    Wt::WVBoxLayout *vlayout = new Wt::WVBoxLayout();
    vlayout->addWidget(new Wt::WText("IndicatorPannel"), 0);
    vlayout->addLayout(hbox, 1);
}
