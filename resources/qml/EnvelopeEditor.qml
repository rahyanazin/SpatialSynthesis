import QtQuick 2.0
import QtQuick.Controls 2.2

import Imaginando 1.0

Column {
    spacing: 10

    property Envelope envelope
    property real knobWidth: (width-(3*5))/4

    onEnvelopeChanged: {
        plot.envelope = envelope

        attack.value = envelope.attack
        //decay.value = envelope.decay
        //sustain.value = envelope.sustain
        release.value = envelope.release

        attackCurve.value = envelope.attackCurveDefault()
        //decayCurve.value = envelope.decayCurveDefault()
        releaseCurve.value = envelope.releaseCurveDefault()

        if(envelope.active)
            envelopeButton.color = "green"
        else
            envelopeButton.color = "red"

        plot.update()
    }

    Rectangle {
        width: parent.width
        height: (parent.height-2*10)/2
        border.width: 1
        border.color: "white"
        color: "#111111"

        EnvelopePlot {
            id: plot
            anchors.fill: parent
            anchors.margins: 1
            Component.onCompleted: plot.envelope = envelope
        }
    }

    Row {
        width: parent.width
        height: (parent.height-2*10)/4
        spacing: 5

        Item{
            width: (parent.width-3*5)/4
            height: parent.height

            Knob {
                id: attack
                anchors.horizontalCenter: parent.horizontalCenter
                height: parent.height
                width: parent.width
                name: "A"
                onValueChanged: envelope.attack = value
            }
        }

        Item{
            width: (parent.width-3*5)/4
            height: parent.height

            /*Knob {
                id: decay
                anchors.horizontalCenter: parent.horizontalCenter
                height: parent.height
                width: parent.width
                name: "D"
                onValueChanged: envelope.decay = value
            }*/
        }

        Item{
            width: (parent.width-3*5)/4
            height: parent.height

            /*Knob {
                id: sustain
                anchors.horizontalCenter: parent.horizontalCenter
                height: parent.height
                width: parent.width
                name: "S"
                onValueChanged: envelope.sustain = value
            }*/
        }

        Item{
            width: (parent.width-3*5)/4
            height: parent.height

            Knob {
                id: release
                anchors.horizontalCenter: parent.horizontalCenter
                height: parent.height
                width: parent.width
                name: "R"
                onValueChanged: envelope.release = value
            }
        }

    }

    Row {
        width: parent.width
        height: (parent.height-2*10)/4
        spacing: 5

        Item{
            width: (parent.width-3*5)/4
            height: parent.height

            Knob {
                id: attackCurve
                anchors.horizontalCenter: parent.horizontalCenter
                height: parent.height
                width: parent.width
                name: "C"
                onValueChanged: envelope.attackCurve = value
            }
        }

        Item{
            width: (parent.width-3*5)/4
            height: parent.height

            /*Knob {
                id: decayCurve
                anchors.horizontalCenter: parent.horizontalCenter
                height: parent.height
                width: parent.width
                name: "C"
                onValueChanged: envelope.decayCurve = value
            }*/
        }

        Item{
            width: (parent.width-3*5)/4
            height: parent.height

            Rectangle {
                id: envelopeButton
                anchors.horizontalCenter: parent.horizontalCenter
                height: parent.height
                width: parent.width
                Component.onCompleted: {
                    if(envelope.active)
                        envelopeButton.color = "green"
                    else
                        envelopeButton.color = "red"
                }

                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        envelope.active = !envelope.active
                        if(envelope.active)
                            envelopeButton.color = "green"
                        else
                            envelopeButton.color = "red"
                    }
                }
            }
        }

        Item{
            width: (parent.width-3*5)/4
            height: parent.height

            Knob {
                id: releaseCurve
                anchors.horizontalCenter: parent.horizontalCenter
                height: parent.height
                width: parent.width
                name: "C"
                onValueChanged: envelope.releaseCurve = value
            }
        }


    }
}
