#ifndef TEXTFINDER_H
#define TEXTFINDER_H

#include <QWidget>
#include <QVector>
#include <QByteArray>
#include <QPlainTextEdit>
#include <QFile>
#include <QLineEdit>
#include <QMessageBox>
#include <QTextEdit>
#include <QTextStream>
#include <QUiLoader>
#include <QVBoxLayout>
#include <QByteArrayMatcher>
#include <QFuture>
#include <QtConcurrent/QtConcurrentFilter>
#include <QtConcurrent/QtConcurrentRun>
#include <QList>

QT_BEGIN_NAMESPACE
class QLineEdit;
class QTextEdit;
QT_END_NAMESPACE

class TextFinder : public QWidget
{
    Q_OBJECT

public:
    explicit TextFinder(QWidget *parent = nullptr);

private slots:
    void any_button_pressed(QString s);

private:
    QPlainTextEdit *ui_textEdit;
    QLineEdit *ui_lineEdit;
    QList<QByteArray> data;
};

#endif // TEXTFINDER_H
