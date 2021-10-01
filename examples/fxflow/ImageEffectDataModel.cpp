#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QEvent>

#include "ImageEffectDataModel.hpp"

#include "PixmapData.hpp"

ImageEffectDataModel::ImageEffectDataModel(unsigned int numInPorts)
: _ins(numInPorts), _label(new QLabel())
{
  _label->setFixedSize(PixmapData::THUMBNAIL_SIZE, PixmapData::THUMBNAIL_SIZE);
  _label->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
  _label->setStyleSheet("background-color: rgba(0,0,0,0)");
  _label->installEventFilter(this);
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

    int w = _label->width();
    int h = _label->height();
    _label->setPixmap(_out->pixmap().scaled(w, h, Qt::KeepAspectRatio));

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

bool ImageEffectDataModel::eventFilter(QObject* object, QEvent* event) {
  if (object == _label && event->type() == QEvent::Resize) {
    if (_out && !_out->pixmap().isNull()) {
      int w = _label->width();
      int h = _label->height();
      _label->setPixmap(_out->pixmap().scaled(w, h, Qt::KeepAspectRatio));
    }
  }

  return false;
}
