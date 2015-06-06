import QtQuick 2.0

Rectangle {
    width: 800
    height: 600
    color: 'black'
    Grid {
        id: grid1

        anchors.fill: parent
        columns: 3
        rows: 4
        rowSpacing: 2
        columnSpacing: 2
    }


    function setGUIWidthAndHeight(width, height) {

        var length=width*height;
        var boxHeight = (grid1.height / height) - grid1.rowSpacing
        var boxWidth = (grid1.width / width) - grid1.columnSpacing
        console.log("Got message:", width, " x ", height , " sum: " , length, "\t" , " box: " , boxHeight , "x", boxWidth)

        grid1.columns = width
        grid1.rows = height

        for (var i=0; i<length; i++) {
            var snippetName = "dynamicSnippet" + i
            Qt.createQmlObject('import QtQuick 2.0; Rectangle {color: "grey"; width: ' + boxWidth +'; height: ' + boxHeight + ' }',
                grid1,  snippetName);
        }
        return "some return value"
    }
}
