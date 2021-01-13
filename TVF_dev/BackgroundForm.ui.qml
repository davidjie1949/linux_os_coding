import QtQuick 2.4

Item {
    id: background
    width: 640
    height: 480

    Rectangle {
        id: rectangle
        anchors.fill: parent
        visible: true
        gradient: Gradient {
            GradientStop {
                position: 0
                color: "#ffffff"
            }

            GradientStop {
                position: 1
                color: "#56a5dd"
            }
        }
    }
}
