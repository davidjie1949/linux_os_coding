import QtQuick 2.0

Circle {
    id: txButton

    property int counter: 0
    property Rx target: null

    signal send(string value)
    onTargetChanged: send.connect(target.receiver)

    MouseArea {
        anchors.fill: parent

        onClicked: {
            counter++
            parent.send(counter)
            test.test()
        }

        onPressed: parent.buttonColor = "green"
        onReleased: parent.buttonColor = "white"
    }
}
