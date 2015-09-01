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
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QByteArray>

LogbookModel::LogbookModel()
{
    startEmptyLogbook();
}

LogbookModel::~LogbookModel()
{

}

void LogbookModel::addEntry(const LogEntry &entry)
{
    _entries << entry;
    std::stable_sort(_entries.begin(), _entries.end());
    _isEdited = true;
}

QString LogbookModel::currentOpenFile() const
{
    if (_currentOpenFile.compare("") == 0) {
        return "New file";
    } else {
        return _currentOpenFile;
    }
}

void LogbookModel::deleteEntry(int index)
{
    if (index >= 0 && index < _entries.count()) {
        _entries.removeAt(index);
        _isEdited = true;
    }
}

bool LogbookModel::exportLogbookPDF(const QString &fileName)
{
    int i = fileName.lastIndexOf(QDir::separator());
    QString folderURI;
    if (i >= 0) {
        folderURI = fileName.left(i+1);
    } else {
        folderURI = ".";
    }
    QDir folder(folderURI);
    if (folder.exists()) {
        QPrinter printer(QPrinter::HighResolution);
        printer.setPaperSize(QPrinter::A4);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(fileName);

        QTextDocument *document = new QTextDocument();
        QTextCursor cursor(document);
        cursor.insertHtml(QString(_description).append("<br><br>"));
//        cursor.insertText(QString(_description).append("\n\n"));
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

void LogbookModel::loadLogbookJSON(const QString &fileName)
{
    QFile jsonFile(fileName);
    if (jsonFile.open(QFile::ReadOnly)) {
        QByteArray byteArray = jsonFile.readAll();
        QJsonDocument jsonDoc(QJsonDocument::fromJson(byteArray));
        jsonFile.close();
        QJsonObject jsonLogbook = jsonDoc.object();

        _description = jsonLogbook["description"].toString();
        _types = QList<EntryType>();
        _entries = QList<LogEntry>();

        _types.reserve(jsonLogbook["numentrytypes"].toInt());
        QJsonArray jsonEntryTypes = jsonLogbook["entrytypes"].toArray();
        for (int i=0; i<jsonEntryTypes.count(); i++) {
            QJsonObject jsonEntryType = jsonEntryTypes.at(i).toObject();
            _types.append(EntryType(jsonEntryType["id"].toInt(), jsonEntryType["name"].toString()));
        }

        QJsonArray jsonEntries = jsonLogbook["entries"].toArray();
        for (int i=0; i<jsonEntries.count(); i++) {
            QJsonObject jsonEntry = jsonEntries.at(i).toObject();
            QDate date = QDate::fromString(jsonEntry["date"].toString(), "dd/MM/yyyy");
            QTime duration = QTime::fromString(jsonEntry["duration"].toString(), "H'h'm'm'");
            _entries.append(LogEntry(date, duration, _types.at(jsonEntry["entrytype"].toInt()), jsonEntry["description"].toString()));
        }
        std::stable_sort(_entries.begin(), _entries.end());

        _currentOpenFile = fileName;
        _isEdited = false;
    } else {
        qWarning() << "Could not open file:" << jsonFile.fileName();
    }
}

void LogbookModel::modifyEntry(int index, const LogEntry &entry)
{
    if (index >= 0 && index < _entries.count()) {
        _entries[index] = entry;
        std::stable_sort(_entries.begin(), _entries.end());
        _isEdited = true;
    }
}

void LogbookModel::saveLogbookJSON()
{
    if (_currentOpenFile.compare("") != 0 && _isEdited) {
        saveAsLogbookJSON(_currentOpenFile);
    }
}

void LogbookModel::saveAsLogbookJSON(const QString &fileName)
{
    QJsonObject jsonLogbook;

    jsonLogbook["description"] = _description;
    jsonLogbook["numentrytypes"] = _types.count();

    QJsonArray jsonEntryTypes;
    for (int i=0; i<_types.count(); i++) {
        QJsonObject jsonEntryType;
        EntryType type = _types.at(i);
        jsonEntryType["id"] = type.id();
        jsonEntryType["name"] = type.name();
        jsonEntryTypes.append(jsonEntryType);
    }
    jsonLogbook["entrytypes"] = jsonEntryTypes;

    QJsonArray jsonEntries;
    for (int i=0; i<_entries.count(); i++) {
        QJsonObject jsonEntry;
        LogEntry entry = _entries.at(i);
        jsonEntry["date"] = entry.date().toString("dd/MM/yyyy");
        jsonEntry["duration"] = entry.duration().toString("H'h'm'm'");
        jsonEntry["entrytype"] = entry.type().id();
        jsonEntry["description"] = entry.description();
        jsonEntries.append(jsonEntry);
    }
    jsonLogbook["entries"] = jsonEntries;

    QJsonDocument jsonDoc(jsonLogbook);
    QFile jsonFile(fileName);
    if (jsonFile.open(QFile::WriteOnly)) {
        jsonFile.write(jsonDoc.toJson());
        jsonFile.close();
        _isEdited = false;
        _isNew = false;
        _currentOpenFile = fileName;
    } else {
        qWarning() << "Could not open file:" << jsonFile.fileName();
    }
}

void LogbookModel::setDescription(const QString &description)
{
    _description = description;
}

void LogbookModel::startEmptyLogbook()
{
    _description = "Dit is een gegenereerd logboek.";
    _types = QList<EntryType>();
    _entries = QList<LogEntry>();
    _types << EntryType(0, "Literatuur");
    _types << EntryType(1, "Implementatie");
    _isEdited = false;
    _isNew = true;
    _currentOpenFile = "";

//    QString desc("Dit is een beschrijving. ");
//    QString longDesc("Nu is dit een langere beschrijving. ");
//    _entries << LogEntry(QDate(2015, 6, 15), QTime(0, 30), _types.at(0), desc);
//    desc.append(longDesc);
//    _entries << LogEntry(QDate(2015, 6, 17), QTime(1, 30), _types.at(1), desc);
//    desc.append(longDesc);
//    _entries << LogEntry(QDate(2015, 6, 16), QTime(2, 30), _types.at(0), desc);
//    std::stable_sort(_entries.begin(), _entries.end());
}
