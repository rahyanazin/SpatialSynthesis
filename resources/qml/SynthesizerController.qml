import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

import Imaginando 1.0

Item{
    property Synthesizer synth

    Rectangle {
        anchors.fill: parent
        border.width: 1
        border.color: "white"
        color: "#111111"

        ColumnLayout{
            anchors.fill: parent
            anchors.margins: 10

            Item{
                Layout.fillWidth: true
                Layout.fillHeight: true
                Text{
                    color: "white"
                    text: "SYNTHESIS:"
                }
            }

            RowLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true

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

            Item{
                Layout.fillWidth: true
                Layout.fillHeight: true

                Rectangle {
                    id: running_button
                    anchors.fill: parent
                    Component.onCompleted: {
                        if(synth.running)
                            running_button.color = "green"
                        else
                            running_button.color = "red"
                    }

                    MouseArea{
                        anchors.fill: parent
                        onClicked: {
                            synth.running = !synth.running
                            if(synth.running)
                                running_button.color = "green"
                            else
                                running_button.color = "red"
                        }
                    }
                }
            }

        }

    }
}


