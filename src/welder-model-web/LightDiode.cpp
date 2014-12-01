#include <Wt/WHBoxLayout>
#include <Wt/WPaintedWidget>
#include <Wt/WPainter>
#include <Wt/WPainterPath>
#include <Wt/WBrush>
#include <Wt/WText>

#include "LightDiode.hpp"

using namespace Web;


class PaintedWidget
    : public Wt::WPaintedWidget
{
public:
    PaintedWidget(Wt::WContainerWidget *parent = 0)
        : Wt::WPaintedWidget(parent)
    {
        resize(30, 30);
    }

protected:
    void paintEvent(Wt::WPaintDevice *paint_device) {
        Wt::WPainter painter(paint_device);
        painter.setBrush(Wt::WBrush(Wt::WBrush(Wt::green)));
        painter.setPen(Wt::black);
        Wt::WPainterPath filled_ellipse_path = Wt::WPainterPath();
        filled_ellipse_path.addEllipse(0, 0, 30, 30);
        filled_ellipse_path.closeSubPath();
        painter.drawPath(filled_ellipse_path);
    }
};


LightDiode::LightDiode(const std::string &text) {
    Wt::WHBoxLayout *hlayout = new Wt::WHBoxLayout(this);
    hlayout->addWidget(new PaintedWidget(this));
    hlayout->addWidget(new Wt::WText(Wt::WString::tr(text)));
}
