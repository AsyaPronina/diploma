#ifndef IMAINVIEW_H
#define IMAINVIEW_H

#include "iview.h"
#include "isliceview.h"
#include "global/slice_defs.h"
#include "ivolumeview.h"

class IMainView : public IView
{
public:
    virtual ISliceView *getSliceView(SLICE_AXIS) const = 0;
    virtual IVolumeView *getVolumeView() const = 0;
signals:
    virtual void openRawFilePressed() = 0;
};

Q_DECLARE_INTERFACE(IMainView, "IMainView")


#endif // IMAINVIEW_H
