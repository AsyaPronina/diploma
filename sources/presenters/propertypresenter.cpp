#include <QVariant>

#include "tomogram.h"
#include "propertypresenter.h"

PropertyPresenter::PropertyPresenter(IPropertyView *view):
    m_model(DomainModel::getInstance()),
    m_view(view)
{
    bindView();
    m_view->showView();
}

void PropertyPresenter::bindView()
{
    connect(dynamic_cast<QObject *>(m_view), SIGNAL(viewClosed()), this, SIGNAL(viewClosed()));
    connect(dynamic_cast<QObject *>(m_view), SIGNAL(propertiesUpdated(int, int, int, int)), this, SLOT(updateProperties(int, int, int, int)));
}

void PropertyPresenter::updateProperties(int height, int width, int depth, int colorDepth)
{
    m_model->setSizes(height, width, depth, colorDepth);
}

PropertyPresenter::~PropertyPresenter()
{
    delete m_view;
}
