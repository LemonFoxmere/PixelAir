#include "canvascontroller.h"
#include <QtQml/qqmlregistration.h>
#include <QDebug>

CanvasController::CanvasController(QObject *parent)
    :m_activeLayer(0), m_height(100), m_width(100) {
    // initialize layers
    m_layers = QVector<RasterLayer>();
    // add an initial empty layer
    m_layers.emplaceBack(RasterLayer());

    // debug: add some nodes
    RasterLayer layer = m_layers[0];
    layer.upsert({1, 1}, QColor(255, 0, 0, 255));
    layer.upsert({0, 0}, QColor(255, 0, 0, 255));
    layer.upsert({3, 1}, QColor(255, 0, 0, 255));
    layer.upsert({1, 0}, QColor(255, 0, 0, 255));
    layer.upsert({2, 1}, QColor(255, 0, 0, 255));
    layer.upsert({4, 0}, QColor(255, 0, 0, 255));
    layer.upsert({1, 2}, QColor(255, 0, 0, 255));

    qDebug().noquote() << layer.toString();
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

std::optional<Pixel> CanvasController::getPixel(int x, int y) const {
    // get the active layer
    RasterLayer layer = m_layers[m_activeLayer];
    return layer.get({x, y});
}

int CanvasController::width() const { return m_width; }
void CanvasController::setWidth(int width) { m_width = clampToNonNegative(width); }

int CanvasController::height() const { return m_height; }
void CanvasController::setHeight(int height) { m_height = clampToNonNegative(height); }

int CanvasController::activeLayer() const { return m_activeLayer; }
void CanvasController::setActiveLayer(int newActiveLayer) {
    m_activeLayer = clampToRange(newActiveLayer, 0, static_cast<int>(m_layers.size()));
}

// helper functions
int CanvasController::clampToNonNegative(int value) const {
    return std::max(0, value);
}

int CanvasController::clampToRange(int value, int min, int max) const {
    return std::max(min, std::min(max, value));
}
