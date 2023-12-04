import QtQuick
import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls

Rectangle {
    property var fileInterface

    anchors.fill: parent
    color: 'tomato'


    ColumnLayout {
        anchors.fill: parent

        anchors.margins: 10

        SpinBox {
            id: personIndexBox
            Layout.fillWidth: true
            Layout.preferredHeight: 70
            value: 0
            to: 10

            onValueChanged: {
                console.log('here')
                if (value === 0) {
                    value = 0
                }

                if (value >= ayCppInterface.personModel.rowCount()) {
                    value = ayCppInterface.personModel.rowCount() - 1
                }

                personEditor.text = ayCppInterface.personModel.getPersonJson(value)
            }
        }

        ScrollView {
            Layout.fillWidth: true
            Layout.fillHeight: true

            TextArea {
                id: personEditor

                text: 'something'
                background: Rectangle {
                    color: 'white'
                }
            }
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.preferredHeight: 70

            Button {
                text: 'add new'
                Layout.fillWidth: true
                Layout.fillHeight: true

                onClicked: {
                    ayCppInterface.personModel.appendRow(personEditor.text)
                }
            }

            Button {
                text: 'save in file'
                Layout.fillWidth: true
                Layout.fillHeight: true

                onClicked: {
                    ayCppInterface.savePersonToFile()
                }
            }
        }
    }

    Component.onCompleted: {
        console.log(fileInterface.personModel)
        console.log(ayCppInterface.personModel.getPerson(ayCppInterface.personModel.index(0, 0)))
        console.log(ayCppInterface.personModel.getFullName(ayCppInterface.personModel.index(0, 0)))
        console.log(ayCppInterface.personModel.getPersonJson(0))
        personEditor.text = ayCppInterface.personModel.getPersonJson(0)
    }

}
