#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include "ImageEffectDataModel.hpp"

#include "PixmapData.hpp"

ImageEffectDataModel::ImageEffectDataModel(unsigned int numInPorts)
: _ins(numInPorts), _label(new QLabel())
{
  _label->setFixedSize(PixmapData::THUMBNAIL_SIZE, PixmapData::THUMBNAIL_SIZE);
  _label->setScaledContents(true);
}

unsigned int ImageEffectDataModel::nPorts(PortType portType) const
{
  unsigned int result;

  if (portType == PortType::In) {
    result = _ins.size();
  } else {
    result = 1;
  }

  return result;
}


NodeDataType ImageEffectDataModel::dataType(PortType, PortIndex) const
{
  return PixmapData().type();
}


std::shared_ptr<NodeData> ImageEffectDataModel::outData(PortIndex)
{
  return std::static_pointer_cast<NodeData>(_out);
}


void ImageEffectDataModel::setInData(std::shared_ptr<NodeData> data, PortIndex portIndex)
{

  if (data) {
    assert(portIndex < _ins.size());
    _ins[portIndex] = std::dynamic_pointer_cast<PixmapData>(data);

    compute();

    _label->setPixmap(_out->pixmap());

    modelValidationState = NodeValidationState::Valid;
    modelValidationError = QString();
  } else {
    _label->clear();
    modelValidationState = NodeValidationState::Warning;
    modelValidationError = "Missing or incorrect inputs";
  }
}


NodeValidationState ImageEffectDataModel::validationState() const
{
  return modelValidationState;
}


QString ImageEffectDataModel::validationMessage() const
{
  return modelValidationError;
}

QPixmap ImageEffectDataModel::applyEffect(const QPixmap& src, QGraphicsEffect* effect)
{
    if(src.isNull() || !effect) {
      return src;
    }

    QGraphicsScene scene;
    QGraphicsPixmapItem item;
    item.setPixmap(src);
    item.setGraphicsEffect(effect);
    scene.addItem(&item);

    QPixmap res(src.size());
    res.fill(Qt::transparent);
    QPainter ptr(&res);
    scene.render(&ptr, QRectF(), QRectF(0, 0, src.width(), src.height()));
    return res;
}

