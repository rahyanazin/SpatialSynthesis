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
                        Layout.preferredWidth: parent.width*0.15
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
                        Layout.preferredWidth: parent.width*0.18
                        Layout.fillHeight: true

                        Rectangle {
//                            height: parent.height
//                            width: height
                            anchors.fill: parent

                            Text{
                                id: tf_button_text
                                anchors.centerIn: parent
                                text: 'Update\nTransfer Function:\nOn'
                            }

                            MouseArea{
                                anchors.fill: parent
                                onClicked: {
                                    spatialSound.transferFunction = !spatialSound.transferFunction
                                    if(spatialSound.transferFunction)
                                        tf_button_text.text = 'Update\nTransfer Function:\nOn'
                                    else
                                        tf_button_text.text = 'Update\nTransfer Function:\nOff'
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
                                id: azimuth_rect
                                Layout.fillWidth: true
                                Layout.fillHeight: true
                                border.width: 1
                                border.color: "white"
                                color: "#111111"

                                DimensionController {
                                    anchors.fill: parent
                                    name: "Azimuth"
                                    label: spatialSound.azimuthLabel(value)
                                    onValueChanged: {
                                        spatialSound.setAzimuth(value)
                                        label = spatialSound.azimuthLabel(value)
                                    }
                                }
                            }

                            Rectangle {
                                id: pho_rect
                                Layout.fillWidth: true
                                Layout.fillHeight: true
                                border.width: 1
                                border.color: "white"
                                color: "#111111"

                                DimensionController {
                                    anchors.fill: parent
                                    name: "Pho"
                                    label: spatialSound.phoLabel(value)
                                    onValueChanged: {
                                        spatialSound.setPho(value)
                                        label = spatialSound.phoLabel(value)
                                    }

                                }
                            }

                            Rectangle {
                                id: elevation_rect
                                Layout.fillWidth: true
                                Layout.fillHeight: true
                                border.width: 1
                                border.color: "white"
                                color: "red"

                                DimensionController {
                                    anchors.fill: parent
                                    name: "Elevation"
                                    value: 0.0
                                    label: spatialSound.elevationLabel(0.0)
                                    onValueChanged: {
                                        spatialSound.setElevation(value)
                                        label = spatialSound.elevationLabel(value)
                                    }
                                }
                            }
                        }
                    }

                    Item{
                        Layout.preferredWidth: parent.width*0.12
                        Layout.fillHeight: true

                        ComboBox {
                            anchors.fill: parent
                            anchors.centerIn: parent
                            model: ["Head", "CIPIC"]

                            Component.onCompleted: currentIndex = spatialSound.mode
                            onActivated: {
                                spatialSound.mode = currentIndex
                                if (currentIndex == 0) {
                                    azimuth_rect.color = "#111111"
                                    pho_rect.color = "#111111"
                                    elevation_rect.color = "red"
                                    reset_headmodel.visible = true
                                    subject_select.visible = false
                                }
                                else if (currentIndex == 1) {
                                    azimuth_rect.color = "#111111"
                                    pho_rect.color = "red"
                                    elevation_rect.color = "#111111"
                                    reset_headmodel.visible = false
                                    subject_select.visible = true
                                }
                            }
                        }

                    }

                    Item{
                        id: reset_headmodel
                        Layout.preferredWidth: parent.width*0.1
                        Layout.fillHeight: true

                        Button {
                            anchors.margins: 10
                            anchors.fill: parent
                            text: "Reset"
                            onClicked: spatialSound.reset()
                        }
                    }

                    Item{
                        id: subject_select
                        Layout.preferredWidth: parent.width*0.1
                        Layout.fillHeight: true
                        visible: false

                        ComboBox {
                            anchors.fill: parent
                            anchors.centerIn: parent
                            model: ["003",
                                    "008",
                                    "009",
                                    "010",
                                    "011",
                                    "012",
                                    "015",
                                    "017",
                                    "018",
                                    "019",
                                    "020",
                                    "021",
                                    "027",
                                    "028",
                                    "033",
                                    "040",
                                    "044",
                                    "048",
                                    "050",
                                    "051",
                                    "058",
                                    "059",
                                    "060",
                                    "061",
                                    "065",
                                    "119",
                                    "124",
                                    "126",
                                    "127",
                                    "131",
                                    "133",
                                    "134",
                                    "135",
                                    "137",
                                    "147",
                                    "148",
                                    "152",
                                    "153",
                                    "154",
                                    "155",
                                    "156",
                                    "158",
                                    "162",
                                    "163",
                                    "165",
                                    "mean"]

                            Component.onCompleted: {
                                currentIndex = spatialSound.subject
                            }

                            onActivated: {
                                spatialSound.subject = currentIndex
                            }
                        }
                    }

                    Button {
                        Layout.fillHeight: true
                        Layout.maximumWidth: 20

                        onClicked: spatialSound.impression()
                    }
                }
            }
        }

    }
}


