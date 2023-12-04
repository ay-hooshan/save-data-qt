import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Rectangle {
    property var fileInterface

    anchors.fill: parent

    ColumnLayout {
        anchors.centerIn: parent
        width: 200

        TextField {
            id: nameTextInput
            Layout.fillWidth: true
            Layout.preferredHeight: 70
            anchors.margins: 10
            font.pixelSize: 20
            verticalAlignment: Text.AlignVCenter
            text: ayCppInterface.name
        }

        Button {
            text: 'save'
            Layout.fillWidth: true
            Layout.preferredHeight: 70
            onClicked: {
                fileInterface.name = nameTextInput.text
                fileInterface.saveNameToFile()
            }
        }
    }

}

