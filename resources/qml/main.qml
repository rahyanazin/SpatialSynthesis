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
    title: qsTr("Groove Machine")

    Component.onDestruction: controller.stop()

    Item{
        anchors.fill: parent
        anchors.margins: 20

        ColumnLayout{
            anchors.fill: parent
            spacing: 20

            SignalPlot {
                Layout.fillWidth: true
                Layout.preferredHeight: parent.height*0.125
                Component.onCompleted: controller.signalPlot=this
            }

            SpectrumPlot {
                Layout.fillWidth: true
                Layout.preferredHeight: parent.height*0.125
                Component.onCompleted: controller.spectrumPlot=this
            }

            SpatialSoundController {
                Layout.fillWidth: true
                Layout.preferredHeight: parent.height*0.45
                Component.onCompleted: spatialSound = controller.spatialSound
            }

            SynthesizerController {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Component.onCompleted: synth = controller.synth
            }
        }
    }
}
