import QtQuick 2.0

Rectangle {
    width: 320
    height: 480
    Grid {
        id: grid1
        anchors.fill: parent
        columns: 3
        spacing: 2

        Rectangle {
            id: rgb1

        }
        Rectangle {
            id: rgb2
            color: "#FF0000"
        }
        Rectangle {
            id: rgb3
            color: "#FF0000"
        }
        Rectangle {
            id: rgb4
            color: "#FF0000"
        }
        Rectangle {
            id: rgb5
            color: "#FF0000"
        }
        Rectangle {
            id: rgb6
            color: "#FF0000"
        }
    }
}
