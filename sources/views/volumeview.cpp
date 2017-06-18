/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/
#include <QOpenGLShader>
#include "volumeview.h"


#define FACES 6
#define FACE_VERTEX 4
#define VERTEX_COMPONENTS 3

VolumeView::VolumeView(QWidget *parent) :
    QOpenGLWidget(parent),
    m_program(Q_NULLPTR),
    m_scaleFactor(0)
{
    m_boundingBox = QPair<QVector3D, QVector3D>(QVector3D(0.f, 0.f, 0.f), QVector3D(1.f, 1.f, 1.f));

    m_projection.setToIdentity();
    m_projection.perspective(45, 1, 0.3f, 60.0f);
}

void VolumeView::showView()
{
    this->show();
}

void VolumeView::hideView()
{
    this->hide();
}

void VolumeView::provideData(size_t height, size_t width, size_t depth, int depthOfColor, const void* data)
{
    updateTexture(height, width, depth, depthOfColor, data);
    update();
}

VolumeView::~VolumeView()
{
    makeCurrent();
    m_vbo->destroy();
    glDeleteTextures(1, &m_texture);
    delete m_program;
    //delete shaders?
    doneCurrent();
}

void VolumeView::initializeGL()
{
    initializeOpenGLFunctions();

    createBoundingBox(m_boundingBox.first, m_boundingBox.second);

    const unsigned char data = (char)0;
    createTexture(1, 1, 1, 1, &data);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    QOpenGLShader *vshader = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vshader->compileSourceFile(":/shaders/vertex_shader.glsl");
    qDebug() << vshader->log();

    QOpenGLShader *fshader = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fshader->compileSourceFile(":/shaders/fragment_shader_volume_ray_casting.glsl");
    qDebug() << fshader->log();

    m_program = new QOpenGLShaderProgram;
    m_program->addShader(vshader);
    m_program->addShader(fshader);
    m_program->link();

    m_program->bind();
}

void VolumeView::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 viewTranslationMatrix;
    viewTranslationMatrix.translate(-.5f, -.5f, -.5f);
    QMatrix4x4 viewInvertedTranslationMatrix;
    viewInvertedTranslationMatrix.translate(.5f, .5f, .5f);

    QMatrix4x4 viewRotationMatrix;
    viewRotationMatrix.rotate(m_rotation.x() / 16.0f, 1.0f, 0.0f, 0.0f);
    viewRotationMatrix.rotate(m_rotation.y() / 16.0f, 0.0f, 1.0f, 0.0f);

    QMatrix4x4 viewRotatedTranslationMatrix;
    viewRotatedTranslationMatrix.translate(0.0f, 0.0f, -2.0f + m_scaleFactor);

    QVector4D camera_position(0.0f, 0.0f, 2.0f - m_scaleFactor, 1.0f);
    camera_position = viewInvertedTranslationMatrix * viewRotationMatrix.inverted() * camera_position;

    m_program->setUniformValue("mvp_matrix", m_projection * viewRotatedTranslationMatrix * viewRotationMatrix * viewTranslationMatrix);
    m_program->setUniformValue("texture_unit", 0);
    m_program->setUniformValue("density", 0.008f);
    m_program->setUniformValue("density_limit", 0.108f);
    m_program->setUniformValue("step_length", 0.003f);
    m_program->setUniformValue("box1", m_boundingBox.first);
    m_program->setUniformValue("box2", m_boundingBox.second);

    //in shader we calculate in World space (in accordance to texture_unit coordinates)
    m_program->setUniformValue("camera_position", camera_position.toVector3D());

    int vertexLocation = m_program->attributeLocation("vertex");
    m_program->enableAttributeArray(vertexLocation);
    m_program->setAttributeBuffer(vertexLocation, GL_FLOAT, 0, 3, 3 * sizeof(GLfloat));

    for (int i = 0; i < FACES; ++i)
    {
        glDrawArrays(GL_TRIANGLE_FAN, i * FACE_VERTEX, FACE_VERTEX);
    }
}

void VolumeView::resizeGL(int w, int h)
{
    qreal aspect = qreal(w) / qreal(h ? h : 1);
    const qreal zNear = 0.3, zFar = 60.0, fov = 45.0;

    m_projection.setToIdentity();
    m_projection.perspective(fov, aspect, zNear, zFar);
}

