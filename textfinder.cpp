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
    
//    QMetaObject::connectSlotsByName(this);
    connect(ui_lineEdit, SIGNAL(textEdited(QString)), this, SLOT(any_button_pressed(QString)));

    // put this in other thread
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
    search_result.clear();

    auto check = [&](const QByteArray& qb) {
        return (s_matcher.indexIn((qb)) != -1);
    };

    QFuture<QByteArray> s_r = QtConcurrent::filtered(data, check);
    auto s_r_results = s_r.results();
//    if (s_r_results.size() > 1000) {

//    }
    ui_textEdit->setPlainText(QString(s_r_results.join('\n')));

//    foreach (const auto& item, data) {
//        int match = s_matcher.indexIn(item);
//        if (match != -1) {
//            // put string with highlited pattern into buffer
//            // print this buffer at the end;
//            search_result.append(item + '\n');
//        }
//    }
//    ui_textEdit->clear();
//    ui_textEdit->setText(search_result);
}
//void TextFinder::on_findButton_clicked()
//{
//    QString searchString = ui_lineEdit->text();
//    QTextDocument *document = ui_textEdit->document();

//    bool found = false;

//    // undo previous change (if any)
//    document->undo();

//    if (searchString.isEmpty()) {
//        QMessageBox::information(this, tr("Empty Search Field"),
//                                 tr("The search field is empty. "
//                                    "Please enter a word and click Find."));
//    } else {
//        QTextCursor highlightCursor(document);
//        QTextCursor cursor(document);

//        cursor.beginEditBlock();

//        QTextCharFormat plainFormat(highlightCursor.charFormat());
//        QTextCharFormat colorFormat = plainFormat;
//        colorFormat.setForeground(Qt::red);

//        while (!highlightCursor.isNull() && !highlightCursor.atEnd()) {
//            highlightCursor = document->find(searchString, highlightCursor,
//                                             QTextDocument::FindWholeWords);

//            if (!highlightCursor.isNull()) {
//                found = true;
//                highlightCursor.movePosition(QTextCursor::WordRight,
//                                             QTextCursor::KeepAnchor);
//                highlightCursor.mergeCharFormat(colorFormat);
//            }
//        }

//        cursor.endEditBlock();

//        if (found == false) {
//            QMessageBox::information(this, tr("Word Not Found"),
//                                     tr("Sorry, the word cannot be found."));
//        }
//    }
//}
