#ifndef RASTERLAYER_H
#define RASTERLAYER_H

#include <avltree.h>
#include <QColor>
#include <QVector2D>

// A single pixel (without any of the node shit)
struct PixelRef {
    QPoint location;
    std::reference_wrapper<QColor> value;

    PixelRef(int x, int y, QColor& color)
        : location{x, y}, value{color} {}

    PixelRef(QPoint l, QColor& color)
        : location{l}, value{color} {}
};

class RasterLayer
{

    typedef AVLTree<int, QColor> Column;

private:
    // stores essentially "columns" of pixels
    AVLTree<int, Column> pixelData_;
    int size_;
    QString name_;
    bool visible_;

public:
    // constructor destructor ---------------------------
    RasterLayer();
    RasterLayer(const RasterLayer& other);
    ~RasterLayer();

    // accessors ---------------------------

    // return the number of pixels in the layer
    int size() const;

    // return if there is a pixel at location k
    bool contains(const QPoint loc) const;

    // return the pixel at location. If there is no pixel at location k, return nil
    std::optional<PixelRef> get(const QPoint loc) const;
    // return all pixels within a given region. If there are no pixels in the region, return an empty vector
    QVector<PixelRef> get(const int x1, const int x2, const int y1, const int y2) const;
    QVector<PixelRef> get(const QRect boundingBox) const;

    // mutators ---------------------------

    // clear the layer
    void clear();

    // update the pixel at location k with value v. If the pixel does not exist, do nothing
    void update(const QPoint loc, const QColor c);

    // insert a pixel at location k with value v. If the pixel already exists, update the pixel
    void upsert(const QPoint loc, const QColor c);

    // remove the pixel at location k. If the pixel does not exist, do nothing
    void remove(const QPoint loc);

    // other functions ---------------------------

    // write the tree in string format
    std::string toString() const;
};

#endif // RASTERLAYER_H
