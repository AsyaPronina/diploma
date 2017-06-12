#include "propertyview.h"
#include "ui_propertyview.h"

PropertyView::PropertyView(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::PropertyView)
{
    m_ui->setupUi(this);
    setWindowTitle("Properties:");
    connect(m_ui->okButton, SIGNAL(clicked(bool)), this, SLOT(onOkButtonClicked()));
}

void PropertyView::showView()
{
    this->show();
}

void PropertyView::hideView()
{
    this->hide();
}

void PropertyView::onOkButtonClicked()
{
    int colorDepth = m_ui->colorDepthComboBox->currentText().toInt();
    emit propertiesUpdated(m_ui->heightSpinBox->value(), m_ui->widthSpinBox->value(), m_ui->depthSpinBox->value(), colorDepth);
    this->close();
    emit viewClosed();
}

PropertyView::~PropertyView()
{
    delete m_ui;
}
