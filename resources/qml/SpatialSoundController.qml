import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

import Imaginando 1.0

Item{
    property SpatialSound spatialSound

    Rectangle {
        anchors.fill: parent
        border.width: 1
        border.color: "white"
        color: "#111111"

        ColumnLayout{
            anchors.fill: parent
            anchors.margins: 10
            //spacing: 20

            Item {
                Layout.fillWidth: true
                Layout.preferredHeight: parent.height*0.8
//                Layout.fillHeight: true

                TransferFunctionPlot{
                    anchors.fill: parent
                    Component.onCompleted: spatialSound.leftPlot=this
                }

                TransferFunctionPlot{
                    anchors.fill: parent
                    Component.onCompleted: spatialSound.rightPlot=this
                }
            }

            Item {
                Layout.fillWidth: true
                Layout.fillHeight: true
//                Layout.preferredHeight: parent.height*0.1

                RowLayout{
                    anchors.fill: parent

                    Item{
                        Layout.preferredWidth: parent.width*0.3
                        Layout.fillHeight: true

                        Rectangle {
//                            height: parent.height
//                            width: height
                            anchors.fill: parent

                            Text{
                                id: ss_button_text
                                anchors.centerIn: parent
                                text: 'Spatial Sound: On'
                            }

                            MouseArea{
                                anchors.fill: parent
                                onClicked: {
                                    spatialSound.running = !spatialSound.running
                                    if(spatialSound.running)
                                        ss_button_text.text = "Spatial Sound: On"
                                    else
                                        ss_button_text.text = "Spatial Sound: Off"
                                }
                            }
                        }
                    }

                    Item{
                        Layout.fillWidth: true
                        Layout.fillHeight: true

                        RowLayout{
                            anchors.fill: parent

                            Rectangle {
                                Layout.fillWidth: true
                                Layout.fillHeight: true
                                border.width: 1
                                border.color: "white"
                                color: "#111111"

                                DimensionController {
                                    anchors.fill: parent
                                    name: "Azimuth"
                                    label: spatialSound.azimuthLabel(value)
                                    onRunningChanged: spatialSound.setAzimuthRunning(running)
                                    onValueChanged: {
                                        spatialSound.setAzimuth(value)
                                        label = spatialSound.azimuthLabel(value)
                                    }
                                }
                            }

                            Rectangle {
                                Layout.fillWidth: true
                                Layout.fillHeight: true
                                border.width: 1
                                border.color: "white"
                                color: "#111111"

                                DimensionController {
                                    anchors.fill: parent
                                    name: "Pho"
                                    label: spatialSound.phoLabel(value)
                                    onRunningChanged: spatialSound.setPhoRunning(running)
                                    onValueChanged: {
                                        spatialSound.setPho(value)
                                        label = spatialSound.phoLabel(value)
                                    }

                                }
                            }

                            Rectangle {
                                Layout.fillWidth: true
                                Layout.fillHeight: true
                                border.width: 1
                                border.color: "white"
                                color: "#111111"

                                DimensionController {
                                    anchors.fill: parent
                                    name: "Elevation"
                                    label: "22.5º"
                                    onValueChanged: {
                                        //spatialSound.setPho(value)
                                        //label = spatialSound.phoLabel(value)
                                        label = parseFloat(45*value).toFixed(1)+"º"
                                    }
                                    onRunningChanged: {
                                        if (running)
                                            console.log("elevation on!")
                                        else
                                            console.log("elevation off!")
                                    }
                                }
                            }
                        }
                    }

                    Item{
                        Layout.preferredWidth: parent.width*0.1
                        Layout.fillHeight: true

                        Button {
                            anchors.margins: 10
                            anchors.fill: parent
                            text: "Reset"
                            onClicked: spatialSound.reset()
                        }
                    }
                }
            }
        }

    }
}


