#include <nodes/NodeData>
#include <nodes/FlowScene>
#include <nodes/FlowView>
#include <nodes/ConnectionStyle>

#include <QApplication>
#include <QMenuBar>
#include <QMainWindow>
#include <QScreen>

#include <nodes/DataModelRegistry>

#include "ui_mainwindow.h"

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

  QMainWindow mainWindow;
  Ui::MainWindow ui;
  ui.setupUi(&mainWindow);

  auto scene = new FlowScene(registerDataModels(), &mainWindow);
  ui.effectNodeView->setScene(scene);

  int screenHeight = QGuiApplication::primaryScreen()->size().height();
  ui.imageNodeViewSplitter->setSizes({screenHeight*2/3, screenHeight*1/3});
  int screenWidth = QGuiApplication::primaryScreen()->size().width();
  ui.effectUISplitter->setSizes({screenWidth*3/4, screenWidth*1/4});

  mainWindow.setWindowTitle("FxFlow");
  mainWindow.showMaximized();

  return app.exec();
}
