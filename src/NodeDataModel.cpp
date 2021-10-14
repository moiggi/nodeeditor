#include "NodeDataModel.hpp"

#include "StyleCollection.hpp"

using QtNodes::NodeDataModel;
using QtNodes::NodeStyle;

NodeDataModel::
NodeDataModel()
{
  // Derived classes can initialize specific style here
}


QJsonObject
NodeDataModel::
save() const
{
  QJsonObject modelJson;

  modelJson["name"] = name();

  return modelJson;
}


NodeStyle const&
NodeDataModel::
nodeStyle() const
{
  return StyleCollection::nodeStyle(styleId());
}
