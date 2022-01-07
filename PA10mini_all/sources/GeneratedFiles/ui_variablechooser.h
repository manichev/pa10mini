/********************************************************************************
** Form generated from reading UI file 'variablechooser.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VARIABLECHOOSER_H
#define UI_VARIABLECHOOSER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QFormLayout>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QScrollArea>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VariableChooser
{
public:
    QVBoxLayout *verticalLayout_2;
    QFrame *horizontalFrame;
    QHBoxLayout *horizontalLayout_4;
    QCheckBox *checkBox;
    QScrollArea *scrollArea;
    QWidget *layout;
    QHBoxLayout *horizontalLayout_2;
    QFormLayout *formLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;

    void setupUi(QWidget *VariableChooser)
    {
        if (VariableChooser->objectName().isEmpty())
            VariableChooser->setObjectName(QString::fromUtf8("VariableChooser"));
        VariableChooser->setWindowModality(Qt::WindowModal);
        VariableChooser->resize(200, 317);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(VariableChooser->sizePolicy().hasHeightForWidth());
        VariableChooser->setSizePolicy(sizePolicy);
        VariableChooser->setMinimumSize(QSize(200, 200));
        VariableChooser->setMaximumSize(QSize(200, 400));
        verticalLayout_2 = new QVBoxLayout(VariableChooser);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalFrame = new QFrame(VariableChooser);
        horizontalFrame->setObjectName(QString::fromUtf8("horizontalFrame"));
        horizontalFrame->setFrameShape(QFrame::Panel);
        horizontalFrame->setFrameShadow(QFrame::Raised);
        horizontalLayout_4 = new QHBoxLayout(horizontalFrame);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(20, 5, 5, 5);
        checkBox = new QCheckBox(horizontalFrame);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        horizontalLayout_4->addWidget(checkBox);


        verticalLayout_2->addWidget(horizontalFrame);

        scrollArea = new QScrollArea(VariableChooser);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setFrameShape(QFrame::NoFrame);
        scrollArea->setWidgetResizable(true);
        scrollArea->setAlignment(Qt::AlignCenter);
        layout = new QWidget();
        layout->setObjectName(QString::fromUtf8("layout"));
        layout->setGeometry(QRect(0, 0, 200, 253));
        horizontalLayout_2 = new QHBoxLayout(layout);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(20, 10, 20, 0);
        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));

        horizontalLayout_2->addLayout(formLayout);

        scrollArea->setWidget(layout);

        verticalLayout_2->addWidget(scrollArea);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(5, 6, 6, 6);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton = new QPushButton(VariableChooser);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout->addWidget(pushButton);


        verticalLayout_2->addLayout(horizontalLayout);


        retranslateUi(VariableChooser);
        QObject::connect(pushButton, SIGNAL(clicked()), VariableChooser, SLOT(apply()));
        QObject::connect(checkBox, SIGNAL(stateChanged(int)), VariableChooser, SLOT(selectAll(int)));

        QMetaObject::connectSlotsByName(VariableChooser);
    } // setupUi

    void retranslateUi(QWidget *VariableChooser)
    {
        VariableChooser->setWindowTitle(QApplication::translate("VariableChooser", "\320\222\321\213\320\262\320\265\321\201\321\202\320\270:", 0, QApplication::UnicodeUTF8));
        checkBox->setText(QApplication::translate("VariableChooser", "Select all", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("VariableChooser", "\320\236\320\272", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class VariableChooser: public Ui_VariableChooser {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VARIABLECHOOSER_H
