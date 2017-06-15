#ifndef VOLUMEPRESENTER_H
#define VOLUMEPRESENTER_H

#include <QObject>
#include "domainmodel.h"
#include "interfaces/views/ivolumeview.h"

class VolumePresenter : public QObject
{
    Q_OBJECT

public:
    explicit VolumePresenter(IVolumeView *view);

private:
    DomainModel *m_model;
    IVolumeView *m_view;
};

#endif // VOLUMEPRESENTER_H
