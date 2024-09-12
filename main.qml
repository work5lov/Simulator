import QtQuick 2.12
import QtQuick.Controls 2.12
import VPNSimulator 1.0 // Импортируем модуль VPN

ApplicationWindow {
    visible: true // Окно приложения видимо
    width: 414 // Ширина окна
    height: 896 // Высота окна
    title: "VPN Simulator" // Заголовок окна
    color: isDarkTheme ? "black" : "white" // Цвет фона в зависимости от темы

    // Экземпляр симулятора VPN
    Simulator {
        id: vpnSimulator // Идентификатор для доступа к симулятору
    }

    property bool isDarkTheme: false // Переменная для хранения состояния темы
    property string currentStatus: vpnSimulator.connectionStatus // Текущий статус подключения

    Column {
        anchors.centerIn: parent // Центрируем колонку в окне
        spacing: 20 // Расстояние между элементами

        // Выпадающий список для выбора страны
        ComboBox {
            id: countryComboBox
            width: parent.width * 0.8
            anchors.horizontalCenter: parent.horizontalCenter
            model: ["США", "Канада", "Великобритания", "Германия", "Франция"] // Список стран
            onCurrentTextChanged: {
                vpnSimulator.generateIPAddress(currentText); // Генерация IP-адреса
                ipInput.text = vpnSimulator.ipAddress; // Обновление текстового поля
            }
            background: Rectangle {
                color: isDarkTheme ? "gray" : "white" // Цвет фона выпадающего списка
                border.color: isDarkTheme ? "gray" : "black" // Цвет границы
            }
        }

        // Текстовое поле для ввода IP-адреса
        TextField {
            id: ipInput
            placeholderText: "Введите IP-адрес VPN-сервера"
            text: vpnSimulator.ipAddress
            onTextChanged: vpnSimulator.ipAddress = text // Обновление IP-адреса
            width: parent.width * 0.8
            anchors.horizontalCenter: parent.horizontalCenter
            background: Rectangle {
                color: isDarkTheme ? "gray" : "white" // Цвет фона текстового поля
                border.color: isDarkTheme ? "gray" : "black" // Цвет границы
            }
        }

        // Кнопка подключения/отключения
        Button {
            id: connectButton
            text: currentStatus === "Подключен" ? "Отключиться" : "Подключиться"
            onClicked: {
                if (currentStatus === "Подключен") {
                    vpnSimulator.disconnectFromVPN(); // Отключение от VPN
                } else {
                    vpnSimulator.connectToVPN(); // Подключение к VPN
                }
            }
            anchors.horizontalCenter: parent.horizontalCenter
            background: Rectangle {
                color: isDarkTheme ? "gray" : "white" // Цвет фона кнопки
                border.color: isDarkTheme ? "gray" : "black" // Цвет границы
            }
        }

        // Прогресс-бар для отображения статуса подключения
        ProgressBar {
            id: progressBar
            width: parent.width * 0.8
            visible: vpnSimulator.progress > 0 // Показываем, если есть прогресс
            from: 0
            to: 100
            value: vpnSimulator.progress
            anchors.horizontalCenter: parent.horizontalCenter
        }

        // Текст для отображения статуса подключения
        Text {
            id: themeText
            text: currentStatus
            font.pointSize: 20
            color: currentStatus === "Подключен" ? "green" : "red" // Цвет текста в зависимости от статуса
            anchors.horizontalCenter: parent.horizontalCenter
        }

        // Ряд для переключателя темы и меток
        Row {
            anchors.horizontalCenter: parent.horizontalCenter // Центрируем ряд
            spacing: 30 // Расстояние между элементами в ряду

            // Метка для светлой темы
            Item {
                height: 20 // Задаем высоту для вертикального центрирования
                anchors.verticalCenter: themeSwitch.verticalCenter // Центрируем Item по вертикали
                anchors.right: themeSwitch.left // Привязываем к левому краю родителя
                anchors.rightMargin: 20

                Text {
                    text: "Light"
                    color: "white" // Цвет текста для светлой темы
                    anchors.centerIn: parent // Центрируем текст внутри Item
                }
            }

            // Переключатель темы
            Switch {
                id: themeSwitch
                checked: isDarkTheme // Состояние переключателя
                onCheckedChanged: {
                    isDarkTheme = checked; // Обновление состояния темы
                }
            }

            // Метка для темной темы
            Item {
                height: 20 // Задаем высоту для вертикального центрирования
                anchors.verticalCenter: themeSwitch.verticalCenter // Центрируем Item по вертикали
                anchors.left: themeSwitch.right // Привязываем к правому краю родителя
                anchors.leftMargin: 20

                Text {
                    text: "Dark"
                    color: "black" // Цвет текста для темной темы
                    anchors.centerIn: parent // Центрируем текст внутри Item
                }
            }
        }
    }

    // Обработчики событий для обновления интерфейса
    Connections {
        target: vpnSimulator
        onProgressChanged: {
            progressBar.value = vpnSimulator.progress; // Обновление прогресс-бара
            progressBar.visible = vpnSimulator.progress > 0; // Показываем прогресс-бар
        }

        onConnectionStatusChanged: {
            if (vpnSimulator.connectionStatus === "Подключен" || vpnSimulator.connectionStatus === "Отключен") {
                progressBar.visible = false; // Скрываем прогресс-бар после подключения
            }
        }

        onConnectionErrorOccurred: {
            console.log(errorMessage); // Логирование ошибок подключения
        }
    }
}
