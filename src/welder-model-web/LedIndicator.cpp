#include <Wt/WHBoxLayout>
#include <Wt/WVBoxLayout>
#include <Wt/WString>
#include <Wt/WText>

#include "LedIndicator.hpp"


using namespace Web;

static const uint32_t LED_ROWS = 2;
static const uint32_t LED_COLUMNS = 16;



LedIndicator::LedIndicator() {
    _symbols_table = new Wt::WTable(this);
    _symbols_table->setWidth("100%");

    for (uint32_t row = 0; row < LED_ROWS; ++row) {
        for (uint32_t column = 0; column < LED_COLUMNS; ++column) {
            _symbols_table->elementAt(row, column)->addWidget(new Wt::WText("#"));
        }
    }
    //Wt::WText *item = new Wt::WText("Item 1");
    //item->setStyleClass("green-box");
    //hbox->addWidget(item);
    //
    //item = new Wt::WText("Item 2");
    //item->setStyleClass("blue-box");
    //hbox->addWidget(item);
}

