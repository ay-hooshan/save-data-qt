import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic

Rectangle {
    property var fileInterface
    anchors.fill: parent
    color: 'pink'

    ColumnLayout {
        anchors.centerIn: parent
        width: 200

        SpinBox {
            id: counterspx
            Layout.fillWidth: true
            Layout.preferredHeight: 70
            value: fileInterface.counter
            to: 10000
        }

        Button {
            text: 'save'
            Layout.fillWidth: true
            Layout.preferredHeight: 70
            onClicked: {
                fileInterface.counter = counterspx.value
                fileInterface.saveCounterToSetting()
            }
        }
    }




}

