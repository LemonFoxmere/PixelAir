#ifndef GRADIENTSHADER_H
#define GRADIENTSHADER_H

#include <QSGMaterial>
#include <QSGMaterialShader>

class GradientShader : public QSGMaterialShader
{
public:
    GradientShader();
    bool updateUniformData(RenderState &state, QSGMaterial *newMaterial, QSGMaterial *oldMaterial) override;
};

class GradientMaterial : public QSGMaterial
{
public:
    QSGMaterialShader* createShader(QSGRendererInterface::RenderMode mode) const override;
    QSGMaterialType *type() const override;
    int compare(const QSGMaterial *other) const override;
};

#endif // GRADIENTSHADER_H
