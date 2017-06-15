#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>

#include "interfaces/views/imainview.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public IMainView
{
    Q_OBJECT
    Q_INTERFACES(IMainView)

signals:
    void openRawFilePressed() Q_DECL_OVERRIDE;

public:
    explicit MainWindow(QWidget *parent = 0);
    void showView() Q_DECL_OVERRIDE;
    void hideView() Q_DECL_OVERRIDE;
    ISliceView *getSliceView(SLICE_AXIS) const Q_DECL_OVERRIDE;
    IVolumeView *getVolumeView() const Q_DECL_OVERRIDE;
    ~MainWindow();

signals:
    void viewClosed() Q_DECL_OVERRIDE;

private:
    Ui::MainWindow *m_ui;
};

#endif // MAINWINDOW_H
