#include "canvasrenderer.h"

#include <QSGFlatColorMaterial>
#include <QSGGeometry>
#include <QSGSimpleRectNode>

CanvasRenderer::CanvasRenderer() {
    setFlag(ItemHasContents, true);
}

// render
QSGNode *CanvasRenderer::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *data) {
    QSGSimpleRectNode* node = static_cast<QSGSimpleRectNode*>(oldNode);
    if(!oldNode) {
        // QSGGeometry *geometry = new QSGGeometry(QSGGeometry::defaultAttributes_TexturedPoint2D(), 6);
        // geometry->setDrawingMode(QSGGeometry::DrawTriangles);
        // GradientMaterial *material = new GradientMaterial();

        // node = new QSGGeometryNode;
        node = new QSGSimpleRectNode();
        node->setColor("white");
    }

    int size = 100;
    node->setRect(QRectF(width()/2-size/2, height()/2-size/2, size, size));
    node->markDirty(QSGNode::DirtyGeometry | QSGNode::DirtyMaterial);

    return node;
}
