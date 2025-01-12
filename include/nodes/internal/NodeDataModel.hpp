#pragma once


#include <QtWidgets/QWidget>
#include <QString>

#include "PortType.hpp"
#include "NodeData.hpp"
#include "Serializable.hpp"
#include "NodeGeometry.hpp"
#include "NodeStyle.hpp"
#include "NodePainterDelegate.hpp"
#include "Export.hpp"
#include "memory.hpp"

namespace QtNodes
{

enum class NodeValidationState
{
  Valid,
  Warning,
  Error
};

class Connection;

class StyleCollection;

class NODE_EDITOR_PUBLIC NodeDataModel
  : public QObject
  , public Serializable
{
  Q_OBJECT

public:

  NodeDataModel();

  ~NodeDataModel() override = default;

  /// Caption is used in GUI
  virtual QString
  caption() const = 0;

  /// It is possible to hide caption in GUI
  virtual bool
  captionVisible() const { return true; }

  /// Port caption is used in GUI to label individual ports
  virtual QString
  portCaption(PortType, PortIndex) const { return QString(); }

  /// It is possible to hide port caption in GUI
  virtual bool
  portCaptionVisible(PortType, PortIndex) const { return false; }

  /// Name makes this model unique
  virtual QString
  name() const = 0;

public:

  QJsonObject
  save() const override;

public:

  virtual
  unsigned int nPorts(PortType portType) const = 0;

  virtual
  NodeDataType dataType(PortType portType, PortIndex portIndex) const = 0;

public:

  enum class OutConnectionPolicy
  {
    One,
    Many,
  };

  virtual
  OutConnectionPolicy
  portOutConnectionPolicy(PortIndex) const
  {
    return OutConnectionPolicy::Many;
  }

  enum class InConnectionPolicy
  {
    Fixed,
    Substitute,
  };

  virtual
  InConnectionPolicy
  portInConnectionPolicy(PortIndex) const
  {
    return InConnectionPolicy::Substitute;
  }

  // derived classes can define specific style here. The default behavior is to load the style
  // of styleId() from the style collection
  virtual NodeStyle const&
  nodeStyle() const;

  virtual QString styleId() const { return {}; }

public:

  /// Triggers the algorithm
  virtual
  void
  setInData(std::shared_ptr<NodeData> /*nodeData*/,
            PortIndex /*port*/) {}

  virtual
  std::shared_ptr<NodeData>
  outData(PortIndex /*port*/) { return nullptr; }

  virtual
  QWidget *
  embeddedWidget() = 0;

  virtual
  bool
  resizable() const { return false; }

  virtual
  NodeValidationState
  validationState() const { return NodeValidationState::Valid; }

  virtual
  QString
  validationMessage() const { return ""; }

  virtual
  NodePainterDelegate* painterDelegate() const { return nullptr; }

public Q_SLOTS:

  virtual void
  inputConnectionCreated(Connection const&)
  {
  }

  virtual void
  inputConnectionDeleted(Connection const&)
  {
  }

  virtual void
  outputConnectionCreated(Connection const&)
  {
  }

  virtual void
  outputConnectionDeleted(Connection const&)
  {
  }

Q_SIGNALS:

  void
  dataUpdated(PortIndex index);

  void
  dataInvalidated(PortIndex index);

  void
  computingStarted();

  void
  computingFinished();

  void embeddedWidgetSizeUpdated();

};
}
