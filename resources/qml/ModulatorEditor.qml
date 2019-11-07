import QtQuick 2.0
import QtQuick.Controls 2.2

Column {
    id: root

    Row {
        width: root.width
        height: root.height
        spacing: root.spacing

        Column {
            width: parent.width/2
            height: parent.height
            spacing: root.spacing

            ComboBox {
                width: parent.width
                height: (parent.height-5)/2
                model: ["None", "Sine", "Square"]
                onActivated: synth.ampModID = currentIndex
            }

            Knob {
                width: parent.width
                height: (parent.height-root.spacing)/2
                name: "Freq"
                onValueChanged: synth.setAmpModFreq(value)
            }
        }

        Column {
            width: parent.width/2
            height: parent.height
            spacing: root.spacing

            ComboBox {
                width: parent.width
                height: (parent.height-root.spacing)/2
                model: ["None", "Sine", "Square"]
                onActivated: synth.pitchModID = currentIndex
            }

            Knob{
                width: parent.width
                height: (parent.height-root.spacing)/2
                name: "Freq"
                onValueChanged: synth.setPitchModFreq(value)
            }
        }
    }
}
