#include "ImageDisplayDataModel.hpp"

#include <QLabel>
#include <QSizePolicy>

#include "PixmapData.hpp"

class ImageDisplayLabel : public QLabel
{
public:
  ImageDisplayLabel() = default;

  void enterEvent(QEnterEvent * event) override;
  void leaveEvent(QEvent* event) override;
};

void ImageDisplayLabel::enterEvent(QEnterEvent* event) {
  QWidget::enterEvent(event);

//  setFixedSize(512, 512);
//  updateGeometry();
}

void ImageDisplayLabel::leaveEvent(QEvent* event) {
  QWidget::leaveEvent(event);

//  setFixedSize(128, 128);
//  updateGeometry();
}

ImageDisplayDataModel::ImageDisplayDataModel() : _label(new ImageDisplayLabel()) {
  _label->setFixedSize(PixmapData::THUMBNAIL_SIZE, PixmapData::THUMBNAIL_SIZE);
  _label->setScaledContents(true);
}


unsigned int ImageDisplayDataModel::nPorts(PortType portType) const {
  unsigned int result = 1;

  switch (portType) {
    case PortType::In:
      result = 1;
      break;
    case PortType::Out:
      result = 0;
      break;
    default:
      break;
  }

  return result;
}


NodeDataType ImageDisplayDataModel::dataType(PortType, PortIndex) const {
  return PixmapData().type();
}


void ImageDisplayDataModel::setInData(std::shared_ptr<NodeData> data, int) {
  auto inPixmapData = std::dynamic_pointer_cast<PixmapData>(data);

  if (inPixmapData) {
    _pixmapData = std::make_shared<PixmapData>();
    _pixmapData->setPixmap(inPixmapData->pixmap());
    _label->setPixmap(_pixmapData->pixmap());

    modelValidationState = NodeValidationState::Valid;
    modelValidationError = QString();
  } else {
    _label->clear();
    modelValidationState = NodeValidationState::Warning;
    modelValidationError = "Missing or incorrect inputs";
  }
}


QWidget* ImageDisplayDataModel::embeddedWidget()
{
  return _label;
}

NodeValidationState ImageDisplayDataModel::validationState() const {
  return modelValidationState;
}


QString ImageDisplayDataModel::validationMessage() const {
  return modelValidationError;
}
