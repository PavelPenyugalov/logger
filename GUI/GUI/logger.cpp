#include "logger.h"

Logger::Logger()
{
    //testFunction();
}

Logger::~Logger()
{

}
void Logger::getInputData()
{
    while(standardInput.readLineInto(&inputString)){
        standartOutput << inputString << endl;
        checkTypeMessage(inputString);
    }
}

int Logger::checkTypeMessage(const QString &str)
{
    int result = 0;
    if(str.contains("info", Qt::CaseInsensitive)){
        m_messagesContainer.insert(messageType::INFO, str);
        result = messageType::INFO;
    }else if(str.contains("warning", Qt::CaseInsensitive)){
        m_messagesContainer.insert(messageType::WARNING, str);
        result = messageType::WARNING;
    }
    else if(str.contains("error", Qt::CaseInsensitive)){
        m_messagesContainer.insert(messageType::ERROR, str);
        result = messageType::ERROR;
    }
    return result;
}

void Logger::getContainerValuesByKey(int key)
{
    QMultiHash<int, QString>::Iterator beginContainer = m_messagesContainer.begin();
    QMultiHash<int, QString>::Iterator endContainer = m_messagesContainer.end();
    while(beginContainer != endContainer){
        if(key ==  beginContainer.key()){
            m_selectedValues.append(beginContainer.value());
        }
        beginContainer++;
    }
}

void Logger::getAllContainer()
{
    if(m_selectedValues.size() > 0){
        m_selectedValues.clear();
    }
    QMultiHash<int, QString>::Iterator beginContainer = m_messagesContainer.begin();
    QMultiHash<int, QString>::Iterator endContainer = m_messagesContainer.end();
    while(beginContainer != endContainer){
        m_selectedValues.append(beginContainer.value());
        beginContainer++;
    }
}

void Logger::removeContainerValuesByKey(int key)
{
    QString searchSubstring;

    switch(key){
        case messageType::INFO:
            searchSubstring.clear();
            searchSubstring.push_back("INFO");
        break;
        case messageType::WARNING:
            searchSubstring.clear();
            searchSubstring.push_back("WARNING");
        break;
        case messageType::ERROR:
            searchSubstring.clear();
            searchSubstring.push_back("ERROR");
        break;
        default:
            qDebug() << "Wrong message type!";
        break;
    }
     if(!m_selectedValues.empty()){
         m_selectedValues.erase(std::remove_if(m_selectedValues.begin(), m_selectedValues.end(), [&searchSubstring](QString &str) { return str.contains(searchSubstring); }), m_selectedValues.end());
    }
}

void Logger::listToCommonString()
{
    if(m_commonString.size() != 0){
        m_commonString.clear();
    }
    m_selectedValues.sort();
    QTextStream fillStream(&m_commonString);
    QList<QString>::const_iterator listBegin = m_selectedValues.begin();
    QList<QString>::const_iterator listEnd = m_selectedValues.end();
    while(listBegin != listEnd){
        fillStream << (*listBegin) << "\n";
        listBegin++;
    }
}

void Logger::testFunction()
{
    m_messagesContainer.insert(messageType::INFO, "2019-05-30 13:49:31, 100 INFO Imitator:  INFO MESSAGE");
    m_messagesContainer.insert(messageType::ERROR, "2019-05-30 13:49:36, 300 ERROR Imitator:  ERROR MESSAGE");
    m_messagesContainer.insert(messageType::INFO, "2019-05-30 13:49:41, 400 INFO Imitator:  INFO MESSAGE");
    m_messagesContainer.insert(messageType::INFO, "2019-05-30 13:49:46, 100 INFO Imitator:  INFO MESSAGE");
    m_messagesContainer.insert(messageType::INFO, "2019-05-30 13:49:51, 300 INFO Imitator:  INFO MESSAGE");
    m_messagesContainer.insert(messageType::INFO, "2019-05-30 13:49:56, 300 INFO Imitator:  INFO MESSAGE");
    m_messagesContainer.insert(messageType::WARNING, "2019-05-30 13:50:36, 400 WARNING Imitator:  WARNING MESSAGE");
    m_messagesContainer.insert(messageType::ERROR, "2019-05-30 13:22:26, 300 ERROR Imitator:  ERROR MESSAGE");
    m_messagesContainer.insert(messageType::WARNING, "2019-05-30 13:50:11, 200 WARNING Imitator:  WARNING MESSAGE");

}
