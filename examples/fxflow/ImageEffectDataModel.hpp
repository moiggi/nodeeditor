#pragma once

#include <QObject>
#include <QLabel>

#include <nodes/NodeDataModel>

#include <memory>
#include <iostream>
#include <vector>

class PixmapData;

using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDataModel;
using QtNodes::NodeValidationState;

/// The model dictates the number of inputs and outputs for the Node.
/// In this example it has no logic.
class ImageEffectDataModel : public NodeDataModel
{
  Q_OBJECT

public:
  explicit ImageEffectDataModel(unsigned int numInPorts = 1);
  ~ImageEffectDataModel() override = default;

  unsigned int nPorts(PortType portType) const override;
  NodeDataType dataType(PortType portType, PortIndex portIndex) const override;
  std::shared_ptr<NodeData> outData(PortIndex port) override;
  void setInData(std::shared_ptr<NodeData> data, PortIndex portIndex) override;

  bool captionVisible() const override { return true; }
  QWidget* embeddedWidget() override { return _label; }

  bool resizable() const override { return true; }

  NodeValidationState validationState() const override;
  QString validationMessage() const override;

protected:
  virtual void compute() = 0;

  QPixmap applyEffect(const QPixmap& src, QGraphicsEffect* effect);

  bool eventFilter(QObject* object, QEvent* event) override;

protected:
  std::vector<std::weak_ptr<PixmapData>> _ins;
  std::shared_ptr<PixmapData> _out;

  QLabel* _label;

  NodeValidationState modelValidationState = NodeValidationState::Warning;
  QString modelValidationError = QString("Missing or incorrect inputs");
};
