import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

import Imaginando 1.0

Rectangle{
    border.width: 1
    border.color: "white"
    color: "#111111"

    property Synthesizer synth

    RowLayout {
        anchors.fill: parent
        anchors.margins: 10

        Item{
            Layout.fillWidth: true
            Layout.fillHeight: true

            ComboBox {
                anchors.fill: parent
                anchors.centerIn: parent
                model: ["Sine", "Square", "Noise"]

                Component.onCompleted: {
                    currentIndex = synth.mode
                }

                onActivated: {
                    synth.mode = currentIndex

                    if (currentIndex == 0 || currentIndex == 1) {
                        tone_knob.name = "Freq"
                        res_knob.visible = false
                    }
                    else if (currentIndex == 2) {
                        tone_knob.name = "Cutoff"
                        res_knob.visible = true
                    }
                }
            }
        }

        Item{
            Layout.fillWidth: true
            Layout.fillHeight: true

            RowLayout{
                anchors.fill: parent

                Item{
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    Knob {
                        id: tone_knob
                        height: parent.height
                        width: height
                        anchors.centerIn: parent
                        name: "Freq"
                        value: 0.5
                        onValueChanged: synth.setTone(value)
                    }
                }

                Item{
                    id: res_knob
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    visible: false

                    Knob {
                        height: parent.height
                        width: height
                        anchors.centerIn: parent
                        name: "Res"
                        value: 0.5
                        onValueChanged: synth.setResonance(value)
                    }
                }
            }
        }
    }
}


