import QtQuick 2.0

Rectangle {
    width: 800
    height: 600
    Grid {
        id: grid1
        anchors.fill: parent
        columns: 3
    }

    function setGUIWidthAndHeight(width, height) {

        var length=width*height;
        console.log("Got message:", width, " x ", height , " sum: " , length)
        for (var i=0; i<length; i++) {

            var newObject = Qt.createQmlObject('import QtQuick 2.0; Rectangle {color: "red"; width: 60; height: 60 }',
                grid1, "dynamicSnippet" );
        }
        return "some return value"
    }
}
