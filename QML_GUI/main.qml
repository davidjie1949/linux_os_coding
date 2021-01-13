import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

Window {
    visible: true
    width: 640
    height: 480
    id: root
    title: qsTr("Hello World")

    Row {
        id: tools
        Button {
            id: clear
            text: "Clear"
            onClicked: {
                my_a.test()
            }
        }

        Button {
            id: save
            text: "Save"
            onClicked: {

            }
        }
    }
}
