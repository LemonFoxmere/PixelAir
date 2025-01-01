import QtQuick
import QtQuick.Controls

ApplicationWindow {
    id: root

    width: 1200
    height: 700
    minimumWidth: 600
    minimumHeight: 400

    visible: true

    Rectangle {
        id: testPlatform

        width: 350
        height: 350

        color: Qt.hsla(0, 0, 0, 0)
        border {
            color: "red"
            width: 1
        }

        anchors.centerIn: parent
    }
}
