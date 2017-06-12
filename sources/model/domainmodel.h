#ifndef DOMAINMODEL_H
#define DOMAINMODEL_H

#include <QObject>
#include <QPair>
#include <QFile>
#include "tomogram.h"

class DomainModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(ITomogram *originCT READ getOriginCT NOTIFY originCTChanged)
    Q_PROPERTY(ITomogram *segmentedCT READ getSegmentedCT NOTIFY segmentedCTChanged)

public:
    DomainModel(DomainModel&) = delete;
    void operator=(DomainModel&) = delete;

    static DomainModel *getInstance();

    ITomogram *getOriginCT() const;
    ITomogram *getSegmentedCT() const;

    void setSizes(int height, int width, int depth, int colorDepth);
    void loadRawData(QFile *ctFile);

signals:
    //as arguments I want to pass ranges of indeces.
    void originCTChanged(QPair<int, int> iRange, QPair<int, int> jRange, QPair<int, int> kRange);
    void segmentedCTChanged(QPair<int, int> iRange, QPair<int, int> jRange, QPair<int, int> kRange);

private:
    DomainModel();

    Tomogram *m_originCTData = nullptr;
    Tomogram *m_segmentedCTData = nullptr;
    //for 3DView and 3DPresenter
    //BINGO!
    //and more decorators for half-displaying must be created in presenters of view with volume rendering!!
};

#endif // DOMAINMODEL_H
