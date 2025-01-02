#include "canvascontroller.h"
#include <QtQml/qqmlregistration.h>
#include <QDebug>

CanvasController::CanvasController(QObject *parent)
    :m_activeLayer(0), m_height(100), m_width(100), m_x(0), m_y(0), m_zoom(1.0), m_defaultPixelSize(50.0f) {
    // initialize layers
    m_layers = QVector<RasterLayer>();
    // add an initial empty layer
    m_layers.emplaceBack(RasterLayer());

    // debug: add some nodes
    RasterLayer layer = m_layers[0];
    layer.upsert({1, 1}, QColor(255, 0, 0, 255));
    layer.upsert({0, 0}, QColor(0, 255, 0, 255));
    layer.upsert({3, 1}, QColor(0, 0, 255, 255));
    layer.upsert({1, 0}, QColor(255, 255, 0, 255));
    layer.upsert({2, 1}, QColor(0, 255, 255, 255));
    layer.upsert({4, 0}, QColor(255, 0, 255, 255));
    layer.upsert({1, 2}, QColor(255, 0, 0, 255));
}

void CanvasController::drawPixel(int x, int y, QColor c) {
    // get the active layer
    RasterLayer layer = m_layers[m_activeLayer];
    layer.upsert({x, y}, c);
}

void CanvasController::erasePixel(int x, int y) {
    // get the active layer
    RasterLayer layer = m_layers[m_activeLayer];
    layer.remove({x, y});
}

void CanvasController::clearLayer() {
    // get the active layer
    RasterLayer layer = m_layers[m_activeLayer];
    layer.clear();
}

std::optional<PixelRef> CanvasController::getPixel(int x, int y) const {
    // get the active layer
    RasterLayer layer = m_layers[m_activeLayer];
    return layer.get({x, y});
}

QVector<PixelRef> CanvasController::getLayerPixels(int layer) const {
    // get the active layer
    RasterLayer l = m_layers[layer];
}

int CanvasController::width() const { return m_width; }
void CanvasController::setWidth(int width) {
    m_width = clampToNonNegative(width);
    emit widthChanged();
}

int CanvasController::height() const { return m_height; }
void CanvasController::setHeight(int height) {
    m_height = clampToNonNegative(height);
    emit heightChanged();
}

int CanvasController::activeLayer() const { return m_activeLayer; }
void CanvasController::setActiveLayer(int newActiveLayer) {
    m_activeLayer = clampToRange(newActiveLayer, 0, static_cast<int>(m_layers.size()));
    emit activeLayerChanged();
}

// helper functions

int CanvasController::clampToNonNegative(int value) const {
    return std::max(0, value);
}

int CanvasController::clampToRange(int value, int min, int max) const {
    return std::max(min, std::min(max, value));
}

// canvas Controls

float CanvasController::x() const { return m_x; }
void CanvasController::setX(float newX) {
    if (qFuzzyCompare(m_x, newX))
        return;
    m_x = newX;
    emit xChanged();
}
float CanvasController::y() const { return m_y; }
void CanvasController::setY(float newY) {
    if (qFuzzyCompare(m_y, newY))
        return;
    m_y = newY;
    emit yChanged();
}
float CanvasController::zoom() const { return m_zoom; }
void CanvasController::setZoom(float newZoom) {
    if (qFuzzyCompare(m_zoom, newZoom))
        return;
    m_zoom = newZoom;
    emit zoomChanged();
}
