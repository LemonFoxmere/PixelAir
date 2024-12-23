import QtQuick
import QtQuick.Controls 2.15

ApplicationWindow {
    width: 1200
    height: 700
    minimumWidth: 600
    minimumHeight: 400

    visible: true

    color: "black"

    Item {
        id: lol
        anchors.centerIn: parent
        width: childrenRect.width
        height: childrenRect.height

        Text {
            id: ogre
            font.pixelSize: 64
            text: qsTr("👺")
        }

        Text {
            anchors {
                left: ogre.right
                verticalCenter: ogre.verticalCenter
                leftMargin: 16
            }

            color: "white"
            font {
                pixelSize: 32
                weight: 700
            }
            text: qsTr("Bruh")
        }
    }
}
