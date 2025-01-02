import QtQuick
import QtQuick.Controls
import PixelAir

ApplicationWindow {
    id: root

    width: 700
    height: 700
    minimumWidth: 600
    minimumHeight: 400

    visible: true

    Item {
        id: topBar

        height: 50
        width: root.width
        anchors {
            top: root.top
            left: root.left
            right: root.right
        }
        z: 2

        MouseArea {
            anchors.fill: topBar
            onMouseXChanged: {
                root.startSystemMove();
            }
        }
    }

    Item {
        id: mainCanvas
        anchors.fill: parent

        // bind width and height to controller height and width
        onWidthChanged: CanvasController.width = mainCanvas.width
        onHeightChanged: CanvasController.height = mainCanvas.height

        Text {
            anchors {
                top: parent.top
                left: parent.left
                topMargin: 50
                leftMargin: 5
            }

            color: "white"
            text: `Canvas size: ${CanvasController.width} x ${CanvasController.height} \n` +
                  `Scale: ${CanvasController.zoom} \n` +
                  `Active layer: ${CanvasController.activeLayer}`
            z: 1
        }

        CanvasRenderer {
            anchors.fill: parent
        }
    }
}
