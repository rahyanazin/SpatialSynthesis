import QtQuick 2.0
Item{
    id:root

    Keys.enabled: true

    property bool logScale: false

    property string name: ""

    property real min: 0
    property real max: 1

    property real value

    onValueChanged: {
        //console.log("value: " + value)
        canvas.requestPaint()
    }

    onMinChanged: {
        if(value<min)
            value = min
        canvas.requestPaint()
    }

    onMaxChanged: {
        if(value>max)
            value = max
        canvas.requestPaint()
    }

    Keys.onPressed: {
        if (event.key === Qt.Key_Control)
            mouseArea.changeValue = false
    }

    Keys.onReleased: {
        if (event.key === Qt.Key_Control)
            mouseArea.changeValue = true

        if (event.key === Qt.Key_Shift)
            if(!mouseArea.changeValue)
                mouseArea.changeMin = !mouseArea.changeMin
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        onEntered: root.focus = true
        onExited: root.focus = false

        property real lastYPosition: 0
        property bool control: false
        property bool changeValue: true
        property bool changeMin: false

        property real deltaRate: 13*parent.height

        onPressed: {
            control = true
            lastYPosition = mouseY
        }

        onReleased: control = false

        onMouseYChanged: {
            if (control) {
                var aux, delta

                delta = (lastYPosition-mouseY)/1000
                lastYPosition = mouseY

                if (changeValue) {
                    aux = root.value + delta

                    if (aux>max) aux=max
                    if (aux<min) aux=min

                    root.value = aux
                }

                else if (changeMin) {
                    aux = root.min + delta
                    if (aux>max) aux=max
                    if (aux<0) aux=0
                    root.min = aux
                }
                else {
                    aux = root.max + delta
                    if (aux<min) aux=min
                    if (aux>1) aux=1
                    root.max = aux
                }
            }
        }
    }

    Canvas {
        id: canvas
        anchors.fill: parent

        onPaint: {
            var ctx = getContext("2d");

            ctx.clearRect(0, 0, width, height)

            var centerX = width/2;
            var centerY = 1.1*height/2;
            var radius = 0.9*width/2;

            if(height < width)
                radius = 0.9*height/2;

            ctx.beginPath();
            ctx.arc(centerX, centerY, radius, -5*Math.PI/4*(1-min)+Math.PI/4*min, Math.PI/4*max-5*Math.PI/4*(1-max), false);
            ctx.strokeStyle = "#6D6F6D"
            ctx.lineWidth = 2.0
            ctx.stroke();
            ctx.closePath();

            var theta = Math.PI*(5-6*value)/4

            ctx.beginPath();
            ctx.moveTo(centerX+radius*Math.cos(theta), centerY-radius*Math.sin(theta))
            ctx.lineTo(centerX+0.75*radius*Math.cos(theta), centerY-0.75*radius*Math.sin(theta))
            ctx.strokeStyle = "#6D6F6D";
            ctx.lineWidth = 3.0;
            ctx.stroke();
            ctx.closePath();
        }

        Text {
            anchors.centerIn: parent
            text: name
            color: "white"
            font.pixelSize: 10
        }
    }
}

