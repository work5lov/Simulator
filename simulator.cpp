#include "simulator.h"

Simulator::Simulator(QObject *parent) : QObject(parent), m_isConnected(false), m_progress(0) {
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, [this]() {
        if (m_progress < 100) {
            m_progress += 10; // Увеличиваем прогресс
            emit progressChanged();
        } else {
            m_isConnected = !m_isConnected;
            m_connectionStatus = m_isConnected ? "Подключен" : "Отключен";
            emit connectionStatusChanged();
            logConnectionAttempt(m_connectionStatus, m_country);
            m_timer->stop();
        }
    });

    // Инициализация словаря стран и IP-адресов
    countryToIPMap.insert("США", "192.168.1.1");
    countryToIPMap.insert("Канада", "192.168.1.2");
    countryToIPMap.insert("Великобритания", "192.168.1.3");
    countryToIPMap.insert("Германия", "192.168.1.4");
    countryToIPMap.insert("Франция", "192.168.1.5");
}

QString Simulator::ipAddress() const {
    return m_ipAddress;
}

void Simulator::setIpAddress(const QString &ip) {
    if (m_ipAddress != ip) {
        m_ipAddress = ip;
        emit ipAddressChanged();
    }
}

QString Simulator::connectionStatus() const {
    return m_isConnected ? "Подключен" : "Отключен";
}

int Simulator::progress() const {
    return m_progress;
}

void Simulator::connectToVPN() {
    if (!m_isConnected) {
        m_progress = 0; // Сбрасываем прогресс
        emit progressChanged();
        m_timer->start(300); // Запускаем таймер для обновления прогресса

        // Симуляция ошибки подключения
        if (QRandomGenerator::global()->bounded(100) < 50) { // 20% вероятность ошибки
            m_timer->stop();
            qDebug() << "true";
            emit connectionErrorOccurred("Ошибка подключения к " + m_ipAddress); // Генерируем ошибку
            logConnectionAttempt("Connection error", m_country);
            disconnectFromVPN();
            return;
        }
    }
}

void Simulator::disconnectFromVPN() {
    if (m_isConnected) {
        m_isConnected = false;
        m_connectionStatus = "Отключен";
        emit connectionStatusChanged();
        logConnectionAttempt(m_connectionStatus, m_country);

        // Сброс прогресса
        m_progress = 0;
        emit progressChanged();

        // Остановить таймер, если он работает
        if (m_timer->isActive()) {
            m_timer->stop();
        }
    }
}

void Simulator::generateIPAddress(const QString &country) {
    // Определяем диапазоны IP-адресов для каждой страны
        QMap<QString, QStringList> ipRanges;
        ipRanges["США"] << "23.0.0.0/8" << "24.0.0.0/8" << "64.0.0.0/8"; // Примеры диапазонов
        ipRanges["Канада"] << "24.64.0.0/10" << "70.48.0.0/12"; // Примеры диапазонов
        ipRanges["Великобритания"] << "51.0.0.0/8" << "86.0.0.0/8"; // Примеры диапазонов
        ipRanges["Германия"] << "5.0.0.0/8" << "46.0.0.0/8"; // Примеры диапазонов
        ipRanges["Франция"] << "80.0.0.0/8" << "88.0.0.0/8"; // Примеры диапазонов

        // Проверяем, есть ли диапазоны для указанной страны
        if (!ipRanges.contains(country)) {
//            return QString("Неизвестная страна");
        }
        m_country = country; // Устанавливаем страну
        // Выбираем случайный диапазон
        QStringList ranges = ipRanges[country];
        QString selectedRange = ranges[QRandomGenerator::global()->bounded(ranges.size())];

        // Генерируем случайный IP-адрес в выбранном диапазоне
        QStringList parts = selectedRange.split("/");
        QString baseIP = parts[0];
        QStringList ipParts = baseIP.split(".");

        // Генерируем случайные октеты
        QStringList generatedIPParts;
        generatedIPParts << ipParts[0]; // Первый октет фиксированный

        // Генерируем случайные значения для остальных октетов
        for (int i = 1; i < 4; ++i) {
            generatedIPParts << QString::number(QRandomGenerator::global()->bounded(0, 256));
        }


        QString ipAddress = generatedIPParts.join(".");

//    if (countryToIPMap.contains(country)) {
        setIpAddress(ipAddress); // Устанавливаем IP-адрес в зависимости от выбранной страны
//    }
}

void Simulator::startProgressAnimation() {
    m_progress = 0; // Сбрасываем прогресс
    emit progressChanged();
    m_timer->start(300); // Запускаем таймер для обновления прогресса
}

void Simulator::logConnectionAttempt(const QString &status, const QString &country) {
    QFile file("connection_log.txt");
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
//        out.setCodec("UTF-8");
//        out.setCodec("UTF-8"); // Устанавливаем кодировку UTF-8
//        QTextCodec::setCodecForTr(QTextCodec::codecForName("Windows-1251"));
        out << "Connection attempt: " << m_ipAddress << " - " << status << " - Country: " << country << "\n";
        file.flush(); // Принудительно сбрасываем буфер
        file.close();
    }
}
