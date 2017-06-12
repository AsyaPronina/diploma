#ifndef IVIEW_H
#define IVIEW_H

class IView
{
public:
    virtual ~IView() = default;
    virtual void showView() = 0;
    virtual void hideView() = 0;

signals:
    virtual void viewClosed() = 0;
};

Q_DECLARE_INTERFACE(IView, "IView")

#endif // IVIEW_H
