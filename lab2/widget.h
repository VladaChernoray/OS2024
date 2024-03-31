#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFileSystemModel>
#include <QStringListModel>
#include <QStringList>
#include <QDir>
#include <QLabel>
#include <QListWidgetItem>

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

    void displayTextFileContent(const QString &filePath);

    void displayImageFileContent(const QString &filePath);

    void displayXmlFileContent(const QString &filePath);

    void displayHtmlFileContent(const QString &filePath);

    void displayInfoAbout(const QString &filepath);

    void displayInfoAboutDir(const QFileInfo &dirInfo);

private:
    Ui::Widget *ui;
    QFileSystemModel *model;
    QStringListModel *textModel;
    QListWidgetItem *item;
};
#endif // WIDGET_H
