#include "BlurEffectDataModel.hpp"

#include <QGraphicsBlurEffect>

#include "PixmapData.hpp"

void BlurEffectDataModel::compute()
{
    _out = std::make_shared<PixmapData>();

    if (auto in = _ins[0].lock()) {
      QGraphicsBlurEffect* blur = new QGraphicsBlurEffect();
      blur->setBlurRadius(16);
      QPixmap result = applyEffect(in->pixmap(), blur);
      _out->setPixmap(result);
    }
}



