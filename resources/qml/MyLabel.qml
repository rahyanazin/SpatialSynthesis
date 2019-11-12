import QtQuick 2.0

Item {
    id: root
    property string text

    Text{
        anchors.fill: parent
        color: "white"
        text: root.text
    }

    Canvas {
        id: canvas
        anchors.fill: parent

        onPaint: {
            var ctx = getContext("2d")
            ctx.strokeStyle = "white"
            ctx.clearRect(0, 0, width, height)
            ctx.beginPath()
            ctx.moveTo(0,height)
            ctx.lineTo(width, height)
            ctx.closePath()
            ctx.stroke()
        }
    }
}


