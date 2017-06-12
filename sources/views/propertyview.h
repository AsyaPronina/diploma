#ifndef PROPERTYVIEW_H
#define PROPERTYVIEW_H

#include <QDialog>
#include <QCloseEvent>
#include "interfaces/views/ipropertyview.h"

namespace Ui {
class PropertyView;
}

class PropertyView : public QDialog, public IPropertyView
{
    Q_OBJECT
    Q_INTERFACES(IPropertyView)

public:
    explicit PropertyView(QWidget *parent = Q_NULLPTR);
    void showView() Q_DECL_OVERRIDE;
    void hideView() Q_DECL_OVERRIDE;
    ~PropertyView();

signals:
    void propertiesUpdated(int height, int width, int depth, int colorDepth) Q_DECL_OVERRIDE;
    void viewClosed() Q_DECL_OVERRIDE;

private:
    Ui::PropertyView *m_ui;

private slots:
    void onOkButtonClicked();
};

#endif // PROPERTYVIEW_H
