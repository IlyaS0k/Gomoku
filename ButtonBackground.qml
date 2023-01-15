import QtQuick 2.0

Rectangle {
    anchors.fill: parent
    border.color: "black"
    color: parent.down ? "white" :
                            (parent.hovered ? "lightgreen" : "white")
}
