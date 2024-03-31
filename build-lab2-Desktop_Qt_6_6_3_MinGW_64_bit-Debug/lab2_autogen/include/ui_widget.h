/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QListView *rightEl;
    QPushButton *navigateToParentDirectory;
    QListView *leftEl;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->setWindowModality(Qt::NonModal);
        Widget->resize(961, 532);
        Widget->setWindowTitle(QString::fromUtf8("System File Viewer"));
        Widget->setStyleSheet(QString::fromUtf8("background-color: grey; "));
        rightEl = new QListView(Widget);
        rightEl->setObjectName("rightEl");
        rightEl->setGeometry(QRect(360, 20, 581, 491));
        rightEl->setStyleSheet(QString::fromUtf8("background-color: LightGrey;\n"
"padding: 30px 25px;"));
        rightEl->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        rightEl->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        rightEl->setAutoScroll(true);
        rightEl->setTabKeyNavigation(true);
        rightEl->setProperty("showDropIndicator", QVariant(false));
        rightEl->setDragEnabled(false);
        rightEl->setDragDropOverwriteMode(false);
        rightEl->setDragDropMode(QAbstractItemView::NoDragDrop);
        rightEl->setAlternatingRowColors(false);
        rightEl->setProperty("isWrapping", QVariant(false));
        navigateToParentDirectory = new QPushButton(Widget);
        navigateToParentDirectory->setObjectName("navigateToParentDirectory");
        navigateToParentDirectory->setGeometry(QRect(30, 30, 31, 21));
        navigateToParentDirectory->setFocusPolicy(Qt::NoFocus);
        navigateToParentDirectory->setStyleSheet(QString::fromUtf8("border: none;\n"
"background-color: lightGrey;\n"
"color: black;\n"
"font-size: 20px;\n"
""));
        navigateToParentDirectory->setAutoDefault(false);
        navigateToParentDirectory->setFlat(false);
        leftEl = new QListView(Widget);
        leftEl->setObjectName("leftEl");
        leftEl->setGeometry(QRect(20, 20, 321, 491));
        leftEl->setStyleSheet(QString::fromUtf8("background-color: LightGrey;\n"
"padding:  30px 20px;\n"
""));
        leftEl->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        leftEl->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        rightEl->raise();
        leftEl->raise();
        navigateToParentDirectory->raise();

        retranslateUi(Widget);

        navigateToParentDirectory->setDefault(false);


        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        navigateToParentDirectory->setText(QCoreApplication::translate("Widget", "\342\206\220", nullptr));
        (void)Widget;
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
