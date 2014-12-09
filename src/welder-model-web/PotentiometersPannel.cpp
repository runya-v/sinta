#include <Wt/WHBoxLayout>
#include <Wt/WVBoxLayout>
#include <Wt/WString>
#include <Wt/WText>
#include <Wt/WCssDecorationStyle>
#include <Wt/WBorder>
#include <Wt/WColor>

#include "WorkModePannel.hpp"
#include "WeldingPowerPannel.hpp"
#include "ArkLenghtPannel.hpp"
#include "DynamikParamsPannel.hpp"
#include "PotentiometersPannel.hpp"

using namespace Web;


PotentiometersPannel::PotentiometersPannel() {
    //this->decorationStyle().setBorder(Wt::WBorder(Wt::WBorder::Solid, Wt::WBorder::Thin, Wt::WColor(0, 0, 0, 255)));
    this->setStyleClass("pannel");

    Wt::WHBoxLayout *hbox = new Wt::WHBoxLayout();
    hbox->setContentsMargins(5, 5, 5, 5);
    hbox->addWidget(new WorkModePannel());

    Wt::WVBoxLayout *vbox = new Wt::WVBoxLayout();
    vbox->setContentsMargins(5, 5, 5, 5);
    vbox->addWidget(new WeldingPowerPannel());
    vbox->addWidget(new ArkLenghtPannel());
    hbox->addLayout(vbox);

    hbox->addWidget(new DynamikParamsPannel());

    Wt::WVBoxLayout *vlayout = new Wt::WVBoxLayout(this);
    vlayout->setContentsMargins(5, 5, 5, 5);
    vlayout->addWidget(new Wt::WText(Wt::WString::tr("PotentiometersPannel")));
    vlayout->addLayout(hbox);
}
