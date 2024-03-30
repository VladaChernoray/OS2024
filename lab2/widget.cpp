#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    model = new QFileSystemModel(this);
    model->setFilter(QDir::AllEntries);
    model->setRootPath(QDir::rootPath());
    ui->leftEl->setModel(model);
    ui->rightEl->setModel(model);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_leftEl_doubleClicked(const QModelIndex &index)
{
    QListView* listView = qobject_cast<QListView*>(sender());
    if (!listView)
        return;

    QFileInfo fileInfo = model->fileInfo(index);
    if (fileInfo.fileName() == "..") {
        QModelIndex parentIndex = index.parent();
        if (parentIndex.isValid()) {
            listView->setRootIndex(parentIndex);
        }
    } else if (fileInfo.fileName() == ".") {
    } else if (fileInfo.isDir()) {
        listView->setRootIndex(index);
    }
}

void Widget::on_navigateToParentDirectory_clicked()
{
    QModelIndex currentIndex = ui->leftEl->rootIndex();
    QModelIndex parentIndex = model->parent(currentIndex);
    if (parentIndex.isValid()) {
        ui->leftEl->setRootIndex(parentIndex);
    }
}

void Widget::displayTextFileContent(const QString &filePath){}



