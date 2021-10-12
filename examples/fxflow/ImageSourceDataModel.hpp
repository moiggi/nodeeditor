#pragma once

#include <QtCore/QObject>

#include <nodes/NodeDataModel>

#include <iostream>

class QWidget;
class QPushButton;
class PixmapData;

using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDataModel;
using QtNodes::NodeValidationState;

class ImageSourceDataModel: public NodeDataModel
{
  Q_OBJECT

public:
  ImageSourceDataModel();
  ~ImageSourceDataModel() override = default;

  QString caption() const override { return QStringLiteral("Image Source"); }
  bool captionVisible() const override { return true; }
  QString name() const override { return QStringLiteral("Image Source"); }

  QJsonObject save() const override;
  void restore(QJsonObject const &p) override;

  unsigned int nPorts(PortType portType) const override;
  NodeDataType dataType(PortType portType, PortIndex portIndex) const override;
  std::shared_ptr<NodeData> outData(PortIndex port) override;
  
  QWidget* embeddedWidget() override;

  bool resizable() const override { return true; }

private Q_SLOTS:
  void onImageButtonClicked(bool);

private:
  bool eventFilter(QObject* object, QEvent* event) override;

  bool loadImage(const QString& fileName);

  QString styleId() const override { return "ImageSource"; }

private:
  std::shared_ptr<PixmapData> _pixmapData;

  QPushButton* _imageButton;
};
