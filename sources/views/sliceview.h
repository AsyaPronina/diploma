#ifndef SLICEVIEW_H
#define SLICEVIEW_H

#include <view.h>
#include <propertyview.h>
#include "interfaces/views/isliceview.h"

namespace Ui {
class SliceView;
}

class SliceView : public QWidget, public ISliceView
{
    Q_OBJECT
    Q_INTERFACES(ISliceView)

public:
    explicit SliceView(QWidget *parent = Q_NULLPTR);
    void setSliceImage(QImage *tomogramImage) Q_DECL_OVERRIDE;
    void paint() Q_DECL_OVERRIDE;
    void showView() Q_DECL_OVERRIDE;
    void hideView() Q_DECL_OVERRIDE;
    ~SliceView();

signals:
    void viewClosed() Q_DECL_OVERRIDE;

signals:
    void scrollbarChanged(int delta) Q_DECL_OVERRIDE;

private:
    Ui::SliceView *m_ui;
};

#endif // SLICEVIEW_H
