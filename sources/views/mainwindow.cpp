#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QButtonGroup>
#include <QFileDialog>
#include <QTextStream>
#include <QBrush>
#include <QDebug>
#include <QKeyEvent>
#include <vector>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);
    QFile file(":/styles/application.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    qApp->setStyleSheet(styleSheet);
    connect(m_ui->actionOpen_Raw_File, SIGNAL(triggered(bool)), this, SIGNAL(openRawFilePressed()));
}

void MainWindow::showView()
{
    this->show();
}

void MainWindow::hideView()
{
    this->hide();
}

ISliceView *MainWindow::getSliceView(SLICE_AXIS sliceAxis) const
{
    switch (sliceAxis)
    {
    case SLICE_AXIS::XY:
        return m_ui->xyAxisSliceWidget;
    case SLICE_AXIS::XZ:
         return m_ui->xzAxisSliceWidget;
    case SLICE_AXIS::YZ:
        return m_ui->yzAxisSliceWidget;
    }
}

MainWindow::~MainWindow()
{
    delete m_ui;
}
