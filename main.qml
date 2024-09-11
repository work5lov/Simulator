import QtQuick 2.12
import QtQuick.Controls 2.12
import VPNSimulator 1.0 // Импортируйте ваш модуль

ApplicationWindow {
    visible: true
    width: 414
    height: 896
    title: "VPN Simulator"

    // Создаем экземпляр Simulator
    Simulator {
        id: vpnSimulator
    }

    property string currentStatus: vpnSimulator.connectionStatus

    Column {
        anchors.centerIn: parent
        spacing: 20

        // Выпадающий список для выбора страны
        ComboBox {
            id: countryComboBox
            width: parent.width * 0.8
            anchors.horizontalCenter: parent.horizontalCenter // Центрируем по горизонтали
            model: ["США", "Канада", "Великобритания", "Германия", "Франция"] // Список стран
            onCurrentTextChanged: {
                vpnSimulator.generateIPAddress(currentText); // Генерируем IP-адрес при выборе страны
                ipInput.text = vpnSimulator.ipAddress; // Обновляем текстовое поле с IP-адресом
            }
        }

        TextField {
            id: ipInput
            placeholderText: "Введите IP-адрес VPN-сервера"
            text: vpnSimulator.ipAddress
            onTextChanged: vpnSimulator.ipAddress = text
            width: parent.width * 0.8 // Устанавливаем ширину текстового поля
            anchors.horizontalCenter: parent.horizontalCenter // Центрируем текстовое поле
        }

        Button {
            id: connectButton
            text: currentStatus === "Подключен" ? "Отключиться" : "Подключиться"
            onClicked: {
                if (currentStatus === "Подключен") {
                    vpnSimulator.disconnectFromVPN();
//                    text: currentStatus = "Отключен"
                } else {
                    vpnSimulator.connectToVPN();
                }
            }
            anchors.horizontalCenter: parent.horizontalCenter // Центрируем кнопку по горизонтали
        }

        ProgressBar {
            id: progressBar
            width: parent.width * 0.8
            visible: vpnSimulator.progress > 0 // Показываем прогресс-бар, если прогресс больше 0
            from: 0
            to: 100
            value: vpnSimulator.progress
            anchors.horizontalCenter: parent.horizontalCenter // Центрируем прогресс-бар
        }

        Text {
            text: currentStatus
            font.pointSize: 20
            color: currentStatus === "Подключен" ? "green" : "red"
            anchors.horizontalCenter: parent.horizontalCenter // Центрируем текст по горизонтали
        }
    }

    // Обновляем прогресс-бар при изменении прогресса
    Connections {
        target: vpnSimulator
        onProgressChanged: {
            progressBar.value = vpnSimulator.progress;
            progressBar.visible = vpnSimulator.progress > 0; // Показываем прогресс-бар, если прогресс больше 0
        }

        onConnectionStatusChanged: {
            if (vpnSimulator.connectionStatus === "Подключен" || vpnSimulator.connectionStatus === "Отключен") {
                progressBar.visible = false; // Скрываем прогресс-бар после завершения подключения
            }
        }

        onConnectionErrorOccurred: {
            // Отобразите сообщение об ошибке, например, с помощью MessageDialog
            console.log(errorMessage); // Выводим сообщение об ошибке в консоль
            // Вы можете использовать MessageDialog для отображения ошибки пользователю
            // Например:
            // MessageDialog {
            //     title: "Ошибка"
            //     text: errorMessage
            //     onAccepted: { /* Действие при принятии */ }
            // }.open();
        }
    }
}
