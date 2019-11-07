import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

import Imaginando 1.0

ColumnLayout {
    id: root
    property var engine
    spacing: 10

    RowLayout {
        Layout.fillWidth: true
        Layout.minimumHeight: 30
        spacing: 1

        Button {
            Layout.minimumWidth: 50
            text: checked?"STOP":"START"
            checkable: true
            checked: controller.running
            onCheckedChanged: {
                if (checked)
                    controller.start();
                else
                    controller.stop();
            }
        }

        Knob {
            Layout.minimumWidth: 50
            Layout.minimumHeight: 50
            value: 0.5
            name: engine.bpm()
            onValueChanged: {
                root.engine.tempo = value
                name = root.engine.bpm()
            }
        }

        Button {
            Layout.minimumWidth: 50
            onClicked: engine.clear()
            text: "Clear"
        }
    }

    RowLayout {
        Layout.fillWidth: true
        Layout.minimumHeight: 50
        spacing: 5

        Repeater {
            id: steps
            model: engine.steps
            delegate: Rectangle {
                Layout.fillWidth: true
                Layout.minimumHeight: 50
                color: engine.currentStep===index?"yellow":(active?"white":"gray")

                MouseArea {
                    anchors.fill: parent
                    onClicked: modelData.active=!modelData.active
                }
            }
        }
    }
}