void VolumeView::mousePressEvent(QMouseEvent *e)
{
    m_mousePosition = QVector2D(e->localPos());
}

void VolumeView::mouseMoveEvent(QMouseEvent *e)
{
    int dx = e->x() - m_mousePosition.x();
    int dy = e->y() - m_mousePosition.y();

    const int speed = 8;
    m_rotation += QVector3D(speed * dy, speed * dx, 0);
    update();

    m_mousePosition.setX(e->pos().x());
    m_mousePosition.setY(e->pos().y());
}

void VolumeView::wheelEvent(QWheelEvent *event)
{
    m_scaleFactor = std::min(0.2f, m_scaleFactor + (event->delta() / 120));
    update();
}

void VolumeView::createBoundingBox(QVector3D topLeft, QVector3D bottomRight)
{
    int size = FACES * FACE_VERTEX * VERTEX_COMPONENTS;

    static const GLfloat coords[FACES][FACE_VERTEX][VERTEX_COMPONENTS] = {
        { { bottomRight.x(), topLeft.y(), topLeft.z() }, { topLeft.x(), topLeft.y(), topLeft.z() }, { topLeft.x(), bottomRight.y(), topLeft.z() }, { bottomRight.x(), bottomRight.y(), topLeft.z() } },
        { { bottomRight.x(), bottomRight.y(), topLeft.z() }, { topLeft.x(), bottomRight.y(), topLeft.z() }, { topLeft.x(), bottomRight.y(), bottomRight.z() }, { bottomRight.x(), bottomRight.y(), bottomRight.z() } },
        { { bottomRight.x(), topLeft.y(), bottomRight.z() }, { bottomRight.x(), topLeft.y(), topLeft.z() }, { bottomRight.x(), bottomRight.y(), topLeft.z() }, { bottomRight.x(), bottomRight.y(), bottomRight.z() } },
        { { topLeft.x(), topLeft.y(), topLeft.z() }, { topLeft.x(), topLeft.y(), bottomRight.z() }, { topLeft.x(), bottomRight.y(), bottomRight.z() }, { topLeft.x(), bottomRight.y(), topLeft.z() } },
        { { bottomRight.x(), topLeft.y(), bottomRight.z() }, { topLeft.x(), topLeft.y(), bottomRight.z() }, { topLeft.x(), topLeft.y(), topLeft.z() }, { bottomRight.x(), topLeft.y(), topLeft.z() } },
        { { topLeft.x(), topLeft.y(), bottomRight.z() }, { bottomRight.x(), topLeft.y(), bottomRight.z() }, { bottomRight.x(), bottomRight.y(), bottomRight.z() }, { topLeft.x(), bottomRight.y(), bottomRight.z() } }
    };

    m_vbo = new QOpenGLBuffer();
    m_vbo->create();
    m_vbo->bind();
    m_vbo->allocate(coords, size * sizeof(GLfloat));
}

void VolumeView::createTexture(int height, int width, int depth, int depthOfColor, const void *data)
{
    glActiveTexture(GL_TEXTURE0);
    glEnable(GL_TEXTURE_3D);

    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_3D, m_texture);

    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP);

    updateTexture(height, width, depth, depthOfColor, data);

    glDisable(GL_TEXTURE_3D);
    glActiveTexture(GL_TEXTURE0);
}

void VolumeView::updateTexture(int height, int width, int depth, int depthOfColor, const void *data)
{
    glBindTexture(GL_TEXTURE_3D, m_texture);

    int internalFormat, textureFormat;
    GLenum type;

    if (depthOfColor == 1)
    {
        internalFormat = GL_LUMINANCE8;
        textureFormat = GL_LUMINANCE;
        type = GL_UNSIGNED_BYTE;

    }
    else
    {
        internalFormat = GL_LUMINANCE16F_ARB;
        textureFormat = GL_LUMINANCE;
        type = GL_UNSIGNED_SHORT;
    }

    static PFNGLTEXIMAGE3DPROC glTexImage3D = (PFNGLTEXIMAGE3DPROC) wglGetProcAddress("glTexImage3D");
    glTexImage3D(GL_TEXTURE_3D, 0, internalFormat, width, height, depth, 0, textureFormat, type, data);
}

