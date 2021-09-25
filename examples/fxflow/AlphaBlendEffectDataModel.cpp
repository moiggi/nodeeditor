#include "AlphaBlendEffectDataModel.hpp"

#include <QGraphicsBlurEffect>

#include "PixmapData.hpp"

void AlphaBlendEffectDataModel::compute()
{
    _out = std::make_shared<PixmapData>();

    auto in0 = _ins[0].lock();
    auto in1 = _ins[1].lock();
    if (in0 && in1) {
      int w = in1->pixmap().width();
      int h = in1->pixmap().height();
      _out->setPixmap(QPixmap(w, h));
      _out->pixmap().fill(Qt::transparent);

      QPainter painter(&_out->pixmap());
      painter.setOpacity(0.5);
      painter.drawPixmap(0, 0, in1->pixmap());
      painter.setOpacity(0.5);
      painter.drawPixmap(0, 0, w, h, in0->pixmap());
    } else if (in0) {
      _out->setPixmap(in0->pixmap());
    } else if (in1) {
      _out->setPixmap(in1->pixmap());
    }
}



