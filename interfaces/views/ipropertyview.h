#ifndef IPROPERTYVIEW_H
#define IPROPERTYVIEW_H

#include "iview.h"

class IPropertyView : public IView
{
signals:
    virtual void propertiesUpdated(int height, int width, int depth, int colorDepth) = 0;

};

Q_DECLARE_INTERFACE(IPropertyView, "IPropertyView")

#endif // IPROPERTYVIEW_H
