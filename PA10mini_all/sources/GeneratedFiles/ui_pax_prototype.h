/********************************************************************************
** Form generated from reading UI file 'pax_prototype.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAX_PROTOTYPE_H
#define UI_PAX_PROTOTYPE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QProgressBar>
#include <QtGui/QSpacerItem>
#include <QtGui/QStackedWidget>
#include <QtGui/QStatusBar>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "equaledit.h"
#include "schemeview.h"

QT_BEGIN_NAMESPACE

class Ui_PAX_PrototypeClass
{
public:
    QAction *action;
    QAction *action_2;
    QAction *action_3;
    QAction *action_4;
    QAction *action_6;
    QAction *action_7;
    QAction *action_8;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QStackedWidget *stackedWidget;
    QWidget *equalMode;
    QVBoxLayout *verticalLayout_2;
    QFrame *frame_1;
    QHBoxLayout *horizontalLayout_2;
    QToolButton *solveButton;
    QToolButton *plotButton;
    QToolButton *openTxtButton;
    QToolButton *createNewButton;
    QToolButton *saveButton;
    QToolButton *saveAsButton;
    QToolButton *undoButton;
    QToolButton *redoButton;
    QSpacerItem *horizontalSpacer;
    QToolButton *editorButton;
    EqualEdit *equalEdit;
    QWidget *schemeMode;
    QVBoxLayout *verticalLayout_3;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout_3;
    QToolButton *solveSchemeButton;
    QToolButton *plotButton_2;
    QToolButton *schemeToTextButton;
    QSpacerItem *horizontalSpacer_2;
    QToolButton *equalButton;
    QFrame *fr;
    QVBoxLayout *verticalLayout_5;
    SchemeView *schemeView;
    QProgressBar *progressBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *PAX_PrototypeClass)
    {
        if (PAX_PrototypeClass->objectName().isEmpty())
            PAX_PrototypeClass->setObjectName(QString::fromUtf8("PAX_PrototypeClass"));
        PAX_PrototypeClass->resize(528, 412);
        PAX_PrototypeClass->setWindowTitle(QString::fromUtf8("PA10mini"));
        QIcon icon;
        icon.addFile(QString::fromUtf8("Resources/main.ico"), QSize(), QIcon::Normal, QIcon::Off);
        PAX_PrototypeClass->setWindowIcon(icon);
        PAX_PrototypeClass->setAnimated(true);
        action = new QAction(PAX_PrototypeClass);
        action->setObjectName(QString::fromUtf8("action"));
        action_2 = new QAction(PAX_PrototypeClass);
        action_2->setObjectName(QString::fromUtf8("action_2"));
        action_3 = new QAction(PAX_PrototypeClass);
        action_3->setObjectName(QString::fromUtf8("action_3"));
        action_4 = new QAction(PAX_PrototypeClass);
        action_4->setObjectName(QString::fromUtf8("action_4"));
        action_6 = new QAction(PAX_PrototypeClass);
        action_6->setObjectName(QString::fromUtf8("action_6"));
        action_7 = new QAction(PAX_PrototypeClass);
        action_7->setObjectName(QString::fromUtf8("action_7"));
        action_8 = new QAction(PAX_PrototypeClass);
        action_8->setObjectName(QString::fromUtf8("action_8"));
        centralWidget = new QWidget(PAX_PrototypeClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        stackedWidget = new QStackedWidget(centralWidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        equalMode = new QWidget();
        equalMode->setObjectName(QString::fromUtf8("equalMode"));
        verticalLayout_2 = new QVBoxLayout(equalMode);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(5, 0, 5, 0);
        frame_1 = new QFrame(equalMode);
        frame_1->setObjectName(QString::fromUtf8("frame_1"));
        frame_1->setFrameShape(QFrame::StyledPanel);
        frame_1->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame_1);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 3, 0, 6);
        solveButton = new QToolButton(frame_1);
        solveButton->setObjectName(QString::fromUtf8("solveButton"));
        solveButton->setMinimumSize(QSize(28, 28));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("Resources/gears.png"), QSize(), QIcon::Normal, QIcon::Off);
        solveButton->setIcon(icon1);
        solveButton->setIconSize(QSize(18, 18));

        horizontalLayout_2->addWidget(solveButton);

        plotButton = new QToolButton(frame_1);
        plotButton->setObjectName(QString::fromUtf8("plotButton"));
        plotButton->setEnabled(false);
        plotButton->setMinimumSize(QSize(28, 28));
        plotButton->setMaximumSize(QSize(28, 28));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8("Resources/curve.png"), QSize(), QIcon::Normal, QIcon::Off);
        plotButton->setIcon(icon2);
        plotButton->setIconSize(QSize(18, 18));

        horizontalLayout_2->addWidget(plotButton);

        openTxtButton = new QToolButton(frame_1);
        openTxtButton->setObjectName(QString::fromUtf8("openTxtButton"));
        openTxtButton->setMinimumSize(QSize(28, 28));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8("Resources/open.png"), QSize(), QIcon::Normal, QIcon::Off);
        openTxtButton->setIcon(icon3);
        openTxtButton->setIconSize(QSize(18, 18));

        horizontalLayout_2->addWidget(openTxtButton);

        createNewButton = new QToolButton(frame_1);
        createNewButton->setObjectName(QString::fromUtf8("createNewButton"));
        createNewButton->setMinimumSize(QSize(28, 28));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8("Resources/document_empty.png"), QSize(), QIcon::Normal, QIcon::Off);
        createNewButton->setIcon(icon4);
        createNewButton->setIconSize(QSize(18, 18));

        horizontalLayout_2->addWidget(createNewButton);

        saveButton = new QToolButton(frame_1);
        saveButton->setObjectName(QString::fromUtf8("saveButton"));
        saveButton->setMinimumSize(QSize(28, 28));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8("Resources/disk.png"), QSize(), QIcon::Normal, QIcon::Off);
        saveButton->setIcon(icon5);
        saveButton->setIconSize(QSize(18, 18));

        horizontalLayout_2->addWidget(saveButton);

        saveAsButton = new QToolButton(frame_1);
        saveAsButton->setObjectName(QString::fromUtf8("saveAsButton"));
        saveAsButton->setMinimumSize(QSize(28, 28));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8("Resources/save_as.png"), QSize(), QIcon::Normal, QIcon::Off);
        saveAsButton->setIcon(icon6);
        saveAsButton->setIconSize(QSize(18, 18));

        horizontalLayout_2->addWidget(saveAsButton);

        undoButton = new QToolButton(frame_1);
        undoButton->setObjectName(QString::fromUtf8("undoButton"));
        undoButton->setEnabled(false);
        undoButton->setMinimumSize(QSize(28, 28));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8("Resources/arrow_undo.png"), QSize(), QIcon::Normal, QIcon::Off);
        undoButton->setIcon(icon7);
        undoButton->setIconSize(QSize(18, 18));

        horizontalLayout_2->addWidget(undoButton);

        redoButton = new QToolButton(frame_1);
        redoButton->setObjectName(QString::fromUtf8("redoButton"));
        redoButton->setEnabled(false);
        redoButton->setMinimumSize(QSize(28, 28));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8("Resources/arrow_redo.png"), QSize(), QIcon::Normal, QIcon::Off);
        redoButton->setIcon(icon8);
        redoButton->setIconSize(QSize(18, 18));

        horizontalLayout_2->addWidget(redoButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        editorButton = new QToolButton(frame_1);
        editorButton->setObjectName(QString::fromUtf8("editorButton"));
        editorButton->setMinimumSize(QSize(28, 28));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8("Resources/high_voltage.png"), QSize(), QIcon::Normal, QIcon::Off);
        editorButton->setIcon(icon9);
        editorButton->setIconSize(QSize(18, 18));

        horizontalLayout_2->addWidget(editorButton);


        verticalLayout_2->addWidget(frame_1);

        equalEdit = new EqualEdit(equalMode);
        equalEdit->setObjectName(QString::fromUtf8("equalEdit"));

        verticalLayout_2->addWidget(equalEdit);

        stackedWidget->addWidget(equalMode);
        schemeMode = new QWidget();
        schemeMode->setObjectName(QString::fromUtf8("schemeMode"));
        verticalLayout_3 = new QVBoxLayout(schemeMode);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(5, 0, 5, 0);
        frame_2 = new QFrame(schemeMode);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        horizontalLayout_3 = new QHBoxLayout(frame_2);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 3, 0, 6);
        solveSchemeButton = new QToolButton(frame_2);
        solveSchemeButton->setObjectName(QString::fromUtf8("solveSchemeButton"));
        solveSchemeButton->setMinimumSize(QSize(28, 28));
        solveSchemeButton->setMaximumSize(QSize(28, 28));
        solveSchemeButton->setIcon(icon1);
        solveSchemeButton->setIconSize(QSize(18, 18));

        horizontalLayout_3->addWidget(solveSchemeButton);

        plotButton_2 = new QToolButton(frame_2);
        plotButton_2->setObjectName(QString::fromUtf8("plotButton_2"));
        plotButton_2->setEnabled(false);
        plotButton_2->setMinimumSize(QSize(28, 28));
        plotButton_2->setMaximumSize(QSize(28, 28));
        plotButton_2->setIcon(icon2);
        plotButton_2->setIconSize(QSize(18, 18));

        horizontalLayout_3->addWidget(plotButton_2);

        schemeToTextButton = new QToolButton(frame_2);
        schemeToTextButton->setObjectName(QString::fromUtf8("schemeToTextButton"));
        schemeToTextButton->setMinimumSize(QSize(28, 28));
        schemeToTextButton->setMaximumSize(QSize(28, 28));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8("Resources/text_document.png"), QSize(), QIcon::Normal, QIcon::Off);
        schemeToTextButton->setIcon(icon10);
        schemeToTextButton->setIconSize(QSize(18, 18));

        horizontalLayout_3->addWidget(schemeToTextButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        equalButton = new QToolButton(frame_2);
        equalButton->setObjectName(QString::fromUtf8("equalButton"));
        equalButton->setMinimumSize(QSize(28, 28));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8("Resources/text.png"), QSize(), QIcon::Normal, QIcon::Off);
        equalButton->setIcon(icon11);
        equalButton->setIconSize(QSize(18, 18));

        horizontalLayout_3->addWidget(equalButton);


        verticalLayout_3->addWidget(frame_2);

        fr = new QFrame(schemeMode);
        fr->setObjectName(QString::fromUtf8("fr"));
        fr->setAutoFillBackground(false);
        fr->setStyleSheet(QString::fromUtf8("QFrame{\n"
"	background-color: rgb(255, 255, 255);\n"
"	border-color: rgb(100,100,100);\n"
"	border-width: 1px;\n"
"}\n"
""));
        fr->setFrameShape(QFrame::StyledPanel);
        fr->setFrameShadow(QFrame::Sunken);
        fr->setLineWidth(1);
        fr->setMidLineWidth(1);
        verticalLayout_5 = new QVBoxLayout(fr);
        verticalLayout_5->setSpacing(15);
        verticalLayout_5->setContentsMargins(15, 15, 15, 15);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        schemeView = new SchemeView(fr);
        schemeView->setObjectName(QString::fromUtf8("schemeView"));

        verticalLayout_5->addWidget(schemeView);


        verticalLayout_3->addWidget(fr);

        stackedWidget->addWidget(schemeMode);

        verticalLayout->addWidget(stackedWidget);

        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(0);
        progressBar->setTextVisible(false);

        verticalLayout->addWidget(progressBar);

        PAX_PrototypeClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(PAX_PrototypeClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        statusBar->setAutoFillBackground(false);
        statusBar->setStyleSheet(QString::fromUtf8("background-color: rgb(245, 245, 245);"));
        PAX_PrototypeClass->setStatusBar(statusBar);

        retranslateUi(PAX_PrototypeClass);
        QObject::connect(editorButton, SIGNAL(clicked()), PAX_PrototypeClass, SLOT(activateSchemeMode()));
        QObject::connect(equalButton, SIGNAL(clicked()), PAX_PrototypeClass, SLOT(activateEqualMode()));
        QObject::connect(equalEdit, SIGNAL(redoAvailable(bool)), redoButton, SLOT(setEnabled(bool)));
        QObject::connect(equalEdit, SIGNAL(undoAvailable(bool)), undoButton, SLOT(setEnabled(bool)));
        QObject::connect(saveAsButton, SIGNAL(clicked()), equalEdit, SLOT(saveAs()));
        QObject::connect(saveButton, SIGNAL(clicked()), equalEdit, SLOT(save()));
        QObject::connect(createNewButton, SIGNAL(clicked()), equalEdit, SLOT(createNew()));
        QObject::connect(redoButton, SIGNAL(clicked()), equalEdit, SLOT(redo()));
        QObject::connect(undoButton, SIGNAL(clicked()), equalEdit, SLOT(undo()));
        QObject::connect(solveButton, SIGNAL(clicked()), PAX_PrototypeClass, SLOT(solve()));
        QObject::connect(openTxtButton, SIGNAL(clicked()), equalEdit, SLOT(open()));
        QObject::connect(plotButton, SIGNAL(clicked()), PAX_PrototypeClass, SLOT(openPlot()));
        QObject::connect(plotButton_2, SIGNAL(clicked()), PAX_PrototypeClass, SLOT(openPlot()));
        QObject::connect(solveSchemeButton, SIGNAL(clicked()), PAX_PrototypeClass, SLOT(solve()));
        QObject::connect(schemeToTextButton, SIGNAL(clicked()), PAX_PrototypeClass, SLOT(schemeToText()));

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(PAX_PrototypeClass);
    } // setupUi

    void retranslateUi(QMainWindow *PAX_PrototypeClass)
    {
        action->setText(QApplication::translate("PAX_PrototypeClass", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214", 0, QApplication::UnicodeUTF8));
        action_2->setText(QApplication::translate("PAX_PrototypeClass", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214", 0, QApplication::UnicodeUTF8));
        action_3->setText(QApplication::translate("PAX_PrototypeClass", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        action_4->setText(QApplication::translate("PAX_PrototypeClass", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\272\320\260\320\272", 0, QApplication::UnicodeUTF8));
        action_6->setText(QApplication::translate("PAX_PrototypeClass", "\320\222\321\213\321\205\320\276\320\264", 0, QApplication::UnicodeUTF8));
        action_7->setText(QApplication::translate("PAX_PrototypeClass", "\320\236\321\202\320\274\320\265\320\275\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        action_8->setText(QApplication::translate("PAX_PrototypeClass", "\320\237\320\276\320\262\321\202\320\276\321\200\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        solveButton->setToolTip(QApplication::translate("PAX_PrototypeClass", "\320\235\320\260\321\207\320\260\321\202\321\214 \320\262\321\213\321\207\320\270\321\201\320\273\320\265\320\275\320\270\321\217", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        solveButton->setStatusTip(QApplication::translate("PAX_PrototypeClass", "\320\235\320\260\321\207\320\260\321\202\321\214 \320\270\320\275\321\202\320\265\320\263\321\200\320\270\321\200\320\276\320\262\320\260\320\275\320\270\320\265 \321\201\320\270\321\201\321\202\320\265\320\274\321\213 \321\203\321\200\320\260\320\262\320\275\320\265\320\275\320\270\320\271", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        solveButton->setText(QApplication::translate("PAX_PrototypeClass", "\320\240\320\265\321\210\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
        plotButton->setText(QApplication::translate("PAX_PrototypeClass", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        openTxtButton->setToolTip(QApplication::translate("PAX_PrototypeClass", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214 \321\204\320\260\320\271\320\273", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        openTxtButton->setStatusTip(QApplication::translate("PAX_PrototypeClass", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214 \321\204\320\260\320\271\320\273", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        openTxtButton->setText(QApplication::translate("PAX_PrototypeClass", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        createNewButton->setToolTip(QApplication::translate("PAX_PrototypeClass", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        createNewButton->setStatusTip(QApplication::translate("PAX_PrototypeClass", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214 \320\275\320\276\320\262\321\213\320\271 \321\204\320\260\320\271\320\273", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        createNewButton->setText(QApplication::translate("PAX_PrototypeClass", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        saveButton->setToolTip(QApplication::translate("PAX_PrototypeClass", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        saveButton->setStatusTip(QApplication::translate("PAX_PrototypeClass", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \321\204\320\260\320\271\320\273", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        saveButton->setText(QApplication::translate("PAX_PrototypeClass", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        saveAsButton->setToolTip(QApplication::translate("PAX_PrototypeClass", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\272\320\260\320\272", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        saveAsButton->setStatusTip(QApplication::translate("PAX_PrototypeClass", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \321\204\320\260\320\271\320\273 \320\272\320\260\320\272", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        saveAsButton->setText(QApplication::translate("PAX_PrototypeClass", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        undoButton->setToolTip(QApplication::translate("PAX_PrototypeClass", "\320\236\321\202\320\274\320\265\320\275\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        undoButton->setStatusTip(QApplication::translate("PAX_PrototypeClass", "\320\236\321\202\320\274\320\265\320\275\320\270\321\202\321\214 \320\270\320\267\320\274\320\265\320\275\320\265\320\275\320\270\321\217", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        undoButton->setText(QApplication::translate("PAX_PrototypeClass", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        redoButton->setToolTip(QApplication::translate("PAX_PrototypeClass", "\320\237\320\276\320\262\321\202\320\276\321\200\320\270\321\202\321\214", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        redoButton->setStatusTip(QApplication::translate("PAX_PrototypeClass", "\320\237\320\276\320\262\321\202\320\276\321\200\320\270\321\202\321\214 \320\270\320\267\320\274\320\265\320\275\320\265\320\275\320\270\321\217", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        redoButton->setText(QString());
        editorButton->setText(QString());
        solveSchemeButton->setText(QString());
        plotButton_2->setText(QString());
        schemeToTextButton->setText(QString());
        equalButton->setText(QString());
        Q_UNUSED(PAX_PrototypeClass);
    } // retranslateUi

};

namespace Ui {
    class PAX_PrototypeClass: public Ui_PAX_PrototypeClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAX_PROTOTYPE_H
