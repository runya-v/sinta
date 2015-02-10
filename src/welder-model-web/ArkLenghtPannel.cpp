#include <Wt/WVBoxLayout>
#include <Wt/WString>
#include <Wt/WText>
#include <Wt/WCssDecorationStyle>
#include <Wt/WBreak>
#include <Wt/WSlider>

#include "ArkLenghtPannel.hpp"

using namespace Web;


ArkLenghtPannel::ArkLenghtPannel() {
    this->setStyleClass("welding-power");

    Wt::WVBoxLayout *vlayout = new Wt::WVBoxLayout(this);
    vlayout->setContentsMargins(5, 5, 5, 5);
    vlayout->addWidget(new Wt::WText(Wt::WString::tr("ArkLenghtPannel")));

    Wt::WContainerWidget *container = new Wt::WContainerWidget();
    vlayout->addWidget(container);
	new Wt::WBreak(container);
	Wt::WSlider *slider = new Wt::WSlider(container);
	slider->setStyleClass("slider");
	slider->resize(400, 50);
	slider->setRange(0, 1000);
	new Wt::WBreak(container);
	Wt::WText *out = new Wt::WText(container);
	new Wt::WBreak(container);

	slider->valueChanged().connect(std::bind([=] () {
		out->setText(slider->valueText());
	}));
}
