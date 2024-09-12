#include "simulator.h"

// Конструктор класса Simulator
Simulator::Simulator(QObject *parent) : QObject(parent), m_isConnected(false), m_progress(0) {
    // Инициализация таймера
    m_timer = new QTimer(this);
    // Подключение сигнала таймера к лямбда-функции для обновления прогресса
    connect(m_timer, &QTimer::timeout, this, [this]() {
        if (m_progress < 100) {
            m_progress += 10; // Увеличиваем прогресс на 10%
            emit progressChanged(); // Уведомляем об изменении прогресса
        } else {
            // Переключаем состояние подключения
            m_isConnected = !m_isConnected;
            m_connectionStatus = m_isConnected ? "Подключен" : "Отключен"; // Обновляем статус подключения
            emit connectionStatusChanged(); // Уведомляем об изменении статуса подключения
            logConnectionAttempt(m_connectionStatus, m_country); // Логируем попытку подключения
            m_timer->stop(); // Останавливаем таймер
        }
    });

    // Инициализация словаря стран и соответствующих IP-адресов
    countryToIPMap.insert("США", "192.168.1.1");
    countryToIPMap.insert("Канада", "192.168.1.2");
    countryToIPMap.insert("Великобритания", "192.168.1.3");
    countryToIPMap.insert("Германия", "192.168.1.4");
    countryToIPMap.insert("Франция", "192.168.1.5");
}

// Метод для получения текущего IP-адреса
QString Simulator::ipAddress() const {
    return m_ipAddress;
}

// Метод для установки нового IP-адреса
void Simulator::setIpAddress(const QString &ip) {
    if (m_ipAddress != ip) { // Проверяем, изменился ли IP-адрес
        m_ipAddress = ip; // Устанавливаем новый IP-адрес
        emit ipAddressChanged(); // Уведомляем об изменении IP-адреса
    }
}

// Метод для получения текущего статуса подключения
QString Simulator::connectionStatus() const {
    return m_isConnected ? "Подключен" : "Отключен"; // Возвращаем статус подключения
}

// Метод для получения текущего прогресса
int Simulator::progress() const {
    return m_progress; // Возвращаем текущий прогресс
}

// Метод для подключения к VPN
void Simulator::connectToVPN() {
    if (!m_isConnected) { // Проверяем, не подключены ли мы уже
        m_progress = 0; // Сбрасываем прогресс
        emit progressChanged(); // Уведомляем об изменении прогресса
        m_timer->start(300); // Запускаем таймер для обновления прогресса

        // Симуляция ошибки подключения с 20% вероятностью
        if (QRandomGenerator::global()->bounded(100) < 25) { // 50% вероятность ошибки
            m_timer->stop(); // Останавливаем таймер
            qDebug() << "true"; // Логируем для отладки
            emit connectionErrorOccurred("Ошибка подключения к " + m_ipAddress); // Генерируем ошибку
            logConnectionAttempt("Connection error", m_country); // Логируем ошибку подключения
            disconnectFromVPN(); // Отключаемся от VPN
            return; // Выходим из метода
        }
    }
}

// Метод для отключения от VPN
void Simulator::disconnectFromVPN() {
    if (m_isConnected) { // Проверяем, подключены ли мы
        m_isConnected = false; // Обновляем состояние подключения
        m_connectionStatus = "Отключен"; // Обновляем статус подключения
        emit connectionStatusChanged(); // Уведомляем об изменении статуса подключения
        logConnectionAttempt(m_connectionStatus, m_country); // Логируем попытку отключения

        // Сброс прогресса
        m_progress = 0; // Сбрасываем прогресс
        emit progressChanged(); // Уведомляем об изменении прогресса

        // Останавливаем таймер, если он активен
        if (m_timer->isActive()) {
            m_timer->stop(); // Останавливаем таймер
        }
    }
}

// Метод для генерации IP-адреса на основе страны
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
        // Если страна неизвестна, можно вернуть ошибку или просто ничего не делать
        return; // Возвращаемся, если страна не найдена
    }
    m_country = country; // Устанавливаем страну
    // Выбираем случайный диапазон
    QStringList ranges = ipRanges[country];
    QString selectedRange = ranges[QRandomGenerator::global()->bounded(ranges.size())]; // Случайный диапазон

    // Генерируем случайный IP-адрес в выбранном диапазоне
    QStringList parts = selectedRange.split("/"); // Разделяем диапазон на базовый IP и маску
    QString baseIP = parts[0]; // Получаем базовый IP
    QStringList ipParts = baseIP.split("."); // Разделяем базовый IP на октеты

    // Генерируем случайные октеты
    QStringList generatedIPParts;
    generatedIPParts << ipParts[0]; // Первый октет фиксированный

    // Генерируем случайные значения для остальных октетов
    for (int i = 1; i < 4; ++i) {
        generatedIPParts << QString::number(QRandomGenerator::global()->bounded(0, 256)); // Случайные значения от 0 до 255
    }

    QString ipAddress = generatedIPParts.join("."); // Объединяем октеты в строку IP-адреса

    setIpAddress(ipAddress); // Устанавливаем сгенерированный IP-адрес
}

// Метод для начала анимации прогресса
void Simulator::startProgressAnimation() {
    m_progress = 0; // Сбрасываем прогресс
    emit progressChanged(); // Уведомляем об изменении прогресса
    m_timer->start(300); // Запускаем таймер для обновления прогресса
}

// Метод для логирования попыток подключения
void Simulator::logConnectionAttempt(const QString &status, const QString &country) {
    QFile file("connection_log.txt"); // Открываем файл для логирования
    if (file.open(QIODevice::Append | QIODevice::Text)) { // Открываем файл в режиме добавления
        QTextStream out(&file); // Создаем поток для записи в файл
        out << "Connection attempt: " << m_ipAddress << " - " << status << " - Country: " << country << "\n"; // Записываем информацию о попытке подключения
        file.flush(); // Принудительно сбрасываем буфер
        file.close(); // Закрываем файл
    }
}
