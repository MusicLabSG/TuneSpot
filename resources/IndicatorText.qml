import QtQuick 2.0

import "shared.js" as Shared

Item {
    anchors.centerIn: parent
    FontLoader {
        id: localFont
        source: "../data/fonts/OpenSans-Light.ttf"
    }

    Text {
        anchors.centerIn: parent
        color: "#FFFFFF"
        font.family: localFont.name
        font.pixelSize: Qt.application.font.pixelSize * 2
        id: name

        Component.onCompleted: {
            text = Qt.binding(function() { return Shared.getInstrument() })
        }
    }
}
