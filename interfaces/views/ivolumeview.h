#ifndef IVOLUMEVIEW_H
#define IVOLUMEVIEW_H

#include <cstdlib>
#include "iview.h"

class IVolumeView : public IView
{
public:
    virtual void provideData(size_t height, size_t width, size_t depth, int depthOfColor, const unsigned char* data) = 0;
};

Q_DECLARE_INTERFACE(IVolumeView, "IVolumeView")

#endif // IVOLUMEVIEW_H
