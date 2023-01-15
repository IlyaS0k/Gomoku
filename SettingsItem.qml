import QtQuick 2.0
import QtQuick.Controls 2.0
Column {
  anchors.top: parent.top
  anchors.left: parent.left
  RadioButton {
   checked: !game.isAgainstComputer
   font.pixelSize: 14
   text: "play against human"
   onClicked: game.isAgainstComputer = false
  }
  RadioButton {
   checked: game.isAgainstComputer
   font.pixelSize: 14
   text: "play against computer"
   onClicked: game.isAgainstComputer = true
  }

}
