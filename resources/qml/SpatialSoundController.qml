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

            Item{
                Layout.fillWidth: true
                Layout.fillHeight: true
                //Layout.preferredHeight: parent.height*0.05
                Text{
                    color: "white"
                    text: "SPATIAL SOUND:"
                }
            }

            Item {
                Layout.fillWidth: true
                Layout.preferredHeight: parent.height*0.7

                TransferFunctionPlot{
                    anchors.fill: parent
                    Component.onCompleted: spatialSound.leftPlot=this
                }

                TransferFunctionPlot{
                    anchors.fill: parent
                    Component.onCompleted: spatialSound.rightPlot=this
                }
            }



            RowLayout{
                Layout.fillWidth: true
                Layout.fillHeight: true

                Item{
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    Rectangle {
                        height: parent.height
                        width: height
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

                    Knob {
                        height: parent.height
                        width: height
                        anchors.centerIn: parent
                        name: "Az"
                        value: 0.75
                        onValueChanged: spatialSound.setAzimuth(value)
                    }
                }
            }
        }

    }
}


