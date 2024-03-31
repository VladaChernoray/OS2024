#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    model = new QFileSystemModel(this);
    model->setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
    model->setRootPath("");
    ui->leftEl->setModel(model);

    textModel = new QStringListModel(this);
    connect(ui->leftEl, &QListView::doubleClicked, this, &Widget::on_leftEl_doubleClicked);
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
        } else {
            listView->setRootIndex(model->index(""));
        }
    } else if (fileInfo.fileName() == ".") {
    } else if (fileInfo.isDir()) {
        listView->setRootIndex(index);
        displayInfoAboutDir(fileInfo);
    } else {
        QString filePath = fileInfo.filePath();
        QString suffix = fileInfo.suffix().toLower();
        if (suffix == "txt") {
            displayTextFileContent(filePath);
        } else if (suffix == "png" || suffix == "jpg") {
            displayImageFileContent(filePath);
        } else if (suffix == "xml") {
            displayXmlFileContent(filePath);
        } else if (suffix == "html") {
            displayHtmlFileContent(filePath);
        }
        else {
            displayInfoAbout(filePath);
        }
    }
}


void Widget::on_navigateToParentDirectory_clicked()
{
    QModelIndex currentIndex = ui->leftEl->rootIndex();
    QModelIndex parentIndex = model->parent(currentIndex);
    if (parentIndex.isValid()) {
        ui->leftEl->setRootIndex(parentIndex);
    } else {
        ui->leftEl->setRootIndex(model->index(""));
    }
}

void Widget::displayTextFileContent(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file:" << filePath;
        return;
    }

    QTextStream in(&file);
    QString fileContent = in.readAll();
    file.close();

    QStringList lines = fileContent.split("\n");

    textModel->setStringList(lines);

    ui->rightEl->setModel(textModel);
}

void Widget::displayImageFileContent(const QString &filePath){

}

void Widget::displayXmlFileContent(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file:" << filePath;
        return;
    }

    QTextStream in(&file);
    QStringList xmlLines;
    xmlLines << "XML File Content:";

    while (!in.atEnd()) {
        QString line = in.readLine();
        xmlLines << line;
    }

    file.close();

    textModel->setStringList(xmlLines);
    ui->rightEl->setModel(textModel);
}


void Widget::displayHtmlFileContent(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file:" << filePath;
        return;
    }

    QTextStream in(&file);
    QStringList htmlLines;
    htmlLines << "HTML File Content:";

    while (!in.atEnd()) {
        QString line = in.readLine();
        htmlLines << line;
    }

    file.close();

    textModel->setStringList(htmlLines);
    ui->rightEl->setModel(textModel);
}

void Widget::displayInfoAbout(const QString &filePath) {
    QFileInfo fileInfo(filePath);

    QStringList fileInfoList;
    fileInfoList << "File Name: " + fileInfo.fileName();
    fileInfoList << "Creation Date: " + fileInfo.birthTime().toString();
    fileInfoList << "Size: " + QString::number(fileInfo.size()) + " bytes";

    textModel->setStringList(fileInfoList);
    ui->rightEl->setModel(textModel);
}


void Widget::displayInfoAboutDir(const QFileInfo &dirInfo) {
    QDir directory(dirInfo.filePath());

    QStringList dirInfoList;
    dirInfoList << "Directory Name: " + dirInfo.fileName();
    dirInfoList << "Creation Date: " + dirInfo.birthTime().toString();

    int fileCount = 0;
    int dirCount = 0;

    QFileInfoList fileList = directory.entryInfoList(QDir::Files);
    for (const QFileInfo& fileInfo : fileList) {
        QString suffix = fileInfo.suffix().toLower();
        if (suffix == "jpg" ||
            suffix == "png" ||
            suffix == "txt" ||
            suffix == "pdf" ||
            suffix == "xml" ||
            suffix == "docx") {
            fileCount++;
        }
    }

    dirCount = directory.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot).count();

    dirInfoList << "Number of files: " + QString::number(fileCount);
    dirInfoList << "Number of subfolders: " + QString::number(dirCount);

    int jpgCount = directory.entryInfoList(QStringList() << "*.jpg", QDir::Files).count();
    int pngCount = directory.entryInfoList(QStringList() << "*.png", QDir::Files).count();
    int txtCount = directory.entryInfoList(QStringList() << "*.txt", QDir::Files).count();
    int pdfCount = directory.entryInfoList(QStringList() << "*.pdf", QDir::Files).count();
    int xmlCount = directory.entryInfoList(QStringList() << "*.xml", QDir::Files).count();
    int docxCount = directory.entryInfoList(QStringList() << "*.docx", QDir::Files).count();

    dirInfoList << "Number of JPG files: " + QString::number(jpgCount);
    dirInfoList << "Number of PNG files: " + QString::number(pngCount);
    dirInfoList << "Number of TXT files: " + QString::number(txtCount);
    dirInfoList << "Number of PDF files: " + QString::number(pdfCount);
    dirInfoList << "Number of XML files: " + QString::number(xmlCount);
    dirInfoList << "Number of DOCX files: " + QString::number(docxCount);

    textModel->setStringList(dirInfoList);
    ui->rightEl->setModel(textModel);
}
