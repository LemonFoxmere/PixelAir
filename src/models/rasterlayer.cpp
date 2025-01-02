#include "rasterlayer.h"
#include <QtCore/qdebug.h>
#include <sstream>

// constructor destructor ---------------------------

RasterLayer::RasterLayer() {
    pixelData_ = AVLTree<int, Column>();
    size_ = 0;
    name_ = "New Layer";
    visible_ = true;
}

RasterLayer::RasterLayer(const RasterLayer& other)
    : pixelData_(other.pixelData_){
    size_ = other.size_;
    name_ = other.name_;
    visible_ = other.visible_;
}

RasterLayer::~RasterLayer() {
    clear();
}

int RasterLayer::size() const { return size_; }

bool RasterLayer::contains(const QPoint loc) const {
    auto column = pixelData_.get(loc.x());
    if (!column.has_value())
        return false;
    return column.value().get().contains(loc.y());
}

std::optional<PixelRef> RasterLayer::get(const QPoint loc) const {
    auto column = pixelData_.get(loc.x());
    if (!column.has_value())
        return std::nullopt;

    auto c = column.value().get().get(loc.y());
    if (!c.has_value())
        return std::nullopt;

    return PixelRef(loc, std::ref(c.value()));
}

QVector<PixelRef> RasterLayer::get(const int x1, const int x2, const int y1, const int y2) const {
    if (x1 > x2 || y1 > y2) return {}; // invalid bounding box
    QVector<PixelRef> pixels;

    auto columns = pixelData_.getRange(x1, x2);
    for (int i = 0; i < columns.length(); i++) {
        int x = columns[i].first;
        auto yPixels = columns[i].second.get().getRange(y1, y2);
        for (int j = 0; j < yPixels.length(); j++) {
            int y = yPixels[j].first;
            QColor c = yPixels[j].second;
            pixels.emplaceBack(QPoint(x, y), std::ref(c));
        }
    }

    return pixels;
}

QVector<PixelRef> RasterLayer::get(const QRect boundingBox) const {
    if (boundingBox.isEmpty()) return {}; // sanity check

    return get(
        boundingBox.left(),
        boundingBox.right(),
        boundingBox.top(),
        boundingBox.bottom());
}

void RasterLayer::clear() {
    pixelData_.clear();
    size_ = 0;
}

void RasterLayer::update(const QPoint loc, const QColor c) {
    auto column = pixelData_.get(loc.x());
    if (!column.has_value()) return; // do nothing

    column.value().get().update(loc.y(), c);
}

void RasterLayer::upsert(const QPoint loc, const QColor c) {
    auto column = pixelData_.get(loc.x());
    if (!column.has_value()) { // if the col doesnt exist yet, make a new one
        Column newColumn = AVLTree<int, QColor>();
        newColumn.upsert(loc.y(), c);
        pixelData_.upsert(loc.x(), newColumn);
        size_++; // increment size since we added a new pixel
        return;
    }

    if(!column.value().get().contains(loc.y())){
        size_++; // if the pixel is new, increment
    }
    column.value().get().upsert(loc.y(), c); // normal upsert
}

void RasterLayer::remove(const QPoint loc) {
    auto column = pixelData_.get(loc.x());
    if (!column.has_value()) return; // do nothing

    if(column.value().get().contains(loc.y())) size_--; // if the pixel exists, decrement)
    column.value().get().remove(loc.y());

    if (column.value().get().size() == 0) { // if the col becomes empty, delete it
        pixelData_.remove(loc.x());
    }
}

// mainly for debug use. Prints out the tree structure
std::string RasterLayer::toString() const {
    std::ostringstream oss;

    oss << "RasterLayer: " << name_.toStdString() << std::endl;
    oss << "Pixel Count: " << size_ << std::endl;
    oss << "Visible: " << (visible_ ? "true" : "false") << std::endl;
    oss << std::endl << "====================================" << std::endl << std::endl;
    oss << "Pixel Data [Columns]: " << std::endl;

    // print out the column tree structure
    oss << pixelData_.toString([](const int& k) -> std::string {
        return "x=" + std::to_string(k);
    }) << std::endl;

    oss << "Pixel Data [Per Column]: " << std::endl;

    // get all columns and print out the pixel tree structure
    auto columns = pixelData_.getRange(INT_MIN, INT_MAX);
    for (int i = 0; i < columns.length(); i++) {
        int x = columns[i].first;
        auto c = columns[i].second;
        oss << "Column x=" << std::to_string(x) << " [size=" << c.get().size() << "] : " << std::endl;
        oss << c.get().toString([](const int& k) -> std::string {
            return "y=" + std::to_string(k);
        }) << std::endl;
    }

    return oss.str();
}


