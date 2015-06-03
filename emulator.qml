import QtQuick 2.0

Rectangle {
    width: 800
    height: 600
    Grid {
        id: grid1
        anchors.fill: parent
        columns: 3
        spacing: 2

        Rectangle {
            id: rgb1
            objectName: "rgb1Obj"
            width: 60
            height: 60
            color: "#000000"
        }
        Rectangle {
            id: rgb2
            objectName: "rgb2"
            color: "#FF0000"
            width: 60
            height: 60
        }
        Rectangle {
            id: rgb3
            color: "#FF0000"
            width: 60
            height: 60
        }
        Rectangle {
            id: rgb4
            color: "#FF0000"
            width: 60
            height: 60
        }
        Rectangle {
            id: rgb5
            color: "#FF0000"
            width: 60
            height: 60
        }
        Rectangle {
            id: rgb6
            color: "#FF0000"
            width: 60
            height: 60
        }
    }

    function setGUIWidthAndHeight(width, height) {
        console.log("Got message:", width, " x ", height)
        return "some return value"
    }
}
