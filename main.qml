import QtQuick 2.15
import QtQuick.Window 2.2
import QtQuick.Controls 2.15
import Qt.labs.qmlmodels 1.0
import QtQuick.Layouts 1.15



Window {

    visible: true
    // Can it be previously saved width and height?
    width: 640
    height: 480
    title: qsTr("Technical Workshop")

    TableView {
        id: view
        anchors.fill: parent
        columnSpacing: 1
        rowSpacing: 1
        clip: true
        visible: false
        signal clicked(int row, int column)

        model: photos
        delegate: Rectangle {
            //Should it be calculated frome the window size?
            //Previosly kept?
            implicitWidth: 100
            implicitHeight: 50
            border.width: 1

            //TODO: Replace text with image
            Text {
                text: display
            }
            MouseArea {
                anchors.fill: parent
                onClicked: photos.onClicked(index)
            }

            //TODO: Add tooltip

        } // delegate
    } // TableView

    // Use button for now
    // Should be replaced with animation

    Button {
        id: loading
        text: "Click me"
        visible: true
        anchors.centerIn: parent
        onClicked: photos.onTest()
    } // Button

    Connections {
        target: photos
        onLoadedChanged: loading.visible = false
    }

    Connections {
        target: photos
        onLoadedChanged: view.visible = true
    }
} // Window
