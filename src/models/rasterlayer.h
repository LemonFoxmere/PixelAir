#ifndef RASTERLAYER_H
#define RASTERLAYER_H

#include <avltree.h>
#include <QColor>
#include <QVector2D>

// A single pixel (without any of the node shit)
struct Pixel {
    QPoint location;
    QColor value;

    Pixel(int x, int y, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
        : location{x, y}, value{QColor(r, g, r, a)} {};
    Pixel(QPoint l, QColor v)
        : location(l), value(v) {};
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
    std::optional<Pixel> get(const QPoint loc) const;
    // return all pixels within a given region. If there are no pixels in the region, return an empty vector
    QVector<Pixel> get(const int x1, const int x2, const int y1, const int y2) const;
    QVector<Pixel> get(const QRect boundingBox) const;

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
