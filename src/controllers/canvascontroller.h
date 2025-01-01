#ifndef CANVASCONTROLLER_H
#define CANVASCONTROLLER_H

#include <QObject>
#include <qqmlintegration.h>
#include <rasterlayer.h>

class CanvasController : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

    Q_PROPERTY(int width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(int height READ height WRITE setHeight NOTIFY heightChanged)
    Q_PROPERTY(int activeLayer READ activeLayer WRITE setActiveLayer NOTIFY activeLayerChanged)

public:
    explicit CanvasController(QObject *parent = nullptr);

    Q_INVOKABLE void drawPixel(int x, int y, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
        drawPixel(x, y, QColor(r, g, b, a));
    }
    Q_INVOKABLE void drawPixel(int x, int y, QColor c);
    Q_INVOKABLE void erasePixel(int x, int y);
    Q_INVOKABLE void clearLayer();

    Q_INVOKABLE std::optional<Pixel> getPixel(int x, int y) const;

    int width() const;
    void setWidth(int width);

    int height() const;
    void setHeight(int height);

    int activeLayer() const;
    void setActiveLayer(int newActiveLayer);

signals:
    void widthChanged();
    void heightChanged();
    void activeLayerChanged();

private:
    int m_width;
    int m_height;
    int m_activeLayer;
    QVector<RasterLayer> m_layers;

    // helper functions
    int clampToRange(int value, int min, int max) const;
    int clampToNonNegative(int value) const;
};

#endif // CANVASCONTROLLER_H
