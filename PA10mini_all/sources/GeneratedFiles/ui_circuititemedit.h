/********************************************************************************
** Form generated from reading UI file 'circuititemedit.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CIRCUITITEMEDIT_H
#define UI_CIRCUITITEMEDIT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CircuitItemEdit
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *uDimLabel;
    QLabel *fNameLabel;
    QLabel *nameLabel;
    QLabel *iDimLabel;
    QLabel *u0Label;
    QLabel *i0Label;
    QLineEdit *i0Edit;
    QLineEdit *u0Edit;
    QLineEdit *fEdit;
    QLabel *fDimLabel;
    QLineEdit *nameEdit;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *okButton;

    void setupUi(QWidget *CircuitItemEdit)
    {
        if (CircuitItemEdit->objectName().isEmpty())
            CircuitItemEdit->setObjectName(QString::fromUtf8("CircuitItemEdit"));
        CircuitItemEdit->resize(230, 149);
        verticalLayout = new QVBoxLayout(CircuitItemEdit);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        uDimLabel = new QLabel(CircuitItemEdit);
        uDimLabel->setObjectName(QString::fromUtf8("uDimLabel"));

        gridLayout->addWidget(uDimLabel, 3, 2, 1, 1);

        fNameLabel = new QLabel(CircuitItemEdit);
        fNameLabel->setObjectName(QString::fromUtf8("fNameLabel"));

        gridLayout->addWidget(fNameLabel, 4, 0, 1, 1);

        nameLabel = new QLabel(CircuitItemEdit);
        nameLabel->setObjectName(QString::fromUtf8("nameLabel"));

        gridLayout->addWidget(nameLabel, 1, 0, 1, 1);

        iDimLabel = new QLabel(CircuitItemEdit);
        iDimLabel->setObjectName(QString::fromUtf8("iDimLabel"));

        gridLayout->addWidget(iDimLabel, 2, 2, 1, 1);

        u0Label = new QLabel(CircuitItemEdit);
        u0Label->setObjectName(QString::fromUtf8("u0Label"));

        gridLayout->addWidget(u0Label, 2, 0, 1, 1);

        i0Label = new QLabel(CircuitItemEdit);
        i0Label->setObjectName(QString::fromUtf8("i0Label"));

        gridLayout->addWidget(i0Label, 3, 0, 1, 1);

        i0Edit = new QLineEdit(CircuitItemEdit);
        i0Edit->setObjectName(QString::fromUtf8("i0Edit"));
        i0Edit->setMinimumSize(QSize(100, 0));
        i0Edit->setMaximumSize(QSize(120, 16777215));

        gridLayout->addWidget(i0Edit, 3, 1, 1, 1);

        u0Edit = new QLineEdit(CircuitItemEdit);
        u0Edit->setObjectName(QString::fromUtf8("u0Edit"));
        u0Edit->setMinimumSize(QSize(100, 0));
        u0Edit->setMaximumSize(QSize(120, 16777215));

        gridLayout->addWidget(u0Edit, 2, 1, 1, 1);

        fEdit = new QLineEdit(CircuitItemEdit);
        fEdit->setObjectName(QString::fromUtf8("fEdit"));
        fEdit->setMinimumSize(QSize(100, 0));
        fEdit->setMaximumSize(QSize(120, 16777215));

        gridLayout->addWidget(fEdit, 4, 1, 1, 1);

        fDimLabel = new QLabel(CircuitItemEdit);
        fDimLabel->setObjectName(QString::fromUtf8("fDimLabel"));

        gridLayout->addWidget(fDimLabel, 4, 2, 1, 1);

        nameEdit = new QLineEdit(CircuitItemEdit);
        nameEdit->setObjectName(QString::fromUtf8("nameEdit"));
        nameEdit->setMinimumSize(QSize(100, 0));
        nameEdit->setMaximumSize(QSize(120, 16777215));

        gridLayout->addWidget(nameEdit, 1, 1, 1, 1);

        gridLayout->setColumnStretch(0, 3);
        gridLayout->setColumnStretch(1, 2);

        verticalLayout->addLayout(gridLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        okButton = new QPushButton(CircuitItemEdit);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        horizontalLayout->addWidget(okButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(CircuitItemEdit);
        QObject::connect(okButton, SIGNAL(clicked()), CircuitItemEdit, SLOT(apply()));

        QMetaObject::connectSlotsByName(CircuitItemEdit);
    } // setupUi

    void retranslateUi(QWidget *CircuitItemEdit)
    {
        CircuitItemEdit->setWindowTitle(QApplication::translate("CircuitItemEdit", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213", 0, QApplication::UnicodeUTF8));
        uDimLabel->setText(QApplication::translate("CircuitItemEdit", "A", 0, QApplication::UnicodeUTF8));
        fNameLabel->setText(QString());
        nameLabel->setText(QApplication::translate("CircuitItemEdit", "Name", 0, QApplication::UnicodeUTF8));
        iDimLabel->setText(QApplication::translate("CircuitItemEdit", "V", 0, QApplication::UnicodeUTF8));
        u0Label->setText(QApplication::translate("CircuitItemEdit", "U(0)", 0, QApplication::UnicodeUTF8));
        i0Label->setText(QApplication::translate("CircuitItemEdit", "I(0)", 0, QApplication::UnicodeUTF8));
        fDimLabel->setText(QApplication::translate("CircuitItemEdit", "F", 0, QApplication::UnicodeUTF8));
        okButton->setText(QApplication::translate("CircuitItemEdit", "Ok", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CircuitItemEdit: public Ui_CircuitItemEdit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CIRCUITITEMEDIT_H
