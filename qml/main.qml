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
            anchors.horizontalCenter: parent.horizontalCenter
            y: 5*boutton1.height
            onClicked: root.buttonClicked("sphere")
        }

        Button {
            id: boutton2
            text: 'Add a Torus'
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: boutton1.bottom
            onClicked: root.buttonClicked("torus")
        }

        Button {
            id: boutton3
            text: 'Add a Cylinder'
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: boutton2.bottom
            onClicked: root.buttonClicked("cylinder")
        }

        Button {
            id: boutton4
            text: 'Add a Cone'
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: boutton3.bottom
            onClicked: root.buttonClicked("cone")
        }

        Button {
            id: boutton5
            text: 'Add a Bent Horns'
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: boutton4.bottom
            onClicked: root.buttonClicked("benthorns")
        }

        Button {
            id: boutton6
            text: 'Add an Apple'
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: boutton5.bottom
            onClicked: root.buttonClicked("apple")
        }

        Button
        {
            id:boutton7
            text: "Add a Plane"
            anchors.top: boutton6.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: root.buttonClicked("plane")
        }
        Button
        {
            id:boutton8
            text: "Add a Sea Shell"
            anchors.top: boutton7.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: root.buttonClicked("seashell")
        }
        Button
        {
            id:boutton9
            text: "Add a Kleins Bottle"
            anchors.top: boutton8.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: root.buttonClicked("kleinsbottle")
        }
        Button
        {
            id:boutton10
            text: "Add a Boy's Surface"
            anchors.top: boutton9.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: root.buttonClicked("boyssurface")
        }
        Button {
            id: clear
            text: 'Clear Scene'
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: boutton10.bottom
            onClicked: root.buttonClicked("clear")
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
