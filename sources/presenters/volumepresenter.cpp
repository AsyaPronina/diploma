#include "interfaces/model/itomogram.h"
#include "volumepresenter.h"

VolumePresenter::VolumePresenter(IVolumeView *view):
    m_model(DomainModel::getInstance()),
    m_view(view)
{
    ITomogram *ct = m_model->property("originCT").value<ITomogram *>();
    m_view->provideData(ct->getRowsCount(), ct->getColumnsCount(), ct->getPlanesCount(), ct->getColorDepth(), ct->getData());
}
