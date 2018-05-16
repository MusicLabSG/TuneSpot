import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Layouts 1.2


import "./resources"
import "./resources/colors.js" as Color

Window {
    height: 667
    width: 375

    color: Color.dark
    id: root
    title: qsTr("Tune Spot")
    visible: true

    FrequencySelector {
        anchors.top: parent.top
        anchors.left: parent.left


        anchors.topMargin: 55;
        anchors.leftMargin: 20;

        height: parent.height
        width: parent.width
    }

    RowLayout {
        anchors.fill: parent
        id: main_container

        Tuner {
            height: parent.height
            width: parent.width
        }

        Instruments_list {
            height: parent.height
            width: parent.width
        }
    }
}
