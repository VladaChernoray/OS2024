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
    QListView *leftEl;
    QListView *rightEl;
    QPushButton *navigateToParentDirectory;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(800, 600);
        leftEl = new QListView(Widget);
        leftEl->setObjectName("leftEl");
        leftEl->setGeometry(QRect(40, 90, 311, 471));
        rightEl = new QListView(Widget);
        rightEl->setObjectName("rightEl");
        rightEl->setGeometry(QRect(380, 90, 391, 471));
        navigateToParentDirectory = new QPushButton(Widget);
        navigateToParentDirectory->setObjectName("navigateToParentDirectory");
        navigateToParentDirectory->setGeometry(QRect(40, 60, 83, 29));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        navigateToParentDirectory->setText(QCoreApplication::translate("Widget", "<-", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
