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

    CanvasRenderer {
        id: test
        anchors.fill: parent
    }
}
