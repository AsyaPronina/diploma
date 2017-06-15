#include "mainpresenter.h"
#include <QMessageBox>
#include <QGraphicsScene>
#include <QButtonGroup>
#include <QFileDialog>
#include <QBrush>
#include <QDebug>
#include <QKeyEvent>
//#include <highgui/highgui.hpp>
//#include <imgproc/imgproc.hpp>
#include <vector>

#include "ui_mainwindow.h"
#include "interfaces/model/itomogram.h"

MainPresenter::MainPresenter(MainWindow *view) :
    m_model(DomainModel::getInstance()),
    m_view(view),
    m_xyAxisSlicePresenter(nullptr),
    m_xzAxisSlicePresenter(nullptr),
    m_yzAxisSlicePresenter(nullptr)
{
    bindView();
    view->showView();
}

void MainPresenter::bindView()
{
    connect(dynamic_cast<QObject *>(m_view), SIGNAL(openRawFilePressed()), this, SLOT(openRawFile()));
}

bool MainPresenter::openFileDialog(QString filter, QFile& file)
{
    QString fileName = QFileDialog::getOpenFileName(dynamic_cast<QWidget *>(m_view), tr("Open File"), QString(), filter);

    if (!fileName.isEmpty())
    {
        file.setFileName(fileName);
        if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::critical(dynamic_cast<QWidget *>(m_view), tr("Error"), tr("Failed to open file"), tr("I see"));
        }

        return true;
    }
    return false;
}

void MainPresenter::openRawFile()
{
    m_ctFile = new QFile();
    if (openFileDialog(tr("*.raw"), *m_ctFile))
    {
        ViewFactory factory;
        //todo: point parent
        IPropertyView *propertyView = factory.createPropertyView();
        m_propertyPresenter = new PropertyPresenter(propertyView);
        this->connect(m_propertyPresenter, SIGNAL(viewClosed()), this, SLOT(loadRawData()));
    }
}

void MainPresenter::loadRawData()
{
    m_model->loadRawData(m_ctFile);

    paint();

    m_ctFile->close();
    m_ctFile->deleteLater();
    m_ctFile = nullptr;

    m_propertyPresenter->deleteLater();
    m_propertyPresenter = nullptr;
}

void MainPresenter::paint()
{
    m_xyAxisSlicePresenter = new SlicePresenter(m_view->getSliceView(SLICE_AXIS::XY), SLICE_AXIS::XY);
    m_xzAxisSlicePresenter = new SlicePresenter(m_view->getSliceView(SLICE_AXIS::XZ), SLICE_AXIS::XZ);
    m_yzAxisSlicePresenter = new SlicePresenter(m_view->getSliceView(SLICE_AXIS::YZ), SLICE_AXIS::YZ);
    m_volumePresenter = new VolumePresenter(m_view->getVolumeView());
}
