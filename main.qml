import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Layouts 1.2


import "./resources"

Window {
    height: 667
    width: 375

    color: "#1e2327"
    id: root
    title: qsTr("Tune Spot")
    visible: true

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
