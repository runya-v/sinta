#include <Wt/WVBoxLayout>
#include <Wt/WString>
#include <Wt/WText>
#include <Wt/WCssDecorationStyle>
#include <Wt/WBorder>
#include <Wt/WColor>

#include "Log.hpp"
#include "LcdIndicator.hpp"

using namespace Web;

static const uint32_t LED_ROWS = 2;
static const uint32_t LED_COLUMNS = 16;


LcdIndicator::LcdIndicator() {
    this->setStyleClass("lcd-indicator");

    _symbols_table = new Wt::WTable();
    _symbols_table->setWidth("100%");
    for (uint32_t row = 0; row < LED_ROWS; ++row) {
        for (uint32_t column = 0; column < LED_COLUMNS; ++column) {
            _symbols_table->elementAt(row, column)->addWidget(new Wt::WText("#"));
        }
    }

    Wt::WVBoxLayout *vlayout = new Wt::WVBoxLayout(this);
    vlayout->addWidget(new Wt::WText(Wt::WString::tr("LcdIndicator")));
    vlayout->addWidget(_symbols_table);
}


void LcdIndicator::setText(int row, int column, std::string &text) {
    int row_count = _symbols_table->rowCount();
    int column_count = _symbols_table->columnCount();

    if (row < row_count && column < column_count) {
        //_symbols_table->elementAt(row, column)->
    }
    else {
        LOG(ERROR)
            << "Invalid new text parameters: input ["
            << row << ":" << column << "], but need ["
            << row_count - 1 << ":" << column_count - 1 << "].";
    }
}

