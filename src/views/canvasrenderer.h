#ifndef CANVASRENDERER_H
#define CANVASRENDERER_H

#include <QObject>
#include <QQuickItem>

class CanvasRenderer : public QQuickItem
{
    Q_OBJECT
    QML_ELEMENT

public:
    CanvasRenderer();

protected:
    QSGNode* updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *data) override;

signals:
};

#endif // CANVASRENDERER_H
