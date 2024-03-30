#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFileSystemModel>
#include <QDir>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
private slots:
    void on_leftEl_doubleClicked(const QModelIndex &index);

    void on_navigateToParentDirectory_clicked();

    void on_rightEl_windowIconTextChanged(const QString &iconText);

    void displayTextFileContent(const QString &filePath);

private:
    Ui::Widget *ui;
    QFileSystemModel *model;
};
#endif // WIDGET_H
