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
            Qt.createQmlObject('import QtQuick 2.0; Rectangle {color: "grey"; width: ' + boxWidth +'; height: ' + boxHeight + '; id: index' + i + ' }',
                grid1,  snippetName);
        }
        //grid1.childAt(1,1).color = '#ff0000'
        return "some return value"
    }

    function updateFrameContent(frameData, width, height) {
        console.log("Frame dimensions : ", width, " x ", height, " Length: " + frameData.length );
        for (var i=0; i<frameData.length; i++) {
            var x=Math.floor(i/width) + 1
            var y=i%width + 1
            console.log(x, "x", y, " :", frameData[i])
            grid1.childAt(x,y).color = frameData[i]
        }

    }
}
