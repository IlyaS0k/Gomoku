import QtQuick 2.0

Item {
    anchors.fill: parent
    property real coefX: 0.7
    property real coefY: 0.7
    property string borderColor: "lightyellow"
    property real dX: (1 - coefX)/2*parent.width
    property real dY: (1 - coefY)/2*parent.height
    Rectangle {
        id: topRectangle
        color: borderColor
        width: parent.width
        height: dY
        anchors.top: parent.top
    }
    Rectangle {
        id: bottomRectangle
        color: borderColor
        width: parent.width
        height: dY
        anchors.bottom: parent.bottom
    }
    Rectangle {
        id: leftRectangle
        color: borderColor
        height: parent.height
        width: dX
        anchors.left: parent.left
    }
    Rectangle {
        id: rightRectangle
        color: borderColor
        height: parent.height
        width: dX
        anchors.right: parent.right
    }
    function isInVisibleZone(curX, curY)
    {
       var minX = x + dX
       var minY = y + dY
       var maxX = x + width - dX
       var maxY = y + height - dY
       var cond = curX >= minX && curX <= maxX &&
       curY >= minY && curY <= maxY
       return cond
    }
}
