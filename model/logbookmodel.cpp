#include "logbookmodel.h"
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QTextDocument>
#include <QTextBlock>
#include <QTextTable>
#include <QTextTableFormat>
#include <QTextCursor>
#include <QPrinter>

LogbookModel::LogbookModel()
{
    _types << EntryType(0, "Literatuur");
    _types << EntryType(1, "Implementatie");

    QString desc("Dit is een beschrijving. ");
    QString longDesc("Nu is dit een langere beschrijving. ");
    _entries << LogEntry(QDate(2015, 6, 15), QTime(0, 30), _types.at(0), desc);
    desc.append(longDesc);
    _entries << LogEntry(QDate(2015, 6, 17), QTime(1, 30), _types.at(1), desc);
    desc.append(longDesc);
    _entries << LogEntry(QDate(2015, 6, 16), QTime(2, 30), _types.at(0), desc);
    std::stable_sort(_entries.begin(), _entries.end());
}

LogbookModel::~LogbookModel()
{

}

void LogbookModel::addEntry(const LogEntry &entry)
{
    _entries << entry;
    std::stable_sort(_entries.begin(), _entries.end());
}

void LogbookModel::deleteEntry(int index)
{
    if (index >= 0 && index < _entries.count()) {
        _entries.removeAt(index);
    }
}

void LogbookModel::modifyEntry(int index, const LogEntry &entry)
{
    if (index >= 0 && index < _entries.count()) {
        _entries[index] = entry;
        std::stable_sort(_entries.begin(), _entries.end());
    }
}

bool LogbookModel::saveLogbook(const QString &fileName)
{
    int i = fileName.lastIndexOf(QDir::separator());
    QString folderURI;
    if (i >= 0) {
        folderURI = fileName.left(i+1);
    } else {
        folderURI = ".";
    }
//    qDebug() << folderURI;
    QDir folder(folderURI);
    if (folder.exists()) {
        QPrinter printer(QPrinter::HighResolution);
        printer.setPaperSize(QPrinter::A4);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(fileName);

        QTextDocument *document = new QTextDocument();
        QTextCursor cursor(document);
        cursor.insertText("Dit is een testvoorbeeld van een logboek.\n\n");
        QTextTableFormat tableFormat;
        tableFormat.setCellSpacing(0);
        tableFormat.setCellPadding(3);
        tableFormat.setBorderBrush(Qt::black);
        tableFormat.setBorder(2);
        tableFormat.setHeaderRowCount(1);
        //    tableFormat.setAlignment(Qt::AlignCenter);
        tableFormat.setWidth(printer.pageLayout().fullRect(QPageLayout::Point).width() + 20);
        QTextTable *table = cursor.insertTable(_entries.count() + 1, 4, tableFormat);

        QTextCharFormat headerCharFormat;
        headerCharFormat.setFontWeight(QFont::Bold);
        headerCharFormat.setTableCellRowSpan(0);
        QTextBlockFormat headerBlockFormat;
        headerBlockFormat.setAlignment(Qt::AlignHCenter);
        QTextCursor tableCursor = table->cellAt(0, 0).firstCursorPosition();
        tableCursor.setCharFormat(headerCharFormat);
        tableCursor.setBlockFormat(headerBlockFormat);
        tableCursor.insertText("Datum");
        tableCursor = table->cellAt(0, 1).firstCursorPosition();
        tableCursor.setCharFormat(headerCharFormat);
        tableCursor.setBlockFormat(headerBlockFormat);
        tableCursor.insertText("Duur");
        tableCursor = table->cellAt(0, 2).firstCursorPosition();
        tableCursor.setCharFormat(headerCharFormat);
        tableCursor.setBlockFormat(headerBlockFormat);
        tableCursor.insertText("Type");
        tableCursor = table->cellAt(0, 3).firstCursorPosition();
        tableCursor.setCharFormat(headerCharFormat);
        tableCursor.setBlockFormat(headerBlockFormat);
        tableCursor.insertText("Beschrijving");

        for (int row = 0; row < _entries.count(); row++) {
            LogEntry entry = _entries.at(row);
            table->cellAt(row+1, 0).firstCursorPosition().insertText(entry.date().toString("dd/MM/yyyy"));
            table->cellAt(row+1, 1).firstCursorPosition().insertText(entry.duration().toString("H'h'mm'm'"));
            table->cellAt(row+1, 2).firstCursorPosition().insertText(entry.type().name());
            table->cellAt(row+1, 3).firstCursorPosition().insertText(entry.description());
        }

        document->print(&printer);

        return true;
    } else {
        return false;
    }
}

