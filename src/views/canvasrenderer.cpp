#include "canvasrenderer.h"

#include <gradientshader.h>
#include <QSGFlatColorMaterial>
#include <QSGGeometry>
#include <QSGGeometryNode>

CanvasRenderer::CanvasRenderer() {
    setFlag(ItemHasContents, true);
}

// render
QSGNode *CanvasRenderer::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *data) {
    QSGGeometryNode* node = static_cast<QSGGeometryNode*>(oldNode);
    if(!oldNode) {
        QSGGeometry *geometry = new QSGGeometry(QSGGeometry::defaultAttributes_TexturedPoint2D(), 3);
        geometry->setDrawingMode(QSGGeometry::DrawTriangles);
        GradientMaterial *material = new GradientMaterial();

        node = new QSGGeometryNode;

        node->setGeometry(geometry);
        node->setFlag(QSGNode::OwnsGeometry);
        node->setMaterial(material);
        node->setFlag(QSGNode::OwnsMaterial);
    }

    QSGGeometry* geometry = node->geometry();
    QSGGeometry::TexturedPoint2D *vertices = geometry->vertexDataAsTexturedPoint2D();
    vertices[0].set(width() / 2.0, 0, 0.5, 1); // top center
    vertices[1].set(0, height(), 0, 0); // bottom left
    vertices[2].set(width(), height(), 1, 0); // bottom right


    node->markDirty(QSGNode::DirtyGeometry | QSGNode::DirtyMaterial);

    return node;
}
