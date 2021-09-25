#include "ImageSourceDataModel.hpp"

#include <QApplication>
#include <QtCore/QJsonValue>
#include <QtGui/QDoubleValidator>
#include <QPushButton>
#include <QDebug>
#include <QFileDialog>
#include <QStandardPaths>
#include <QImageReader>
#include <QMessageBox>
#include <QGuiApplication>

#include "PixmapData.hpp"

namespace {
void initializeImageFileDialog(QFileDialog &dialog) {
  static bool firstDialog = true;

  if (firstDialog) {
    firstDialog = false;
    auto picturesFolders = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
    dialog.setDirectory(picturesFolders.isEmpty() ? QDir::currentPath() : picturesFolders.last());
  }

  QStringList mimeTypeFilters;
  const QByteArrayList supportedMimeTypes = QImageReader::supportedMimeTypes();
  for (const auto &type: supportedMimeTypes) {
    mimeTypeFilters.append(type);
  }
  mimeTypeFilters.sort();
  dialog.setMimeTypeFilters(mimeTypeFilters);
  dialog.selectMimeTypeFilter("image/jpeg");
}
}


ImageSourceDataModel::ImageSourceDataModel() {
  _imageButton = new QPushButton("");
  _imageButton->setFixedSize(QSize(PixmapData::THUMBNAIL_SIZE, PixmapData::THUMBNAIL_SIZE));
  _imageButton->setIconSize(QSize(PixmapData::THUMBNAIL_SIZE, PixmapData::THUMBNAIL_SIZE));
  _imageButton->setToolTip("click to load image");
  _imageButton->setToolTipDuration(1000);
  _imageButton->setFlat(true);
  _imageButton->setStyleSheet(
      "QPushButton { background-color: transparent }"
      "QPushButton:hover:pressed { background-color: rgb(32, 32, 32) }"
  );

  connect(_imageButton, &QPushButton::clicked,
          this, &ImageSourceDataModel::onImageButtonClicked);

  loadImage(":/images/SunnyDay.jpg");
//  loadImage("/home/andy/DevHome/externals/nodeeditor/examples/fxflow/resources/SunnyDay.jpg");
}


QJsonObject ImageSourceDataModel::save() const {
  QJsonObject modelJson = NodeDataModel::save();

//  if (_number) {
//    modelJson["number"] = QString::number(_number->number());
//  }

  return modelJson;
}


void ImageSourceDataModel::restore(QJsonObject const &p) {
//  QJsonValue v = p["number"];
//
//  if (!v.isUndefined()) {
//    QString strNum = v.toString();
//
//    bool ok;
//    double d = strNum.toDouble(&ok);
//    if (ok) {
//      _number = std::make_shared<PixmapData>(d);
//      _lineEdit->setText(strNum);
//    }
//  }
}


unsigned int ImageSourceDataModel::nPorts(PortType portType) const {
  unsigned int result = 1;

  switch (portType) {
    case PortType::In:
      result = 0;
      break;
    case PortType::Out:
      result = 1;
      break;
    default:
      break;
  }

  return result;
}

void ImageSourceDataModel::onImageButtonClicked(bool) {
  qDebug() << "load button clicked";

  QFileDialog dialog(nullptr, tr("Load Image"));
  initializeImageFileDialog(dialog);

  while (dialog.exec() == QDialog::Accepted && !loadImage(dialog.selectedFiles().constFirst())) {}

  Q_EMIT dataUpdated(0);
}


NodeDataType ImageSourceDataModel::dataType(PortType, PortIndex) const {
  return PixmapData().type();
}


std::shared_ptr<NodeData> ImageSourceDataModel::outData(PortIndex) {
  return _pixmapData;
}

QWidget *ImageSourceDataModel::embeddedWidget() {
  return _imageButton;
}

bool ImageSourceDataModel::loadImage(const QString &fileName) {
  const QImage newImage(fileName);
  if (newImage.isNull()) {
    QMessageBox::information(qApp->activeWindow(), QGuiApplication::applicationDisplayName(),
                             tr("Cannot load %1").arg(QDir::toNativeSeparators(fileName)));
    return false;
  }
  if (!_pixmapData) {
    _pixmapData = std::make_shared<PixmapData>();
  }

  _pixmapData->pixmap().convertFromImage(newImage);
  _imageButton->setIcon(QIcon(_pixmapData->pixmap()));

  return true;
}
