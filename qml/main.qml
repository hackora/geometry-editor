import QtQuick 2.1
import QtQuick.Controls 1.4
import SceneGraphRendering 1.0

import "qrc:/qml/components"

Item {
    id: root
    signal buttonClicked(string msg)

   Rectangle {
      id: sidebar

      anchors.left:parent.left

      color: "yellow"
      width:200
      height: 600

      Button {
          id: boutton1

          text: 'Add a Sphere'
          anchors.top: parent
          onClicked: root.buttonClicked("sphere")
          //signal clicked()


      }

      Button {
          id: boutton2

          text: 'Add a Torus'
          anchors.top: boutton1.bottom
          onClicked: root.buttonClicked("torus")
          //signal clicked()


      }

      Button {
          id: boutton3

          text: 'Add a Cylinder'
          anchors.top: boutton2.bottom
          onClicked: root.buttonClicked("cylinder")
          //signal clicked()


      }

      Button {
          id: boutton4

          text: 'Add a Cone'
          anchors.top: boutton3.bottom
          onClicked: root.buttonClicked("cone")
          //signal clicked()


      }

      Button {
          id: boutton5

          text: 'Add a Bent Horns'
          anchors.top: boutton4.bottom
          onClicked: root.buttonClicked("benthorns")
          //signal clicked()


      }

      Button {
          id: boutton6

          text: 'Add an Apple'
          anchors.top: boutton5.bottom
          onClicked: root.buttonClicked("apple")
          //signal clicked()


      }


      Button {
          id: clear

          text: 'Clear Scene'
          anchors.top: boutton6.bottom
          onClicked: root.buttonClicked("clear")
          //signal clicked()


      }
    }

Item {
    id:scene

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
  width:  900
  height: 600

  anchors.right:parent.right
}
}
