#pragma once

#include <QtCore/QString>
#include <QJsonObject>
#include <QJsonArray>
#include <QColor>

namespace QtNodes
{

class Style
{
public:

  virtual
  ~Style() = default;

protected:
  static void readColor(const QJsonObject& values, const char* variableName, QColor& variable)
  {
    auto value = values[variableName];
    if (value.type() == QJsonValue::Undefined || value.type() == QJsonValue::Null) {
      qDebug() << "Undefined value for parameter:" << variableName;
    } else {
      if (value.isArray()) {
        auto colorArray = value.toArray();
        std::vector<int> rgb;
        rgb.reserve(3);
        for (auto &&it: colorArray) {
          rgb.push_back(it.toInt());
        }
        variable = QColor(rgb[0], rgb[1], rgb[2]);
      } else {
        variable = QColor(value.toString());
      }
    }
  }

  static void readFloat(const QJsonObject& values, const char* variableName, float& variable)
  {
    auto value = values[variableName];
    if (value.type() == QJsonValue::Undefined || value.type() == QJsonValue::Null) {
      qDebug() << "Undefined value for parameter:" << variableName;
    } else {
      variable = static_cast<float>(value.toDouble());
    }
  }

  static void readBool(const QJsonObject& values, const char* variableName, bool& variable)
  {
    auto value = values[variableName];
    if (value.type() == QJsonValue::Undefined || value.type() == QJsonValue::Null) {
      qDebug() << "Undefined value for parameter:" << variableName;
    } else {
      variable = value.toBool();
    }
  }

};

}
