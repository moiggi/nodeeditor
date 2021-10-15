#pragma once

#include <map>

#include "NodeStyle.hpp"
#include "ConnectionStyle.hpp"
#include "FlowViewStyle.hpp"
#include "Export.hpp"

namespace QtNodes
{

class NODE_EDITOR_PUBLIC StyleCollection
{
public:
  struct NodeStyles {
    NodeStyle baseStyle;
    std::map<QString /*node data model style id*/, NodeStyle> nodeStyles;
  };

  struct ConnectionStyles {
    ConnectionStyle baseStyle;
    std::map<QString /*data style id*/, ConnectionStyle> connectionStyles;
  };

public:

  static
  NodeStyle const&
  nodeStyle(const QString& styleId);

  static
  ConnectionStyle const&
  connectionStyle(const QString& styleId);

  static
  FlowViewStyle const&
  flowViewStyle();

public:

  static
  void
  setNodeStyle(NodeStyles);

  static
  void
  setConnectionStyle(ConnectionStyles);

  static
  void
  setFlowViewStyle(FlowViewStyle);

private:

  StyleCollection() = default;

  StyleCollection(StyleCollection const&) = delete;

  StyleCollection&
  operator=(StyleCollection const&) = delete;

  static
  StyleCollection&
  instance();

private:

  NodeStyles _nodeStyles;

  ConnectionStyles _connectionStyles;

  FlowViewStyle _flowViewStyle;
};
}
