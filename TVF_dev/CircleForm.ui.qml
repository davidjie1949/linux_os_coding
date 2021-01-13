import QtQuick 2.4

Item {
    id: element
    width: 200
    height: 200
    property alias buttonColor: button.color
    property alias displayText: display.text

    Rectangle {
        id: button
        color: "#ffffff"
        radius: width * 0.5
        anchors.fill: parent

        Text {
            id: display
            x: 139
            y: 62
            text: qsTr("Text")
            fontSizeMode: Text.FixedSize
            font.family: "Arial"
            style: Text.Normal
            font.bold: true
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 30
        }
    }
}
