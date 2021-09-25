#pragma once

#include <nodes/NodeDataModel>

#include <QPixmap>

using QtNodes::NodeDataType;
using QtNodes::NodeData;

/// The class can potentially incapsulate any user data which
/// need to be transferred within the Node Editor graph
class PixmapData : public NodeData
{
public:
  static const int THUMBNAIL_SIZE = 128;
public:
  PixmapData() : _pixmap() {}
  explicit PixmapData(const QPixmap& pixmap) : _pixmap(pixmap) {} // NOLINT(modernize-pass-by-value)

  NodeDataType type() const override {
    return NodeDataType {"pixmap", "Pixmap"};
  }

  QPixmap& pixmap() { return _pixmap; }
  void setPixmap(const QPixmap& pixmap) { _pixmap = pixmap; }

private:
  QPixmap _pixmap;
};
