#include "view.h"

template <class T> View<T>::View(QWidget *parent, T *ui) : QWidget(parent), m_ui(ui)
{
    m_ui->setupUi(this);
}

template <class T> void View<T>::showView()
{
    m_ui->show();
}

template <class T> void View<T>::hideView()
{
    m_ui->hide();
}

template <class T> View<T>::~View()
{
    delete m_ui;
}
