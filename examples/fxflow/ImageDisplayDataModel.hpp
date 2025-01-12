#pragma once

#include <QtCore/QObject>

#include <nodes/NodeDataModel>

#include <iostream>

class QWidget;
class PixmapData;
class ImageDisplayLabel;

using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDataModel;
using QtNodes::NodeValidationState;


class ImageDisplayDataModel : public NodeDataModel
{
  Q_OBJECT

public:
  ImageDisplayDataModel();
  ~ImageDisplayDataModel() override = default;

  QString caption() const override { return QStringLiteral("Image Display"); }
  bool captionVisible() const override { return true; }
  QString name() const override { return QStringLiteral("Image Display"); }

  unsigned int nPorts(PortType portType) const override;
  NodeDataType dataType(PortType portType, PortIndex portIndex) const override;
  void setInData(std::shared_ptr<NodeData> data, int) override;

  QWidget* embeddedWidget() override;

  bool resizable() const override { return true; }

  NodeValidationState validationState() const override;
  QString validationMessage() const override;

private:
  bool eventFilter(QObject* object, QEvent* event) override;

  QString styleId() const override { return "ImageDisplay"; }

private:
  std::shared_ptr<PixmapData> _pixmapData;

  ImageDisplayLabel* _label;

  NodeValidationState modelValidationState = NodeValidationState();
  QString modelValidationError;
};
