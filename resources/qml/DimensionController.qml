import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles 1.4

import Imaginando 1.0

RowLayout {
    id: root

    property string name
    property string label
    property real value: 0.5
    property bool running: true

    Item {
        Layout.fillWidth: true
        Layout.fillHeight: true

        Knob {
            id: knob
            height: parent.height
            width: height
            anchors.centerIn: parent
            name: root.label
            value: root.value
            onValueChanged: root.value = value
        }
    }

    /*Item{
        Layout.fillWidth: true
        Layout.fillHeight: true

        Text{
            text: root.label
            color: 'white'
            anchors.centerIn: parent
        }
    }*/

    Item {
        Layout.fillWidth: true
        Layout.fillHeight: true

        CheckBox {
            anchors.centerIn: parent
            checked: true
            style: CheckBoxStyle {
                label: Text {
                    text: root.name
                    color: "white"
                }
            }
            onCheckedChanged: root.running = checked
        }
    }
}


