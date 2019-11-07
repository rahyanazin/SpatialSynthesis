import QtQuick 2.0
import QtQuick.Controls 2.2

import Imaginando 1.0

Column {
    id: root

    Row {
        width: root.width
        height: 30

        ComboBox {
            width: root.width
            height: parent.height
            model: ["Sine", "Square", "Noise"]
            Component.onCompleted: {
                console.log(synth.param)
                currentIndex = synth.mode
            }
            onActivated: {
                synth.mode = currentIndex

                if (currentIndex == 0 || currentIndex == 1) {
                    cutoff.visible = false
                    resonance.visible = false
                    cutoff.width = 0
                    resonance.width = 0

                    tone.visible = true
                    tone.width = tone.height
                }
                else if (currentIndex == 2) {
                    tone.visible = false
                    tone.width = 0

                    cutoff.visible = true
                    resonance.visible = true
                    cutoff.width = cutoff.height
                    resonance.width = resonance.height
                }
            }
        }
    }

    Row {
        width: root.width
        height: 30
        spacing: 10

        Knob {
            id: tone
            height: parent.height
            width: height
            name: "Freq"
            value: 0.02
            onValueChanged: synth.setTone(value)
        }

        Knob {
            id: cutoff
            height: parent.height
            width: 0
            visible: false
            name: "Cutoff"
            value: 0.5
            onValueChanged: synth.setCutoff(value)
        }

        Knob {
            id: resonance
            height: parent.height
            width: 0
            visible: false
            name: "Res"
            value: 0.5
            onValueChanged: synth.setResonance(value)
        }
    }
}
