#include "viewfactory.h"
#include "sliceview.h"
#include "propertyview.h"

ISliceView *ViewFactory::createSliceView()
{
    return nullptr;//return createView<SliceView>();
}

IPropertyView *ViewFactory::createPropertyView()
{
    return createView<PropertyView>();
}
