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
    hbox->addWidget(new WorkModePannel(), 1);

    Wt::WVBoxLayout *vbox = new Wt::WVBoxLayout();
    vbox->addWidget(new WeldingPowerPannel(), 1);
    vbox->addWidget(new ArkLenghtPannel(), 1);
    hbox->addLayout(vbox);

    hbox->addWidget(new DynamikParamsPannel(), 1);

    Wt::WVBoxLayout *vlayout = new Wt::WVBoxLayout(this);
    vlayout->addWidget(new Wt::WText(Wt::WString::tr("PotentiometersPannel")));
    vlayout->addLayout(hbox);
}
