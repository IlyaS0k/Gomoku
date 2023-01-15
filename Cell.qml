import QtQuick 2.0

Rectangle {
       id: root
       border.color: "black"
       color: "lightsteelblue"
       property int cellIndex
       Text {
          text: displayText
          color: displayColor
          anchors.centerIn: parent
          font.pointSize: (fieldView.cellHeight + fieldView.cellWidth)/4
       }
//       Text {
//          text: index
//          font.pixelSize: 8
//          font.bold: true
//       }
}

