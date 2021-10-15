#pragma once

#include <QtGui/QColor>

#include "Export.hpp"
#include "Style.hpp"

namespace QtNodes
{

class NODE_EDITOR_PUBLIC ConnectionStyle : public Style
{
public:

  ConnectionStyle();

  explicit ConnectionStyle(QString jsonText);

public:

  static void setConnectionStyle(QString jsonText);

  void loadStyle(const QJsonObject& style);

private:

  void loadJsonText(QString jsonText);

  void loadJsonFile(QString fileName);

  void loadJsonFromByteArray(QByteArray const &byteArray);

public:

  QColor ConstructionColor;
  QColor NormalColor;
  QColor SelectedColor;
  QColor SelectedHaloColor;
  QColor HoveredColor;

  QColor ConnectionPointColor;
  QColor FilledConnectionPointColor;

  float LineWidth;
  float ConstructionLineWidth;
  float PointDiameter;
};
}
