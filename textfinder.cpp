#include "textfinder.h"

static QWidget* loadUiFile(QWidget *parent)
{
    QFile file(":/forms/textfinder.ui");
    file.open(QIODevice::ReadOnly);

    QUiLoader loader;
    return loader.load(&file, parent);
}

TextFinder::TextFinder(QWidget *parent)
    : QWidget(parent)
{
    QWidget *formWidget = loadUiFile(this);
    ui_textEdit = findChild<QPlainTextEdit*>("plainTextEdit");
    ui_lineEdit = findChild<QLineEdit*>("lineEdit");
    
    connect(ui_lineEdit, SIGNAL(textEdited(QString)), this, SLOT(any_button_pressed(QString)));

    QFile inputFile(":/forms/input.txt");
    inputFile.open(QIODevice::ReadOnly);
    QByteArray raw = inputFile.readAll();
    data = raw.split('\n');
    
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(formWidget);
    setLayout(layout);
    setWindowTitle(tr("Text Finder"));
}

void TextFinder::any_button_pressed(QString s) {
    if (s.isEmpty()) {
        ui_textEdit->clear();
        return;
    }

    QByteArrayMatcher s_matcher(s.toUtf8());

    auto check = [&](const QByteArray& qb) {
        return (s_matcher.indexIn((qb)) != -1);
    };

    QFuture<QByteArray> s_r = QtConcurrent::filtered(data, check);
    auto s_r_results = s_r.results();
    int printed = s_r_results.size();
    int size = s_r_results.size();
    if (s_r_results.size() > 1000) {
        for (int i = 0; i < 1000; ++i) {
            ui_textEdit->appendPlainText(s_r_results[i]);
        }
        printed = 1000;
    } else {
        ui_textEdit->setPlainText(s_r_results.join('\n'));
    }
    ui_textEdit->appendPlainText(QString(printed) + " of " + QString(size));
}
