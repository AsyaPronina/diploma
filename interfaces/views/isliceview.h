#ifndef ISLICEVIEW_H
#define ISLICEVIEW_H

#include "iview.h"

class ISliceView : public IView
{
public:
    virtual void setSliceImage(QImage *) = 0;
    virtual void paint() = 0;

signals:
    virtual void scrollbarChanged(int) = 0;
};

Q_DECLARE_INTERFACE(ISliceView, "ISliceView")

#endif // ISLICEVIEW_H
