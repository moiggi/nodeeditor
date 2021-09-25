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
  bool captionVisible() const override { return false; }
  QString name() const override { return QStringLiteral("Display"); }

  unsigned int nPorts(PortType portType) const override;
  NodeDataType dataType(PortType portType, PortIndex portIndex) const override;
  void setInData(std::shared_ptr<NodeData> data, int) override;

  QWidget* embeddedWidget() override;

  NodeValidationState validationState() const override;
  QString validationMessage() const override;

private:
  std::shared_ptr<PixmapData> _pixmapData;

  ImageDisplayLabel* _label;

  NodeValidationState modelValidationState = NodeValidationState();
  QString modelValidationError;
};
