/********************************************************************************
** Form generated from reading UI file 'HostDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.1.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HOSTDIALOG_H
#define UI_HOSTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_HostDialog
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *lblIpAddress;
    QLabel *lblMacAddress;
    QLineEdit *txtIpAddress;
    QLineEdit *txtMacAddress;

    void setupUi(QDialog *HostDialog)
    {
        if (HostDialog->objectName().isEmpty())
            HostDialog->setObjectName(QString::fromUtf8("HostDialog"));
        HostDialog->resize(275, 143);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/host.png"), QSize(), QIcon::Normal, QIcon::Off);
        HostDialog->setWindowIcon(icon);
        buttonBox = new QDialogButtonBox(HostDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(110, 110, 156, 23));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        lblIpAddress = new QLabel(HostDialog);
        lblIpAddress->setObjectName(QString::fromUtf8("lblIpAddress"));
        lblIpAddress->setGeometry(QRect(10, 10, 71, 21));
        lblMacAddress = new QLabel(HostDialog);
        lblMacAddress->setObjectName(QString::fromUtf8("lblMacAddress"));
        lblMacAddress->setGeometry(QRect(9, 60, 71, 21));
        txtIpAddress = new QLineEdit(HostDialog);
        txtIpAddress->setObjectName(QString::fromUtf8("txtIpAddress"));
        txtIpAddress->setEnabled(false);
        txtIpAddress->setGeometry(QRect(100, 10, 151, 20));
        txtMacAddress = new QLineEdit(HostDialog);
        txtMacAddress->setObjectName(QString::fromUtf8("txtMacAddress"));
        txtMacAddress->setEnabled(false);
        txtMacAddress->setGeometry(QRect(100, 60, 151, 20));

        retranslateUi(HostDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, HostDialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, HostDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(HostDialog);
    } // setupUi

    void retranslateUi(QDialog *HostDialog)
    {
        HostDialog->setWindowTitle(QCoreApplication::translate("HostDialog", "Dialog", nullptr));
        lblIpAddress->setText(QCoreApplication::translate("HostDialog", "IP Address", nullptr));
        lblMacAddress->setText(QCoreApplication::translate("HostDialog", "MAC Address", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HostDialog: public Ui_HostDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOSTDIALOG_H
