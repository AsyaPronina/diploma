#ifndef MAINPRESENTER_H
#define MAINPRESENTER_H

#include <QObject>

#include "views/viewfactory.h"
#include "views/mainwindow.h"
#include "presenters/propertypresenter.h"
#include "presenters/slicepresenter.h"

class MainPresenter : public QObject
{
    Q_OBJECT

public:
    explicit MainPresenter(MainWindow *);

private slots:
    void paint();
    void openRawFile();
    void loadRawData();

private:
    void bindView();
    void initializeTomogram();
    bool openFileDialog(QString, QFile &);
    //bool adjustSize();

    DomainModel *m_model;
    MainWindow *m_view; //must be IMainView

    PropertyPresenter *m_propertyPresenter;
    SlicePresenter *m_xyAxisSlicePresenter,
                   *m_xzAxisSlicePresenter,
                   *m_yzAxisSlicePresenter;

    QFile *m_ctFile;
};

#endif // MAINPRESENTER_H
