#include "NodeStyle.hpp"

#include <QtCore/QFile>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>

#include <QDebug>

#include "StyleCollection.hpp"

using QtNodes::NodeStyle;

inline void initResources() { Q_INIT_RESOURCE(resources); }

#define NODE_STYLE_READ_COLOR(values, variable) QtNodes::Style::readColor(values, #variable, variable)
#define NODE_STYLE_READ_FLOAT(values, variable) QtNodes::Style::readFloat(values, #variable, variable)

namespace
{
  QtNodes::StyleCollection::NodeStyles loadNodeStyles(const QJsonDocument& json)
  {
    QJsonObject topLevelObject = json.object();
    QJsonObject nodeStyleObject = topLevelObject["NodeStyle"].toObject();

    QtNodes::StyleCollection::NodeStyles styles;
    styles.baseStyle.loadStyle(nodeStyleObject);

    QJsonObject nodesObject = nodeStyleObject["Nodes"].toObject();
    for (auto i = nodesObject.begin(), i_end = nodesObject.end(); i != i_end; ++i) {
      Q_ASSERT(styles.nodeStyles.find(i.key()) == styles.nodeStyles.end()); // should not have duplicates
      NodeStyle nodeStyle = styles.baseStyle;
      nodeStyle.loadStyle(i.value().toObject());
      styles.nodeStyles[i.key()] = nodeStyle;
    }

    return styles;
  }
}

NodeStyle::
NodeStyle()
{
  // Explicit resources initialization for preventing the static initialization
  // order fiasco: https://isocpp.org/wiki/faq/ctors#static-init-order
  initResources();

  // This configuration is stored inside the compiled unit and is loaded statically
  loadJsonFile(":DefaultStyle.json");
}


NodeStyle::
NodeStyle(QString jsonText)
{
  loadJsonText(jsonText);
}


void
NodeStyle::
setNodeStyle(QString jsonText)
{
  auto styles = loadNodeStyles(QJsonDocument::fromJson(jsonText.toUtf8()));
  StyleCollection::setNodeStyle(styles);
}


void
NodeStyle::
loadJsonFile(QString styleFile)
{
  QFile file(styleFile);

  if (!file.open(QIODevice::ReadOnly))
  {
    qWarning() << "Couldn't open file " << styleFile;

    return;
  }

  loadJsonFromByteArray(file.readAll());
}


void
NodeStyle::
loadJsonText(QString jsonText)
{
  loadJsonFromByteArray(jsonText.toUtf8());
}


void
NodeStyle::
loadJsonFromByteArray(QByteArray const &byteArray)
{
  QJsonDocument json(QJsonDocument::fromJson(byteArray));

  QJsonObject topLevelObject = json.object();

  loadStyle(topLevelObject["NodeStyle"].toObject());
}

void NodeStyle::loadStyle(const QJsonObject& style)
{
  NODE_STYLE_READ_COLOR(style, BoundaryColor);
  NODE_STYLE_READ_COLOR(style, GradientColor0);
  NODE_STYLE_READ_COLOR(style, GradientColor1);
  NODE_STYLE_READ_COLOR(style, GradientColor2);
  NODE_STYLE_READ_COLOR(style, GradientColor3);

  NODE_STYLE_READ_COLOR(style, SelectedBoundaryColor);
  NODE_STYLE_READ_COLOR(style, SelectedGradientColor0);
  NODE_STYLE_READ_COLOR(style, SelectedGradientColor1);
  NODE_STYLE_READ_COLOR(style, SelectedGradientColor2);
  NODE_STYLE_READ_COLOR(style, SelectedGradientColor3);

  NODE_STYLE_READ_COLOR(style, ShadowColor);
  NODE_STYLE_READ_COLOR(style, FontColor);
  NODE_STYLE_READ_COLOR(style, FontColorFaded);
  NODE_STYLE_READ_COLOR(style, WarningColor);
  NODE_STYLE_READ_COLOR(style, ErrorColor);

  NODE_STYLE_READ_FLOAT(style, PenWidth);
  NODE_STYLE_READ_FLOAT(style, SelectedPenWidth);
  NODE_STYLE_READ_FLOAT(style, HoveredPenWidth);

  NODE_STYLE_READ_FLOAT(style, ConnectionPointDiameter);

  NODE_STYLE_READ_FLOAT(style, Opacity);
}
