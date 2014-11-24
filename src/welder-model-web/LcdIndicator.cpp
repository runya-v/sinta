#include <Wt/WVBoxLayout>
#include <Wt/WString>
#include <Wt/WText>

#include "Log.hpp"
#include "LcdIndicator.hpp"

using namespace Web;

static const uint32_t LED_ROWS = 2;
static const uint32_t LED_COLUMNS = 16;


LcdIndicator::LcdIndicator() {
    Wt::WVBoxLayout *vlayout = new Wt::WVBoxLayout(this);
    _symbols_table = new Wt::WTable();
    _symbols_table->setWidth("100%");

    for (uint32_t row = 0; row < LED_ROWS; ++row) {
        for (uint32_t column = 0; column < LED_COLUMNS; ++column) {
            _symbols_table->elementAt(row, column)->addWidget(new Wt::WText("#"));
        }
    }
    vlayout->addWidget(new Wt::WText("LCD"), 0);
    vlayout->addWidget(_symbols_table, 1);
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

