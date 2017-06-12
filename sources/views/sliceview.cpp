#include "sliceview.h"
#include "ui_sliceview.h"

SliceView::SliceView(QWidget *parent):
    QWidget(parent),
    m_ui(new Ui::SliceView())
{
    m_ui->setupUi(this);
    connect(m_ui->verticalScrollBar, SIGNAL(valueChanged(int)), this, SIGNAL(scrollbarChanged(int)));
}

void SliceView::setSliceImage(QImage *tomogramImage)
{
    QGraphicsScene *scene = new QGraphicsScene(this);
    QPixmap pixmap = QPixmap::fromImage(*tomogramImage);
    scene->addPixmap(pixmap);
    m_ui->graphicsView->setScene(scene);
}

void SliceView::paint()
{ }

void SliceView::showView()
{
    this->show();
}

void SliceView::hideView()
{
    this->hide();
}

SliceView::~SliceView()
{
    delete m_ui;
}
