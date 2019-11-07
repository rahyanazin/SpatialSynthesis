import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

import Imaginando 1.0

ColumnLayout {
    id: root
    spacing: 20

    signal selected()

    Row {
        Layout.fillWidth: true

        Knob {
            width: parent.width/2
            height: width
            name: "Tone"
            value: 0.5
            onValueChanged: modelData.setTone(value)
        }

        Knob {
            width: parent.width/2
            height: width
            name: "Param"
            value: 0.5
            onValueChanged: console.log(value)
        }
    }

    EnvelopePlot {
        Layout.fillWidth: true
        Layout.minimumHeight: 50
        anchors.margins: 1
        Component.onCompleted: envelope = modelData.ampEnvelope()
    }

    Row {
        Layout.fillWidth: true

        Knob {
            width: parent.width/2
            height: width
            name: "Amp A"
            value: modelData.ampAttackDefault()
            onValueChanged: modelData.setAmpAttack(value)
        }

        Knob {
            width: parent.width/2
            height: width
            name: "Amp D"
            value: modelData.ampDecayDefault()
            onValueChanged: modelData.setAmpDecay(value)
        }
    }

    Row {
        Layout.fillWidth: true

        Knob {
            width: parent.width/2
            height: width
            name: "Att. C"
            value: modelData.ampAttackCurveDefault()
            onValueChanged: modelData.setAmpAttackCurve(value)
        }

        Knob {
            width: parent.width/2
            height: width
            name: "Dec. C"
            value: modelData.ampDecayCurveDefault()
            onValueChanged: modelData.setAmpDecayCurve(value)
        }
    }

    /*EnvelopeEditor {
        Layout.fillWidth: true
        Layout.minimumHeight: 50
        anchors.margins: 1
        Component.onCompleted: {
            _envelope = modelData.ampEnvelope()
            if(!_envelope) {
                visible = false
                width = 0
            }

        }
    }*/


    /*Row {
        Layout.fillWidth: true

        Knob {
            height: parent.height
            width: root.width/2
            name: "Sat"
            onValueChanged: modelData.setSaturation(value)
        }

        Item {
            height: parent.height
            width: root.width/2
        }
    }*/

    Button {
        Layout.fillWidth: true
        Layout.minimumHeight: 25
        onClicked: modelData.tap()//root.selected()
    }
}
