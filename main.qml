import QtQuick 2.10
import QtQuick.Window 2.2
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.3

import Configurator 1.0

import "./resources"
import "./resources/colors.js" as Color
import "./scripts/MainContext.js" as Context

Window {
    height: 667
    width: 375

    color: Color.dark
    id: root
    title: qsTr("Tune Spot")
    visible: true

    // This is the backend btw
    Configurator {
        id: configurator
        active: true
        onPercentageChanged: {
            tuner.percentage_changed(note, configurator.percentage)
        }
    }

    FrequencySelector {
        anchors.left: parent.left
        anchors.bottom: tuner.top
        anchors.leftMargin: 20;
        anchors.bottomMargin: 55;

        configurator: configurator;
    }

    Tuner {
        anchors.bottom: list.top
        height: parent.height * 0.7; width: parent.width
        id: tuner
    }

    Instruments_list {
        width: parent.width
        anchors.bottom: parent.bottom
        configurator: configurator
        id: list

    }

    MouseArea {
        anchors.bottom: parent.bottom
        height: parent.height * 0.6; width: parent.width;

        propagateComposedEvents: true

        // Detect swipe up
        //onClicked: Context.onClick(mouseY);

        //onReleased: {

            //if (Context.isSwipe(mouseY)) {
                //list.drawerVisible = true
            //}
        //}
    }

}
