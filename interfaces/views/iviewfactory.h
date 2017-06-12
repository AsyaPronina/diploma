#ifndef IVIEWFACTORY_H
#define IVIEWFACTORY_H

#include "isliceview.h"
#include "ipropertyview.h"

class IViewFactory
{
public:
    virtual ISliceView *createSliceView() = 0;
    virtual IPropertyView *createPropertyView() = 0;
    virtual ~IViewFactory() { }
};

Q_DECLARE_INTERFACE(IViewFactory, "IViewFactory")

#endif // IVIEWFACTORY_H
