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
#include "interfaces/views/ivolumeview.h"

class VolumeView : public QOpenGLWidget, public IVolumeView, protected QOpenGLFunctions
{
    Q_OBJECT
    Q_INTERFACES(IVolumeView)

public:
    explicit VolumeView(QWidget *parent = Q_NULLPTR);
    void showView() Q_DECL_OVERRIDE;
    void hideView() Q_DECL_OVERRIDE;
    void provideData(size_t height, size_t width, size_t depth, int depthOfColor, const unsigned char* data) Q_DECL_OVERRIDE;
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

    QOpenGLBuffer *m_vbo;
    QOpenGLShaderProgram *m_program;
    QMatrix4x4 m_projection;
    QVector3D m_rotation;
    QVector2D m_mousePosition;
    QVector3D m_rotationAxis;
    qreal m_angularSpeed;
};

#endif // VOLUMEVIEW_H
