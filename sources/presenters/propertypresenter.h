#ifndef PROPERTYPRESENTER_H
#define PROPERTYPRESENTER_H

#include <QObject>
#include "domainmodel.h"
#include "propertyview.h"

class PropertyPresenter : public QObject
{
    Q_OBJECT

public:
    explicit PropertyPresenter(IPropertyView *);
    void bindView();
    ~PropertyPresenter();
signals:
    void viewClosed();
public slots:
    void updateProperties(int height, int width, int depth, int colorDepth);
private:
    DomainModel *m_model;
    IPropertyView *m_view;
};

#endif // PROPERTYPRESENTER_H
