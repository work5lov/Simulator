#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QFile>
#include <QTextStream>
#include <QVariant>
#include <QMap>
// #include <QTextCodec>
#include <QRandomGenerator>

// Класс Simulator наследует QObject и реализует функциональность для симуляции подключения к VPN
class Simulator : public QObject {
    Q_OBJECT
    // Свойства для работы с IP-адресом, статусом подключения и прогрессом
    Q_PROPERTY(QString ipAddress READ ipAddress WRITE setIpAddress NOTIFY ipAddressChanged)
    Q_PROPERTY(QString connectionStatus READ connectionStatus NOTIFY connectionStatusChanged)
    Q_PROPERTY(int progress READ progress NOTIFY progressChanged)

public:
    // Конструктор класса, принимает родительский объект
    explicit Simulator(QObject *parent = nullptr);

    // Метод для получения текущего IP-адреса
    QString ipAddress() const;
    // Метод для установки нового IP-адреса
    void setIpAddress(const QString &ip);

    // Метод для получения текущего статуса подключения
    QString connectionStatus() const;
    // Метод для получения текущего прогресса
    int progress() const;

public slots:
    // Слот для подключения к VPN
    void connectToVPN();
    // Слот для отключения от VPN
    void disconnectFromVPN();
    // Слот для начала анимации прогресса
    void startProgressAnimation();
    // Новый слот для генерации IP-адреса на основе страны
    void generateIPAddress(const QString &country);

signals:
    // Сигналы для уведомления об изменениях свойств
    void ipAddressChanged();
    void connectionStatusChanged();
    void progressChanged();
    // Сигнал для уведомления об ошибках подключения
    void connectionErrorOccurred(const QString &errorMessage);

private:
    // Переменные для хранения состояния
    QString m_ipAddress; // Хранит текущий IP-адрес
    QString m_connectionStatus; // Хранит статус подключения
    QTimer *m_timer; // Таймер для анимации прогресса
    bool m_isConnected; // Флаг, указывающий на состояние подключения
    int m_progress; // Хранит текущий прогресс
    QString m_country; // Новая переменная для хранения страны

    // Метод для логирования попыток подключения
    void logConnectionAttempt(const QString &status, const QString &country);
    // Словарь для сопоставления стран и IP-адресов
    QMap<QString, QString> countryToIPMap;
};

#endif // SIMULATOR_H
