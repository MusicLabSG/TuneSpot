import QtQuick 2.0
import QtQuick.Layouts 1.3
import com.github.tune_spot.configurator 1.0

import "../scripts/TunerContext.js" as Context

Item {
    property Configurator configurator;

    RowLayout {
        id: lines_container
        anchors.centerIn: parent
        spacing: 15.5
    }

    FontLoader {
        id: localFont
        source: "../data/fonts/OpenSans-Light.ttf"
    }

    Text {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: lines_container.bottom
        anchors.bottomMargin: -40
        color: "#FFFFFF"
        font.family: localFont.name
        font.weight: Font.Light
        font.pixelSize: Qt.application.font.pixelSize * 5
        text: "A"
        id: notes_holder
    }

    RowLayout {
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.top: notes_holder.bottom;
        id: string_holder
        spacing: 12
    }

    Component.onCompleted: {
        Context.onCreate(notes_holder, string_holder, lines_container, configurator);

    }
}
