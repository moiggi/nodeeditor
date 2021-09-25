#pragma once

#include "ImageEffectDataModel.hpp"

class QLabel;

class AlphaBlendEffectDataModel : public ImageEffectDataModel {
public:
  AlphaBlendEffectDataModel() : ImageEffectDataModel(2) {}
  ~AlphaBlendEffectDataModel() override = default;

  QString caption() const override { return QStringLiteral("Alpha Blend"); }
  QString name() const override { return QStringLiteral("Alpha Blend"); }

protected:
  void compute() override;
};
