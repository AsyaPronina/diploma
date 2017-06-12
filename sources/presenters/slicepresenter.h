#ifndef SLICEPRESENTER_H
#define SLICEPRESENTER_H

#include <QObject>
#include "domainmodel.h"
#include "interfaces/views/isliceview.h"
#include "global/slice_defs.h"

class SlicePresenter : public QObject
{
    Q_OBJECT

public:
    explicit SlicePresenter(ISliceView *view, SLICE_AXIS axis);
    void bindView();
    ~SlicePresenter();

public slots:
    void scrollToSlice(int sliderPos);

private:
    DomainModel *m_model;
    ISliceView *m_view;
    SLICE_AXIS m_axis;
};

#endif // SLICEPRESENTER_H
