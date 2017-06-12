#include "domainmodel.h"

int g(float);
int g(float);

DomainModel::DomainModel()
{
    m_originCTData = new Tomogram();
    m_segmentedCTData = new Tomogram();
}

ITomogram *DomainModel::getOriginCT() const
{
    return m_originCTData;
}

ITomogram *DomainModel::getSegmentedCT() const
{
    return m_segmentedCTData;
}

void DomainModel::setSizes(int height, int width, int depth, int colorDepth)
{
    m_originCTData->setRowsCount(height);
    m_segmentedCTData->setRowsCount(height);

    m_originCTData->setColumnsCount(width);
    m_segmentedCTData->setColumnsCount(width);

    m_originCTData->setPlanesCount(depth);
    m_segmentedCTData->setPlanesCount(depth);

    m_originCTData->setColorDepth(static_cast<Tomogram::ColorDepth>(colorDepth));
    m_segmentedCTData->setColorDepth(static_cast<Tomogram::ColorDepth>(colorDepth));
}

void DomainModel::loadRawData(QFile *ctFile)
{
    QByteArray byteArray = ctFile->readAll();

    size_t size = m_originCTData->getRowsCount() * m_originCTData->getColumnsCount()
                  * m_originCTData->getPlanesCount();

    unsigned char *tmpBuffer = new unsigned char[size * m_originCTData->getColorDepth()];
    memcpy(tmpBuffer, (unsigned char *)byteArray.data(), size * m_originCTData->getColorDepth());

    m_originCTData->setData(tmpBuffer);
}

DomainModel *DomainModel::getInstance()
{
    static DomainModel instance;
    return &instance;
}
