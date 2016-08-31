import QtQuick 2.0

Rectangle {

  property int fps : 0

  color:   "#d3d3d3"
  opacity: 0.7

  border.color: "black"
  border.width: 2

  Text {
    anchors.centerIn: parent
    text: "FPS: " + fps
  }
}
