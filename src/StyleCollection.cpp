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
connectionStyle(const QString& styleId)
{
  const auto& styles = instance()._connectionStyles;
  auto s = styles.connectionStyles.find(styleId);
  if (s != styles.connectionStyles.end()) {
    return s->second;
  } else {
    return styles.baseStyle;
  }
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
setConnectionStyle(ConnectionStyles connectionStyles)
{
  instance()._connectionStyles = std::move(connectionStyles);
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
