#include "StyleCollection.hpp"

#include <utility>

using QtNodes::StyleCollection;
using QtNodes::NodeStyle;
using QtNodes::ConnectionStyle;
using QtNodes::FlowViewStyle;

NodeStyle const&
StyleCollection::
nodeStyle(const QString& styleId)
{
  const auto& styles = instance()._nodeStyles;
  auto s = styles.nodeStyles.find(styleId);
  if (s != styles.nodeStyles.end()) {
    return s->second;
  } else {
    return styles.baseStyle;
  }
}


ConnectionStyle const&
StyleCollection::
connectionStyle()
{
  return instance()._connectionStyle;
}


FlowViewStyle const&
StyleCollection::
flowViewStyle()
{
  return instance()._flowViewStyle;
}


void
StyleCollection::
setNodeStyle(NodeStyles nodeStyles)
{
  instance()._nodeStyles = std::move(nodeStyles);
}


void
StyleCollection::
setConnectionStyle(ConnectionStyle connectionStyle)
{
  instance()._connectionStyle = std::move(connectionStyle);
}


void
StyleCollection::
setFlowViewStyle(FlowViewStyle flowViewStyle)
{
  instance()._flowViewStyle = std::move(flowViewStyle);
}



StyleCollection&
StyleCollection::
instance()
{
  static StyleCollection collection;

  return collection;
}
