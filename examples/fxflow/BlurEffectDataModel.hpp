#pragma once

#include "ImageEffectDataModel.hpp"

class QLabel;

class BlurEffectDataModel : public ImageEffectDataModel {
public:
  ~BlurEffectDataModel() override = default;

  QString caption() const override { return QStringLiteral("Blur"); }
  QString name() const override { return QStringLiteral("Blur"); }

protected:
  void compute() override;
};
