// программа-генератор текстовых сообщений
#include <QCoreApplication>
#include <QRandomGenerator>
#include <QTime>
#include <QDate>
#include <QDebug>
#include <QThread>

#define DELAY 5 // задержка в секундах

uint32_t getRandomValue(uint32_t low, uint32_t high);
void createMessage(QString& message, QString variant);

enum messageType { INFO, WARNING, ERROR };
enum categoryValue { LEVEL1 = 100, LEVEL2 = 200, LEVEL3 = 300, LEVEL4 = 400, LEVEL5 = 500 };
enum categoryLabel { first, second, third, fourth, filth, all};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString message;
    QTextStream standardOutput(stdout);

    while(true){
        switch(getRandomValue(0, 3)){
            case messageType::INFO:
                createMessage(message, "INFO");
                message.push_back(" INFO MESSAGE");
            break;
            case messageType::WARNING:
                createMessage(message, "WARNING");
                message.push_back(" WARNING MESSAGE");
            break;
            case messageType::ERROR:
                createMessage(message, "ERROR");
                message.push_back(" ERROR MESSAGE");
            break;
        default:
            qDebug() << "No such message type!";
            break;
        }
        standardOutput << message << endl;
        message.clear();
        QThread::sleep(DELAY);
    }
    return a.exec();
}

uint32_t getRandomValue(uint32_t low, uint32_t high)
{
   return (qrand() % ((high - low) + low));
}

void createMessage(QString& message, QString variant)
{
    QTime currentTime =  QTime::currentTime();
    QDate currentDate = QDate::currentDate();
    message.push_back(currentDate.toString("yyyy-MM-dd"));
    message.push_back(" ");
    message.push_back(currentTime.toString("hh:mm:ss"));
    message.push_back(", ");
    switch(getRandomValue(categoryLabel::first, categoryLabel::all)){
        case first:
            message.push_back(QString::number(categoryValue::LEVEL1));
            message.push_back(" ");
            message.push_back(variant.toUpper());
            message.push_back(" Imitator: ");
        break;
        case second:
            message.push_back(QString::number(categoryValue::LEVEL2));
            message.push_back(" ");
            message.push_back(variant.toUpper());
            message.push_back(" Imitator: ");
        break;
        case third:
            message.push_back(QString::number(categoryValue::LEVEL3));
            message.push_back(" ");
            message.push_back(variant.toUpper());
            message.push_back(" Imitator: ");
        break;
        case fourth:
            message.push_back(QString::number(categoryValue::LEVEL4));
            message.push_back(" ");
            message.push_back(variant.toUpper());
            message.push_back(" Imitator: ");
        break;
        case filth:
            message.push_back(QString::number(categoryValue::LEVEL5));
            message.push_back(" ");
            message.push_back(variant.toUpper());
            message.push_back(" Imitator: ");
        break;
        default:
            qDebug() << "No such message type!";
        break;
    }
}
