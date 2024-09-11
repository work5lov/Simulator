#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QFile>
#include <QTextStream>
#include <QVariant>
#include <QMap>
#include <QTextCodec>
#include <QRandomGenerator>

class Simulator : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString ipAddress READ ipAddress WRITE setIpAddress NOTIFY ipAddressChanged)
    Q_PROPERTY(QString connectionStatus READ connectionStatus NOTIFY connectionStatusChanged)
    Q_PROPERTY(int progress READ progress NOTIFY progressChanged)

public:
    explicit Simulator(QObject *parent = nullptr);

    QString ipAddress() const;
    void setIpAddress(const QString &ip);

    QString connectionStatus() const;
    int progress() const;

public slots:
    void connectToVPN();
    void disconnectFromVPN();
    void startProgressAnimation();
    void generateIPAddress(const QString &country); // Новый метод для генерации IP

signals:
    void ipAddressChanged();
    void connectionStatusChanged();
    void progressChanged();
    void connectionErrorOccurred(const QString &errorMessage); // Новый сигнал для ошибки подключения

private:
    QString m_ipAddress;
    QString m_connectionStatus;
    QTimer *m_timer;
    bool m_isConnected;
    int m_progress;
    QString m_country; // Новая переменная для хранения страны

    void logConnectionAttempt(const QString &status, const QString &country);
    QMap<QString, QString> countryToIPMap; // Словарь для стран и IP-адресов
};

#endif // SIMULATOR_H
