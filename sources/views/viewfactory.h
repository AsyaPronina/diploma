#ifndef VIEWFACTORY_H
#define VIEWFACTORY_H

#include <QObject>
#include "interfaces/views/iviewfactory.h"

class ViewFactory : public QObject, public IViewFactory
{
    Q_OBJECT
    Q_INTERFACES(IViewFactory)

public:
    ISliceView *createSliceView() Q_DECL_OVERRIDE;
    IPropertyView *createPropertyView() Q_DECL_OVERRIDE;
private:
    template <class T>
    T *createView() { return new T(); }
};

#endif // VIEWFACTORY_H
