#ifndef VOLUMEVIEW_H
#define VOLUMEVIEW_H

#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include <QVector2D>
#include <QVector4D>
#include <QOpenGLWidget>
#include <QMouseEvent>
#include <QPair>
#include "interfaces/views/ivolumeview.h"

class VolumeView : public QOpenGLWidget, public IVolumeView, protected QOpenGLFunctions
{
    Q_OBJECT
    Q_INTERFACES(IVolumeView)

public:
    explicit VolumeView(QWidget *parent = Q_NULLPTR);
    void showView() Q_DECL_OVERRIDE;
    void hideView() Q_DECL_OVERRIDE;
    void provideData(size_t height, size_t width, size_t depth, int depthOfColor, const void *data) Q_DECL_OVERRIDE;
    ~VolumeView();

signals:
    void viewClosed() Q_DECL_OVERRIDE;

private:
    void initializeGL() Q_DECL_OVERRIDE;
    void resizeGL(int w, int h) Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void createBoundingBox();
    void createTexture(int height, int width, int depth, int depthOfColor, const void *data);
    void updateTexture(int height, int width, int depth, int depthOfColor, const void *data);

    QOpenGLBuffer *m_vbo;
    GLuint m_texture;

    QOpenGLShaderProgram *m_program;

    QVector3D m_rotation;
    QMatrix4x4 m_projection;
    QVector2D m_mousePosition;
};

#endif // VOLUMEVIEW_H
