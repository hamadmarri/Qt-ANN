import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    width: 400
    height: 300
    visible: true
    title: qsTr("Hello World")

    Text {
        anchors.fill: parent
        text: "CLOSE"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: 28
        MouseArea {
            anchors.fill: parent
            onClicked: Qt.quit()
        }
    }
}
