import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Background {
        id: background
        anchors.fill: parent

        Tx {
            id: tx
            y: 138
            anchors.verticalCenter: parent.verticalCenter
            displayText: "Send"
            anchors.left: parent.left
            anchors.leftMargin: 50
            target: rx
        }

        Rx {
            id: rx
            x: 238
            y: 100
            anchors.verticalCenter: parent.verticalCenter
            displayText: "Receive"
            anchors.right: parent.right
            anchors.rightMargin: 50
        }
    }
}
