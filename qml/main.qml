import QtQuick 2.1
import SceneGraphRendering 1.0

import "qrc:/qml/components"

Item {

  GMlibSceneRenderer {
     id: renderer

    anchors.fill: parent

    FpsBox {

      fps: renderer.fps
      
      anchors {
        margins: 20
        top:     parent.top
        right:   parent.right
      }

      width:  100
      height: 25
    }
  }
}

