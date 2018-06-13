import QtQuick 2.0
import "../scripts/TunerContext.js" as Context

Rectangle {
    property string id

    height: 15; width:15
    opacity: 0.9
    radius: width * 0.5


    MouseArea {
        anchors.fill: parent

        onClicked: Context.onStringClicked(parent.id)
    }
}
