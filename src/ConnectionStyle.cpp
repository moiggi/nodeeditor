#include "ConnectionStyle.hpp"

#include <iostream>

#include <QtCore/QFile>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonValueRef>

#include <QDebug>

#include "StyleCollection.hpp"

using QtNodes::ConnectionStyle;

inline void initResources() { Q_INIT_RESOURCE(resources); }

#define CONNECTION_STYLE_READ_COLOR(values, variable) QtNodes::Style::readColor(values, #variable, variable)
#define CONNECTION_STYLE_READ_FLOAT(values, variable) QtNodes::Style::readFloat(values, #variable, variable)
#define CONNECTION_STYLE_READ_BOOL(values, variable) QtNodes::Style::readBool(values, #variable, variable)

namespace
{
  QtNodes::StyleCollection::ConnectionStyles loadConnectionStyles(const QJsonDocument& json)
  {
    QJsonObject topLevelObject = json.object();
    QJsonObject connectionStyleObject = topLevelObject["ConnectionStyle"].toObject();

    QtNodes::StyleCollection::ConnectionStyles styles;
    styles.baseStyle.loadStyle(connectionStyleObject);

    QJsonObject dataObject = connectionStyleObject["Data"].toObject();
    for (auto i = dataObject.begin(), i_end = dataObject.end(); i != i_end; ++i) {
      Q_ASSERT(styles.connectionStyles.find(i.key()) == styles.connectionStyles.end()); // should not have duplicates
      ConnectionStyle connectionStyle = styles.baseStyle;
      connectionStyle.loadStyle(i.value().toObject());
      styles.connectionStyles[i.key()] = connectionStyle;
    }

    return styles;
  }

}

ConnectionStyle::
ConnectionStyle()
{
  // Explicit resources inialization for preventing the static initialization
  // order fiasco: https://isocpp.org/wiki/faq/ctors#static-init-order
  initResources();

  // This configuration is stored inside the compiled unit and is loaded statically
  loadJsonFile(":DefaultStyle.json");
}


ConnectionStyle::
ConnectionStyle(QString jsonText)
{
  loadJsonFile(":DefaultStyle.json");
  loadJsonText(jsonText);
}


void
ConnectionStyle::
setConnectionStyle(QString jsonText)
{
  auto styles = loadConnectionStyles(QJsonDocument::fromJson(jsonText.toUtf8()));

  StyleCollection::setConnectionStyle(styles);
}

void
ConnectionStyle::
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
ConnectionStyle::
loadJsonText(QString jsonText)
{
  loadJsonFromByteArray(jsonText.toUtf8());
}


void
ConnectionStyle::
loadJsonFromByteArray(QByteArray const &byteArray)
{
  QJsonDocument json(QJsonDocument::fromJson(byteArray));

  QJsonObject topLevelObject = json.object();

  QJsonValueRef nodeStyleValues = topLevelObject["ConnectionStyle"];

  QJsonObject obj = nodeStyleValues.toObject();

}

void ConnectionStyle::loadStyle(const QJsonObject& style)
{
  CONNECTION_STYLE_READ_COLOR(style, ConstructionColor);
  CONNECTION_STYLE_READ_COLOR(style, NormalColor);
  CONNECTION_STYLE_READ_COLOR(style, SelectedColor);
  CONNECTION_STYLE_READ_COLOR(style, SelectedHaloColor);
  CONNECTION_STYLE_READ_COLOR(style, HoveredColor);

  CONNECTION_STYLE_READ_COLOR(style, ConnectionPointColor);
  CONNECTION_STYLE_READ_COLOR(style, FilledConnectionPointColor);

  CONNECTION_STYLE_READ_FLOAT(style, LineWidth);
  CONNECTION_STYLE_READ_FLOAT(style, ConstructionLineWidth);
  CONNECTION_STYLE_READ_FLOAT(style, PointDiameter);
}
