#include "gradientshader.h"

#include <QFile>

GradientShader::GradientShader() {
    setShaderFileName(VertexStage, ":/shaders/src/views/shaders/gradientshader.vert.qsb");
    setShaderFileName(FragmentStage, ":/shaders/src/views/shaders/gradientshader.frag.qsb");

    if (!QFile::exists(":/shaders/src/views/shaders/gradientshader.vert")) {
        qWarning() << "Vertex shader file not found.";
    }
    if (!QFile::exists(":/shaders/src/views/shaders/gradientshader.frag")) {
        qWarning() << "Fragment shader file not found.";
    }
}

bool GradientShader::updateUniformData(RenderState &state, QSGMaterial *newMaterial, QSGMaterial *oldMaterial) {
    Q_UNUSED(newMaterial);
    Q_UNUSED(oldMaterial);

    // Ensure the matrix is set if the combined matrix has changed
    if (state.isMatrixDirty()) {
        QMatrix4x4 matrix = state.combinedMatrix();
        QByteArray *uniformData = state.uniformData();
        memcpy(uniformData->data(), matrix.constData(), sizeof(QMatrix4x4));
    }
    return true;
}

QSGMaterialType *GradientMaterial::type() const {
    static QSGMaterialType gradientMaterialType; // Static instance ensures it's shared across all GradientMaterials
    return &gradientMaterialType;
}

int GradientMaterial::compare(const QSGMaterial *other) const {
    if (this == other) {
        return 0; // The same object
    }

    // Safe cast to GradientMaterial (assuming you only compare the same type)
    const GradientMaterial *o = static_cast<const GradientMaterial *>(other);

    // Compare properties if your material has any (e.g., colors, textures, etc.)
    // If you don't have properties to compare, return -1 or 1
    return 0;
}

QSGMaterialShader *GradientMaterial::createShader(QSGRendererInterface::RenderMode mode) const {
    Q_UNUSED(mode);
    return new GradientShader();
}

