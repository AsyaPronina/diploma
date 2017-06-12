#include <QImage>
#include <QGraphicsScene>
#include <QPixmap>
#include "slicepresenter.h"

SlicePresenter::SlicePresenter(ISliceView *view, SLICE_AXIS axis):
    m_view(view), m_model(DomainModel::getInstance()), m_axis(axis)
{
    bindView();
    scrollToSlice(0);
}

void SlicePresenter::bindView()
{
    connect(dynamic_cast<QObject *>(m_view), SIGNAL(scrollbarChanged(int)), this, SLOT(scrollToSlice(int)));
}

void SlicePresenter::scrollToSlice(int sliderPos)
{
    int calculatedIndex = 0;//calculateCurrentIndex(sliderPos);
    int min = 0, max;

    ITomogram *ct = m_model->property("originCT").value<ITomogram *>();
    QImage *tomogramImage = new QImage(ct->getColumnsCount(), ct->getRowsCount(), QImage::Format_Grayscale8);

    //TODO: parallel
    switch (m_axis)
    {
    case SLICE_AXIS::XY:
    {
        max = ct->getPlanesCount() - 1;
        calculatedIndex = qBound(min, sliderPos, max);
        for (int i = 0; i < ct->getRowsCount(); ++i)
        {
            for (int j = 0; j < ct->getColumnsCount(); ++j)
            {
                QColor color(*((int *)ct->getValue(i, j, calculatedIndex)));
                tomogramImage->setPixel(j, i, color.rgb());
            }
        }
        break;
    }
    case SLICE_AXIS::XZ:
    {
        max = ct->getRowsCount() - 1;
        calculatedIndex = qBound(min, sliderPos, max);
        for (int i = 0; i < ct->getPlanesCount(); ++i)
        {
            for (int j = 0; j < ct->getColumnsCount(); ++j)
            {
                QColor color(*((int *)ct->getValue(calculatedIndex, j, (ct->getPlanesCount() - 1) - i)));
                tomogramImage->setPixel(j, i, color.rgb());
            }
        }
        break;
    }
    case SLICE_AXIS::YZ:
    {
        max =  ct->getColumnsCount() - 1;
        calculatedIndex = qBound(min, sliderPos, max);
        for (int j = 0; j < ct->getPlanesCount(); ++j)
        {
            for (int i = 0; i < ct->getRowsCount(); ++i)
            {
                QColor color(*((int *)ct->getValue(i, (ct->getColumnsCount() - 1) - calculatedIndex, j)));
                tomogramImage->setPixel(j, i, color.rgb());
            }
        }
        break;
    }
    }

    m_view->setSliceImage(tomogramImage);
}

SlicePresenter::~SlicePresenter()
{
    delete m_view;
}
