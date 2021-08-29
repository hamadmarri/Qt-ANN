import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

import ANN 1.0
import AnnPainter 1.0

Window {
    width: 400
    height: 300
    visible: true
    title: qsTr("Hello World")

    ANN {
        id: ann
        iterations: 1000000
    }

    Text {
        id: errorTxt
        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
            bottom: annPainter.top
        }
        text: "error: " + ann.error
    }

    AnnPainter {
        id: annPainter
        error: ann.error
        anchors {
            left: parent.left
            right: parent.right
            top: errorTxt.bottom
            bottom: startBtn.top
        }
    }

    Button {
        id: startBtn
        anchors {
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }

        text: "START"
        font.pixelSize: 28
        onPressed: ann.train()
    }
}
