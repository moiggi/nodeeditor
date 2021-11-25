#include "MainWindow.h"
#include "ui_mainwindow.h"

#include <nodes/Node>
#include <nodes/NodeData>
#include <nodes/FlowScene>
#include <nodes/FlowView>
#include <nodes/FlowViewStyle>
#include <nodes/NodeStyle>
#include <nodes/ConnectionStyle>
#include <nodes/DataModelRegistry>

#include <QApplication>
#include <QScreen>
#include <QFile>

#include "ImageSourceDataModel.hpp"
#include "ImageDisplayDataModel.hpp"
#include "BlurEffectDataModel.hpp"
#include "AlphaBlendEffectDataModel.hpp"

using QtNodes::DataModelRegistry;
using QtNodes::FlowScene;
using QtNodes::FlowView;
using QtNodes::Node;

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
  QFile file(":Style.json");
  if (!file.open(QIODevice::ReadOnly))
  {
    qWarning() << "Couldn't open Style.json";
    return;
  }
  QString style = file.readAll();

  QtNodes::FlowViewStyle::setStyle(style);
  QtNodes::NodeStyle::setNodeStyle(style);
  QtNodes::ConnectionStyle::setConnectionStyle(style);
}

} //namespace


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  ::setStyle();

  auto scene = new FlowScene(registerDataModels(), this);
  ui->effectNodeView->setScene(scene);


  connect(scene, &FlowScene::nodeContextMenu, this, [](Node& n, const QPointF& pos) {
    qInfo() << "context menu of node: " << n.nodeDataModel()->name() << " @ " << pos;
  });
  connect(scene, &FlowScene::focusNodeChanged, this, [](Node* newFocus, Node* oldFocus) {
    qInfo() << "node focus changed: from" <<
      (oldFocus ? oldFocus->nodeDataModel()->name() : "null") << " to " <<
      (newFocus ? newFocus->nodeDataModel()->name() : "null");
  });
  connect(scene, &FlowScene::selectedNodeChanged, this, [](std::vector<Node*> nodes) {
    QString selected("selected nodes = ");
    for (auto* node : nodes) {
      selected += node->nodeDataModel()->name();
    }
    qDebug() << selected;
  });

  int screenHeight = QGuiApplication::primaryScreen()->size().height();
  ui->imageNodeViewSplitter->setSizes({screenHeight*2/3, screenHeight*1/3});
  int screenWidth = QGuiApplication::primaryScreen()->size().width();
  ui->effectUISplitter->setSizes({screenWidth*3/4, screenWidth*1/4});

  setWindowTitle("FxFlow");
}

MainWindow::~MainWindow() {
  delete ui;
}

