import QtQuick 2.15
import QtQuick.Controls 2.15
import gamefield 1.0

GridView {
    id: fieldView;
    model: GameFieldModel { }
    cellHeight: width/model.sideSize
    cellWidth: height/model.sideSize
    property int posChain: model.posChain
    property real initialX : (parent.width)/2 - width/2
    property real initialY : (parent.height)/2 - height/2
    property bool held: false
    Component.onCompleted:
    {
        currentIndex = getCentralIndex()
    }

    interactive: false
    delegate: Cell {
        id: cell
        height: fieldView.cellHeight
        width: fieldView.cellWidth
        border.color: GridView.isCurrentItem ? "green" : "black"
        border.width: GridView.isCurrentItem ? 4 : 1
        property string displayText: model.display
        property string displayColor: model.displayColor
        cellIndex:  index
        MouseArea {
            anchors.fill: parent
            drag.target: held ? fieldView : undefined
            property real coeff: 2.61
            drag.maximumX: initialX + fieldView.width/coeff
            drag.minimumX: initialX - fieldView.width/coeff
            drag.maximumY: initialY + fieldView.height/coeff
            drag.minimumY: initialY - fieldView.height/coeff
            onClicked: {
                var relativePos = cell.mapToItem(borderFrame, mouse.x, mouse.y);
                fieldView.currentIndex = borderFrame.isInVisibleZone(relativePos.x, relativePos.y)
                        ? index : fieldView.currentIndex ;
            }
            onPressed: {
                  var relativePos = cell.mapToItem(borderFrame, mouse.x, mouse.y);
                  held = borderFrame.isInVisibleZone(relativePos.x, relativePos.y)
                  ? true : false ;
            }
            onReleased: held = false
        }

    }
    function centrilizeView()
    {
        x = initialX
        y = initialY
        currentIndex = getCentralIndex()
    }
    function getCentralIndex()
    {
      var cX = width/2
      var cY = height/2
      return fieldView.itemAt(cX, cY).cellIndex
    }
}


