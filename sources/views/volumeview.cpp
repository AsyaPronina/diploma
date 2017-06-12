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
    m_program(Q_NULLPTR)
{

}

void VolumeView::showView()
{
    this->show();
}

void VolumeView::hideView()
{
    this->hide();
}

void VolumeView::provideData(size_t height, size_t width, size_t depth, int depthOfColor, const unsigned char* data)
{
 //dummy
}

VolumeView::~VolumeView()
{

}

void VolumeView::initializeGL()
{
    initializeOpenGLFunctions();

    createBoundingBox();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    QOpenGLShader *vshader = new QOpenGLShader(QOpenGLShader::Vertex, this);
    const char *vsrc =
        "in vec4 vertex;\n"
        "uniform mat4 mvp_matrix;\n"
        "void main(void)\n"
        "{\n"
        "    gl_Position = mvp_matrix * vertex;\n"
        "}\n";
    vshader->compileSourceCode(vsrc);

    QOpenGLShader *fshader = new QOpenGLShader(QOpenGLShader::Fragment, this);
    const char *fsrc =
        "void main(void)\n"
        "{\n"
        "    gl_FragColor = vec4(0.3, 0.3, 0.3, 0);\n"
        "}\n";
    fshader->compileSourceCode(fsrc);

    m_program = new QOpenGLShaderProgram;
    m_program->addShader(vshader);
    m_program->addShader(fshader);
    m_program->link();

    m_program->bind();
}

void VolumeView::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 matrix;
    matrix.translate(0.0, 0.0, -5.0);
    matrix.rotate(m_rotation.x() / 16.0f, 1.0f, 0.0f, 0.0f);
    matrix.rotate(m_rotation.y() / 16.0f, 0.0f, 1.0f, 0.0f);
    matrix.rotate(m_rotation.z() / 16.0f, 0.0f, 0.0f, 1.0f);

    m_program->setUniformValue("mvp_matrix", m_projection * matrix);
    int vertexLocation = m_program->attributeLocation("vertex");
    m_program->enableAttributeArray(vertexLocation);
    m_program->setAttributeBuffer(vertexLocation, GL_FLOAT, 0, 3, 3 * sizeof(GLfloat));

    for (int i = 0; i < FACES; ++i)
    {
        glDrawArrays(GL_TRIANGLE_FAN, i * FACE_VERTEX, FACE_VERTEX);
    }
}

//FOR FUTURE
void VolumeView::resizeGL(int w, int h)
{
    qreal aspect = qreal(w) / qreal(h ? h : 1);
    const qreal zNear = 3.0, zFar = 7.0, fov = 45.0;

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

    m_rotation += QVector3D(8 * dy, 8 * dx, 0);
    update();

    m_mousePosition.setX(e->pos().x());
    m_mousePosition.setY(e->pos().y());
}

void VolumeView::createBoundingBox()
{
    int size = FACES * FACE_VERTEX * VERTEX_COMPONENTS;

    static const GLfloat coords[FACES][FACE_VERTEX][VERTEX_COMPONENTS] = {
        { { +1.f, -1.f, -1.f }, { -1.f, -1.f, -1.f }, { -1.f, +1.f, -1.f }, { +1.f, +1.f, -1.f } },
        { { +1.f, +1.f, -1.f }, { -1.f, +1.f, -1.f }, { -1.f, +1.f, +1.f }, { +1.f, +1.f, +1.f } },
        { { +1.f, -1.f, +1.f }, { +1.f, -1.f, -1.f }, { +1.f, +1.f, -1.f }, { +1.f, +1.f, +1.f } },
        { { -1.f, -1.f, -1.f }, { -1.f, -1.f, +1.f }, { -1.f, +1.f, +1.f }, { -1.f, +1.f, -1.f } },
        { { +1.f, -1.f, +1.f }, { -1.f, -1.f, +1.f }, { -1.f, -1.f, -1.f }, { +1.f, -1.f, -1.f } },
        { { -1.f, -1.f, +1.f }, { +1.f, -1.f, +1.f }, { +1.f, +1.f, +1.f }, { -1.f, +1.f, +1.f } }
    };

    m_vbo = new QOpenGLBuffer();
    m_vbo->create();
    m_vbo->bind();
    m_vbo->allocate(coords, size * sizeof(GLfloat));
}
