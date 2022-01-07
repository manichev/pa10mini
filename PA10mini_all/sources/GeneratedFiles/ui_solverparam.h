/********************************************************************************
** Form generated from reading UI file 'solverparam.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SOLVERPARAM_H
#define UI_SOLVERPARAM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SolverParam
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout_2;
    QCheckBox *tCheckBox;
    QLineEdit *t0LineEdit;
    QLabel *label_2;
    QLineEdit *tkLineEdit;
    QLabel *label_1;
    QLineEdit *epsLineEdit;
    QLabel *label_3;
    QLineEdit *hmxLineEdit;
    QLabel *label_4;
    QLabel *label_6;
    QCheckBox *epsCheckBox;
    QLabel *label_5;
    QSpinBox *nmSpinBox;
    QLineEdit *hmnLineEdit;
    QCheckBox *hCheckBox;
    QLabel *label_7;
    QCheckBox *rj2CheckBox;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *okButton;
    QPushButton *pushButton;

    void setupUi(QWidget *SolverParam)
    {
        if (SolverParam->objectName().isEmpty())
            SolverParam->setObjectName(QString::fromUtf8("SolverParam"));
        SolverParam->resize(317, 216);
        verticalLayout = new QVBoxLayout(SolverParam);
        verticalLayout->setSpacing(10);
        verticalLayout->setContentsMargins(5, 5, 5, 5);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setHorizontalSpacing(10);
        gridLayout_2->setContentsMargins(-1, 0, -1, -1);
        tCheckBox = new QCheckBox(SolverParam);
        tCheckBox->setObjectName(QString::fromUtf8("tCheckBox"));
        tCheckBox->setEnabled(true);
        tCheckBox->setStyleSheet(QString::fromUtf8("QCheckBox::indicator{\n"
"width:16px;\n"
"height:16px;\n"
"}\n"
"QCheckBox::indicator:checked {\n"
"	image: url(\"Resources/tick.png\");\n"
"}\n"
"QCheckBox::indicator:unchecked {\n"
"	image: url(\"Resources/cross.png\");\n"
"}\n"
""));
        tCheckBox->setIconSize(QSize(16, 16));
        tCheckBox->setCheckable(true);
        tCheckBox->setChecked(false);

        gridLayout_2->addWidget(tCheckBox, 0, 2, 1, 1);

        t0LineEdit = new QLineEdit(SolverParam);
        t0LineEdit->setObjectName(QString::fromUtf8("t0LineEdit"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(t0LineEdit->sizePolicy().hasHeightForWidth());
        t0LineEdit->setSizePolicy(sizePolicy);
        t0LineEdit->setMinimumSize(QSize(80, 20));
        t0LineEdit->setMaximumSize(QSize(80, 20));
        t0LineEdit->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        t0LineEdit->setDragEnabled(true);

        gridLayout_2->addWidget(t0LineEdit, 0, 1, 1, 1);

        label_2 = new QLabel(SolverParam);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 1, 0, 1, 1);

        tkLineEdit = new QLineEdit(SolverParam);
        tkLineEdit->setObjectName(QString::fromUtf8("tkLineEdit"));
        sizePolicy.setHeightForWidth(tkLineEdit->sizePolicy().hasHeightForWidth());
        tkLineEdit->setSizePolicy(sizePolicy);
        tkLineEdit->setMinimumSize(QSize(80, 20));
        tkLineEdit->setMaximumSize(QSize(80, 20));
        tkLineEdit->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        tkLineEdit->setDragEnabled(true);

        gridLayout_2->addWidget(tkLineEdit, 1, 1, 1, 1);

        label_1 = new QLabel(SolverParam);
        label_1->setObjectName(QString::fromUtf8("label_1"));

        gridLayout_2->addWidget(label_1, 0, 0, 1, 1);

        epsLineEdit = new QLineEdit(SolverParam);
        epsLineEdit->setObjectName(QString::fromUtf8("epsLineEdit"));
        sizePolicy.setHeightForWidth(epsLineEdit->sizePolicy().hasHeightForWidth());
        epsLineEdit->setSizePolicy(sizePolicy);
        epsLineEdit->setMinimumSize(QSize(80, 20));
        epsLineEdit->setMaximumSize(QSize(80, 20));

        gridLayout_2->addWidget(epsLineEdit, 4, 1, 1, 1);

        label_3 = new QLabel(SolverParam);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 2, 0, 1, 1);

        hmxLineEdit = new QLineEdit(SolverParam);
        hmxLineEdit->setObjectName(QString::fromUtf8("hmxLineEdit"));
        sizePolicy.setHeightForWidth(hmxLineEdit->sizePolicy().hasHeightForWidth());
        hmxLineEdit->setSizePolicy(sizePolicy);
        hmxLineEdit->setMinimumSize(QSize(80, 20));
        hmxLineEdit->setMaximumSize(QSize(80, 20));
        hmxLineEdit->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        hmxLineEdit->setDragEnabled(true);

        gridLayout_2->addWidget(hmxLineEdit, 3, 1, 1, 1);

        label_4 = new QLabel(SolverParam);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 3, 0, 1, 1);

        label_6 = new QLabel(SolverParam);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_2->addWidget(label_6, 5, 0, 1, 1);

        epsCheckBox = new QCheckBox(SolverParam);
        epsCheckBox->setObjectName(QString::fromUtf8("epsCheckBox"));
        epsCheckBox->setEnabled(false);
        epsCheckBox->setStyleSheet(QString::fromUtf8("QCheckBox::indicator{\n"
"width:16px;\n"
"height:16px;\n"
"}\n"
"QCheckBox::indicator:checked {\n"
"	image: url(\"Resources/tick.png\");\n"
"}\n"
"QCheckBox::indicator:unchecked {\n"
"	image: url(\"Resources/cross.png\");\n"
"}\n"
""));

        gridLayout_2->addWidget(epsCheckBox, 4, 2, 1, 1);

        label_5 = new QLabel(SolverParam);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_2->addWidget(label_5, 4, 0, 1, 1);

        nmSpinBox = new QSpinBox(SolverParam);
        nmSpinBox->setObjectName(QString::fromUtf8("nmSpinBox"));
        sizePolicy.setHeightForWidth(nmSpinBox->sizePolicy().hasHeightForWidth());
        nmSpinBox->setSizePolicy(sizePolicy);
        nmSpinBox->setMinimumSize(QSize(80, 20));
        nmSpinBox->setMaximumSize(QSize(80, 20));
        nmSpinBox->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        nmSpinBox->setMinimum(1);
        nmSpinBox->setMaximum(3);

        gridLayout_2->addWidget(nmSpinBox, 5, 1, 1, 1);

        hmnLineEdit = new QLineEdit(SolverParam);
        hmnLineEdit->setObjectName(QString::fromUtf8("hmnLineEdit"));
        sizePolicy.setHeightForWidth(hmnLineEdit->sizePolicy().hasHeightForWidth());
        hmnLineEdit->setSizePolicy(sizePolicy);
        hmnLineEdit->setMinimumSize(QSize(80, 20));
        hmnLineEdit->setMaximumSize(QSize(80, 20));
        hmnLineEdit->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        hmnLineEdit->setDragEnabled(true);

        gridLayout_2->addWidget(hmnLineEdit, 2, 1, 1, 1);

        hCheckBox = new QCheckBox(SolverParam);
        hCheckBox->setObjectName(QString::fromUtf8("hCheckBox"));
        hCheckBox->setEnabled(false);
        hCheckBox->setStyleSheet(QString::fromUtf8("QCheckBox::indicator{\n"
"width:16px;\n"
"height:16px;\n"
"}\n"
"QCheckBox::indicator:checked {\n"
"	image: url(\"Resources/tick.png\");\n"
"}\n"
"QCheckBox::indicator:unchecked {\n"
"	image: url(\"Resources/cross.png\");\n"
"}\n"
""));
        hCheckBox->setCheckable(true);

        gridLayout_2->addWidget(hCheckBox, 2, 2, 1, 1);

        label_7 = new QLabel(SolverParam);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_2->addWidget(label_7, 6, 0, 1, 1);

        rj2CheckBox = new QCheckBox(SolverParam);
        rj2CheckBox->setObjectName(QString::fromUtf8("rj2CheckBox"));

        gridLayout_2->addWidget(rj2CheckBox, 6, 1, 1, 1);


        verticalLayout->addLayout(gridLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        okButton = new QPushButton(SolverParam);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        horizontalLayout->addWidget(okButton);

        pushButton = new QPushButton(SolverParam);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout->addWidget(pushButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(SolverParam);
        QObject::connect(t0LineEdit, SIGNAL(textChanged(QString)), SolverParam, SLOT(check()));
        QObject::connect(tkLineEdit, SIGNAL(textChanged(QString)), SolverParam, SLOT(check()));
        QObject::connect(hmxLineEdit, SIGNAL(textChanged(QString)), SolverParam, SLOT(check()));
        QObject::connect(hmnLineEdit, SIGNAL(textChanged(QString)), SolverParam, SLOT(check()));
        QObject::connect(pushButton, SIGNAL(clicked()), SolverParam, SLOT(close()));
        QObject::connect(okButton, SIGNAL(clicked()), SolverParam, SLOT(apply()));
        QObject::connect(epsLineEdit, SIGNAL(textChanged(QString)), SolverParam, SLOT(check()));

        QMetaObject::connectSlotsByName(SolverParam);
    } // setupUi

    void retranslateUi(QWidget *SolverParam)
    {
        SolverParam->setWindowTitle(QApplication::translate("SolverParam", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213 \320\270\320\275\321\202\320\265\320\263\321\200\320\270\321\200\320\276\320\262\320\260\320\275\320\270\321\217", 0, QApplication::UnicodeUTF8));
        tCheckBox->setText(QString());
        t0LineEdit->setText(QString());
        label_2->setText(QApplication::translate("SolverParam", "\320\222\321\200\320\265\320\274\321\217 \320\276\320\272\320\276\320\275\321\207\320\260\320\275\320\270\321\217 \320\270\320\275\321\202\320\265\320\263\321\200\320\270\321\200\320\276\320\262\320\260\320\275\320\270\321\217", 0, QApplication::UnicodeUTF8));
        label_1->setText(QApplication::translate("SolverParam", "\320\222\321\200\320\265\320\274\321\217 \320\275\320\260\321\207\320\260\320\273\320\260 \320\270\320\275\321\202\320\265\320\263\321\200\320\270\321\200\320\276\320\262\320\260\320\275\320\270\321\217", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("SolverParam", "\320\234\320\270\320\275\320\270\320\274\320\260\320\273\321\214\320\275\321\213\320\271 \321\210\320\260\320\263 \320\270\320\275\321\202\320\265\320\263\321\200\320\270\321\200\320\276\320\262\320\260\320\275\320\270\321\217", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("SolverParam", "\320\234\320\260\320\272\321\201\320\270\320\274\320\260\320\273\321\214\320\275\321\213\320\271 \321\210\320\260\320\263 \320\270\320\275\321\202\320\265\320\263\321\200\320\270\321\200\320\276\320\262\320\260\320\275\320\270\321\217", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("SolverParam", "\320\235\320\276\320\274\320\265\321\200 \320\274\320\265\321\202\320\276\320\264\320\260", 0, QApplication::UnicodeUTF8));
        epsCheckBox->setText(QString());
        label_5->setText(QApplication::translate("SolverParam", "\320\242\320\276\321\207\320\275\320\276\321\201\321\202\321\214 \320\270\320\275\321\202\320\265\320\263\321\200\320\270\321\200\320\276\320\262\320\260\320\275\320\270\321\217", 0, QApplication::UnicodeUTF8));
        hCheckBox->setText(QString());
        label_7->setText(QApplication::translate("SolverParam", "\320\222\321\213\321\207\320\270\321\201\320\273\321\217\321\202\321\214 RJ2 \320\260\320\275\320\260\320\273\320\270\321\202\320\270\321\207\320\265\321\201\320\272\320\270", 0, QApplication::UnicodeUTF8));
        rj2CheckBox->setText(QString());
        okButton->setText(QApplication::translate("SolverParam", "\320\236\320\272", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("SolverParam", "\320\236\321\202\320\274\320\265\320\275\320\260", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SolverParam: public Ui_SolverParam {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SOLVERPARAM_H
