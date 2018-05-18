import QtQuick 2.0
import QtQuick.Controls 2.3

import "../scripts/FrequencySelectorContext.js" as Context
import "colors.js" as Color

Item {

    Rectangle {
        height: 45; width: 80

        border.color: Color.accent
        border.width: 1
        color: "transparent"
        id: container
        radius: 20
        visible: true
    }

    FontLoader {
        id: localFont
        source: "../data/fonts/OpenSans-Light.ttf"
    }

    Text {
        property int frequency: 440;

        anchors.centerIn: container
        color: "#FFFFFF"
        font.family: localFont.name
        font.weight: Font.Light
        font.pixelSize: Qt.application.font.pixelSize
        id: freq
        text: frequency + "Hz"
    }

    Text {
        anchors.bottom: freq.top
        anchors.bottomMargin: 10
        anchors.horizontalCenter: freq.horizontalCenter
        color: "#FFFFFF"
        font.family: localFont.name
        font.weight: Font.Light
        font.pixelSize: Qt.application.font.pixelSize
        id: freqShade1
        opacity: 0.5
        text: freq.frequency - 1 + "Hz"
        visible: false
    }

    Text {
        anchors.top: freq.bottom
        anchors.topMargin: 10
        anchors.horizontalCenter: freq.horizontalCenter
        color: "#FFFFFF"
        font.family: localFont.name
        font.weight: Font.Light
        font.pixelSize: Qt.application.font.pixelSize
        id: freqShade2
        opacity: 0.5
        text: freq.frequency + 1 + "Hz"
        visible: false
    }


    Rectangle {
        height: 45; width: 80

        color: Color.accent
        id: helper
        radius: 20
        visible: false

        Text {
            anchors.centerIn: parent
            color: "#FFFFFF"
            font.family: localFont.name
            font.weight: Font.Light
            font.pixelSize: Qt.application.font.pixelSize
            text: "Drag me"
        }
    }

    MouseArea {
        anchors.fill: container

        onPositionChanged: {
            helper.visible = false
            freq.frequency = Context.changeFrequency(mouseY)
            freqShade1.visible = true
            freqShade2.visible = true

            if (freq.frequency === Context.minFreq)
                freqShade1.visible = false
            if (freq.frequency === Context.maxFreq)
                freqShade2.visible = false
        }

        onReleased: {
            Context.resetY()
            freqShade1.visible = false
            freqShade2.visible = false
        }

        onDoubleClicked: helper.visible = true
    }
}
