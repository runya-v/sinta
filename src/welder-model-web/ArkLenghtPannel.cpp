#include <Wt/WVBoxLayout>
#include <Wt/WString>
#include <Wt/WText>
#include <Wt/WCssDecorationStyle>
#include <Wt/WBorder>
#include <Wt/WColor>

#include "ArkLenghtPannel.hpp"

using namespace Web;


ArkLenghtPannel::ArkLenghtPannel() {
	this->decorationStyle().setBorder(Wt::WBorder(Wt::WBorder::Solid, Wt::WBorder::Thin, Wt::WColor(0, 0, 0, 255)));

	Wt::WVBoxLayout *vlayout = new Wt::WVBoxLayout(this);
	vlayout->addWidget(new Wt::WText(Wt::WString::tr("ArkLenghtPannel")));
}
