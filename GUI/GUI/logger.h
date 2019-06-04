#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QQuickItem>
#include <QString>
#include <QThread>
#include <QMultiHash>

#include <fstream>
#include <stdio.h>

// потоки для обработки входных данных
static QTextStream standardInput(stdin);
static QTextStream standartOutput(stdout);

class Logger : public QObject
{
    Q_OBJECT
public:
    // общая строка сообщений лога, передаваемая в QML
    Q_PROPERTY(QString commonString READ getCommonString)

    // методы-обертки, вызываеые из QML слоя
    Q_INVOKABLE void getContainerValuesByKeyWrapper(int key){ getContainerValuesByKey(key); }
    Q_INVOKABLE void removeContainerValuesByKeyWrapper(int key){ removeContainerValuesByKey(key); }
    Q_INVOKABLE void listToCommonStringWrapper() { listToCommonString(); }
    Q_INVOKABLE void getAllContainerWrapper() { getAllContainer(); }

    Logger();
    ~Logger();

    // публичный, потому что через этот метод в отдельном потоке
    // заполняется контейнер сообщений m_messagesContainer
    void getInputData();

    // для тестирования
    void testFunction();

    // нужен для Q_PROPERTY
    QString getCommonString() const { return m_commonString; }

private:
    // проверяет тип сообщения и добавляет в m_messagesContainer
    int checkTypeMessage(const QString &str);
    // получить из QML слоя значения по ключу, модифицирует m_selectedValues
    void getContainerValuesByKey(int key);
    // преобразовать в строку для вставки в TextArea
    void listToCommonString();
    // удалить значения по ключу, модифицирует m_selectedValues
    void removeContainerValuesByKey(int key);
    // получить все полученные сообщения из m_messagesContainer
    void getAllContainer();

    enum messageType {INFO = 1, WARNING, ERROR};

    QString inputString;
    QString m_commonString;
    QList<QString> m_selectedValues;
    QMultiHash<int, QString> m_messagesContainer;
};

#endif // LOGGER_H
