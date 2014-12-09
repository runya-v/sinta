#include <Wt/WVBoxLayout>
#include <Wt/WString>
#include <Wt/WText>
#include <Wt/WCssDecorationStyle>
#include <Wt/WBorder>
#include <Wt/WColor>
#include <Wt/WBreak>
#include <Wt/WSlider>

#include "WeldingPowerPannel.hpp"

using namespace Web;


WeldingPowerPannel::WeldingPowerPannel() {
    this->setStyleClass("welding-power");

    Wt::WVBoxLayout *vlayout = new Wt::WVBoxLayout(this);
    vlayout->setContentsMargins(5, 5, 5, 5);
    vlayout->addWidget(new Wt::WText(Wt::WString::tr("WeldingPowerPannel")));
    
    Wt::WContainerWidget *container = new Wt::WContainerWidget();
    container->setStyleClass("welder");
    //container->decorationStyle().setBorder(Wt::WBorder(Wt::WBorder::Solid, Wt::WBorder::Thin, Wt::WColor(0, 0, 0, 255)));
    vlayout->addWidget(container);
	new Wt::WBreak(container);
	Wt::WSlider *slider = new Wt::WSlider(container);
	slider->decorationStyle().setBackgroundColor(Wt::WColor(0, 0, 100, 255)); 
	//slider->decorationStyle().setForegroundColor(Wt::WColor(0, 0, 100, 255));
	//slider->resize(Wt::WLength(100, Wt::WLength::Percentage), Wt::WLength(50, Wt::WLength::Percentage));
	slider->resize(500, 50);
	//slider->setTickPosition(Wt::WSlider::TicksAbove);
	slider->setTickPosition(Wt::WSlider::TicksBothSides);
	slider->setRange(0, 1000);
	new Wt::WBreak(container);

	slider->valueChanged().connect(std::bind([=] () {
		//out->setText("I'm born in the year " + slider->valueText() + ".");
	}));
}
