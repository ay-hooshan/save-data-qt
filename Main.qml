import QtQuick
import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls
import AyInterface

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")
//    color: 'black'

    AyCppInterface {
        id: ayCppInterface
    }

    ColumnLayout {
        anchors.fill: parent

        TabBar {
            id: bar
            Layout.fillWidth: true

            TabButton {
                text: qsTr("SaveInSetteing")
            }

            TabButton {
                text: qsTr("SaveInFile")
            }

            TabButton {
                text: qsTr("SaveInFileJson")
            }
        }

        StackLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            currentIndex: bar.currentIndex

            Rectangle {
                Layout.fillHeight: true
                Layout.fillWidth: true

                SaveInSetting {
                    fileInterface: ayCppInterface
                }
            }

            Rectangle {
                Layout.fillHeight: true
                Layout.fillWidth: true

                SaveInFile {
                    fileInterface: ayCppInterface
                }
            }

            Rectangle {
                Layout.fillHeight: true
                Layout.fillWidth: true

                SaveInFileJson {
                    fileInterface: ayCppInterface
                }
            }
        }
    }



}
