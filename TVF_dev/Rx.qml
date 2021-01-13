import QtQuick 2.0

Circle {
    id: rxButton

    function receiver(value){
        displayText = value
        clicknotify.running = true
    }

    SequentialAnimation on buttonColor {
        id: clicknotify
        running: false

        ColorAnimation {
            from: "white"
            to: "red"
            duration: 250
        }

        ColorAnimation {
            from: "red"
            to: "white"
            duration: 250
        }
    }
}
