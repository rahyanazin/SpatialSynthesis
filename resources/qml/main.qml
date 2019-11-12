import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

import Imaginando 1.0

Window {
    id: root
    visible: true
    width: 800
    height: 600
    color: "black"
    title: qsTr("Spatial Synthesis")

    Component.onDestruction: controller.stop()

    Item{
        anchors.fill: parent
        anchors.margins: 10

        ColumnLayout{
            anchors.fill: parent
            //spacing: 10

            RowLayout {
                Layout.fillWidth: true
                Layout.maximumHeight: 15
                Layout.minimumHeight: 15

                Item{
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    Text{
                        color: "white"
                        text: "ANALYSIS LEFT:"
                    }
                }

                Item{
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    Text{
                        color: "white"
                        text: "ANALYSIS RIGHT:"
                    }
                }
            }

            Rectangle {
                Layout.fillWidth: true
                Layout.fillHeight: true
                border.width: 1
                border.color: "white"
                color: "#111111"

                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 10

                    Item {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
        //                Layout.preferredHeight: parent.height*0.125

                        RowLayout {
                            anchors.fill: parent

                            SignalPlot {
                                Layout.fillWidth: true
                                Layout.fillHeight: true
                                Component.onCompleted: controller.signalLeft=this
                            }

                            SignalPlot {
                                Layout.fillWidth: true
                                Layout.fillHeight: true
                                Component.onCompleted: controller.signalRight=this
                            }
                        }
                    }

                    Item {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
        //                Layout.preferredHeight: parent.height*0.125

                        RowLayout {
                            anchors.fill: parent

                            SpectrumPlot {
                                Layout.fillWidth: true
                                Layout.fillHeight: true
                                Component.onCompleted: controller.spectrumLeft=this
                            }

                            SpectrumPlot {
                                Layout.fillWidth: true
                                Layout.fillHeight: true
                                Component.onCompleted: controller.spectrumRight=this
                            }
                        }
                    }
                }
            }

            Item{
                Layout.fillWidth: true
                Layout.maximumHeight: 15
                Layout.minimumHeight: 15

                Text{
                    color: "white"
                    text: "SPATIAL SOUND:"
                }
            }

            SpatialSoundController {
                Layout.fillWidth: true
//                Layout.fillHeight: true
                Layout.preferredHeight: parent.height*0.5
                Component.onCompleted: spatialSound = controller.spatialSound
            }

            RowLayout {
                Layout.fillWidth: true
                Layout.maximumHeight: 15
                Layout.minimumHeight: 15

                Item{
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    Text{
                        color: "white"
                        text: "SYNTHESIS:"
                    }
                }

                Item{
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    Text{
                        color: "white"
                        text: "START/STOP:"
                    }
                }
            }

            Item{
                Layout.fillWidth: true
//                Layout.fillHeight: true
                Layout.preferredHeight: parent.height*0.08

                RowLayout {
                    anchors.fill: parent

                    SynthesizerController {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        Component.onCompleted: synth = controller.synth
                    }

                    Rectangle {
                        id: running_button
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        Component.onCompleted: {
                            if(controller.running)
                                running_button.color = "green"
                            else
                                running_button.color = "red"
                        }

                        MouseArea{
                            anchors.fill: parent
                            onClicked: {
                                controller.running = !controller.running
                                if(controller.running)
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
}
