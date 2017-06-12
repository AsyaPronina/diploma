#ifndef VIEW_H
#define VIEW_H

#include <QWidget>
#include "interfaces/views/iview.h"

template <class T> class View : public QWidget, public IView
{

public:
    explicit View(QWidget *parent, T *ui);
    void showView() Q_DECL_OVERRIDE;
    void hideView() Q_DECL_OVERRIDE;
    ~View() Q_DECL_OVERRIDE;

protected:
    T *m_ui;
};

#endif // VIEW_H
