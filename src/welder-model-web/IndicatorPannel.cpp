#include <Wt/WHBoxLayout>
#include <Wt/WVBoxLayout>
#include <Wt/WString>
#include <Wt/WText>
#include <Wt/WCssDecorationStyle>
#include <Wt/WBorder>
#include <Wt/WColor>

#include "LcdIndicator.hpp"
#include "JobListPannel.hpp"
#include "WelderParamsPannel.hpp"
#include "WeldingTypesPannel.hpp"
#include "IndicatorPannel.hpp"

using namespace Web;


IndicatorPannel::IndicatorPannel() {
    //this->decorationStyle().setBorder(Wt::WBorder(Wt::WBorder::Solid, Wt::WBorder::Thin, Wt::WColor(0, 0, 0, 255)));
    this->setStyleClass("pannel");

    Wt::WVBoxLayout *vbox = new Wt::WVBoxLayout();
	vbox->setContentsMargins(5, 5, 5, 5);
    LcdIndicator *lcd_indicator = new LcdIndicator();
    vbox->addWidget(lcd_indicator);
    JobListPannel *job_list_pannel = new JobListPannel();
    vbox->addWidget(job_list_pannel);

    Wt::WHBoxLayout *hbox = new Wt::WHBoxLayout();
	hbox->setContentsMargins(5, 5, 5, 5);
    hbox->addLayout(vbox, 1);
    WelderParamsPannel *welder_params_pannel = new WelderParamsPannel();
    hbox->addWidget(welder_params_pannel);
    WeldingTypesPannel *welding_types_pannel = new WeldingTypesPannel();
    hbox->addWidget(welding_types_pannel);

    Wt::WVBoxLayout *vlayout = new Wt::WVBoxLayout(this);
	vlayout->setContentsMargins(5, 5, 5, 5);
    vlayout->addWidget(new Wt::WText(Wt::WString::tr("IndicatorPannel")));
    vlayout->addLayout(hbox);
}
