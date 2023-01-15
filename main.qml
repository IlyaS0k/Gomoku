import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Window 2.0
import Game 1.0
import cell.state 1.0

ApplicationWindow {
   id: root
    width: 800
    height: 800
    visible: true
    maximumWidth: width
    maximumHeight: width
    minimumWidth: height
    minimumHeight: height
    function enableButtons(f){
        insertButton.enabled = f
        resetButton.enabled = f
    }
    Game {
        id: game
        property bool isOver: (gameField.posChain > 0)
        property bool isNextTurn : !game.isOver && isComputerTurn
    }
    Timer {
        running: game.isNextTurn
        interval: 0
        onTriggered: {
            enableButtons(false)
        }
    }
    Timer {
        running: game.isNextTurn
        interval: 500
        onTriggered: {
            game.bestTurn(gameField.getCentralIndex())
            enableButtons(true)

        }
    }
    Timer {
        interval: 0
        running: game.isOver
        onTriggered: {
             enableButtons(false)
             label.text = game.getVictoryString()
        }
    }
    Timer {
        interval: 3000
        running: game.isOver
        onTriggered: {
            label.text = ""
            game.newGame()
             gameField.centrilizeView()
            enableButtons(true)
        }
    }
    BorderFrame{
        id: borderFrame
        z: -1
    }


    SettingsItem {
        z: 1
        id: settingsItem
    }

    GameField {
        id: gameField
        z: -2
        width:3*root.width
        height:3*root.height
        x: initialX
        y: initialY
        Component.onCompleted: {
             game.setGameField(gameField.model)
        }
    }

   InsertButton {
       id: insertButton
       z: 1
       onClicked: {
           game.nextTurn(gameField.model.setState
                        (gameField.currentIndex,
                         game.getCurrentPlayerInsertedState(),
                         game.getCurrentPlayerColor()))
       }
   }
   ResetButton {
       z: 1
       id: resetButton
       onClicked: {
           game.newGame()
           gameField.centrilizeView()

       }
   }

   MessageLabel {
       z: 1
       id: label
   }

}
