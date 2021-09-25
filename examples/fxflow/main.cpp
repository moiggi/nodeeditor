#include <nodes/NodeData>
#include <nodes/FlowScene>
#include <nodes/FlowView>
#include <nodes/ConnectionStyle>

#include <QtWidgets/QApplication>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QMenuBar>

#include <nodes/DataModelRegistry>

#include "ImageSourceDataModel.hpp"
#include "ImageDisplayDataModel.hpp"
#include "BlurEffectDataModel.hpp"
#include "AlphaBlendEffectDataModel.hpp"

using QtNodes::DataModelRegistry;
using QtNodes::FlowScene;
using QtNodes::FlowView;
using QtNodes::ConnectionStyle;

namespace {

std::shared_ptr<DataModelRegistry> registerDataModels() {
  auto ret = std::make_shared<DataModelRegistry>();

  ret->registerModel<ImageSourceDataModel>("Sources");
  ret->registerModel<ImageDisplayDataModel>("Displays");
  ret->registerModel<BlurEffectDataModel>("Effects");
  ret->registerModel<AlphaBlendEffectDataModel>("Effects");

  return ret;
}

void setStyle() {
  ConnectionStyle::setConnectionStyle(R"(
  {
    "ConnectionStyle": {
      "ConstructionColor": "gray",
      "NormalColor": "black",
      "SelectedColor": "gray",
      "SelectedHaloColor": "deepskyblue",
      "HoveredColor": "deepskyblue",

      "LineWidth": 3.0,
      "ConstructionLineWidth": 2.0,
      "PointDiameter": 10.0,

      "UseDataDefinedColors": true
    }
  })");
}
} //namespace

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  setStyle();

  QWidget mainWidget;

  auto menuBar    = new QMenuBar();
  auto saveAction = menuBar->addAction("Save..");
  auto loadAction = menuBar->addAction("Load..");

  QVBoxLayout *l = new QVBoxLayout(&mainWidget);

  l->addWidget(menuBar);
  auto scene = new FlowScene(registerDataModels(), &mainWidget);
  l->addWidget(new FlowView(scene));
  l->setContentsMargins(0, 0, 0, 0);
  l->setSpacing(0);

  QObject::connect(saveAction, &QAction::triggered,
                   scene, &FlowScene::save);

  QObject::connect(loadAction, &QAction::triggered,
                   scene, &FlowScene::load);

  mainWidget.setWindowTitle("Dataflow tools: simplest calculator");
  mainWidget.resize(800, 600);
  mainWidget.showNormal();

  return app.exec();
}
