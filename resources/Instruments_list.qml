import QtQuick 2.0
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.3
import Configurator 1.0

import "../scripts/InstrumentsContext.js" as Context
import "shared.js" as Shared
import "colors.js" as Color

Item {
    property Configurator configurator;

    height: parent.height * 0.13
    id: main
    Component.onCompleted:{
        Context.onCreate(parent, main, instruments_indicator, instruments_selector, configurator)
    }

    // Minimazed
    Rectangle {
        height: parent.height
        width: parent.width

        gradient: Gradient {
                    GradientStop { position: 0.0; color: Color.dark }
                    GradientStop { position: 1.0; color: Color.light }
                }

        id: instruments_indicator

        MouseArea {
            anchors.fill: parent
            onClicked: {
                Context.maximize()
            }
        }
    }


    // Full width
    Drawer {
        height: parent.height * 0.6; width: parent.width

        edge: Qt.BottomEdge
        id: instruments_selector

        onAboutToShow: Context.repopulateList()
        onClosed: Context.minimize()
        onPositionChanged: Context.onDrawerPositionChanged(position) 

        Rectangle {
            anchors.fill: parent

            color: Color.light
            // Close handler
            Rectangle {
                height: parent.height * 0.1; width: parent.width

                anchors.top: parent.top
                color: "transparent"
                id: close_pane

                Image {
                    anchors.centerIn: parent
                    opacity: 1
                    source: "../data/icons/arrow_48dp.png"
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        Context.minimize()
                    }
                }
            }


            // Populate the list of available instruments
            ListModel {
                id: instruments_list

                Component.onCompleted: {
                    Context.populateList(instruments_list)
                }
            }

            ListView {
                anchors.fill: parent
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.topMargin: close_pane.height

                delegate: instrument_delecate
                height: instruments_selector.height
                model: instruments_list

                id: myListView
            }
        }

    }

    Component {
        id: instrument_delecate

        Item {
            width: parent.width
            height: 45

            Image {
                anchors.right: text.left
                anchors.rightMargin: 20
                anchors.verticalCenter: text.verticalCenter
                fillMode: Image.PreserveAspectFit
                transform: Rotation { origin.x: 25; origin.y: 25; angle: rotate ? 45 : 0}
                source: icon || ""
                height: 40
            }

            FontLoader {
                id: localFont
                source: "../data/fonts/OpenSans-Regular.ttf"
            }

            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                color: selected ? Color.accent : Color.white;
                font: localFont.name
                id: text
                scale: 1.8
                text: name
            }

            MouseArea {
                anchors.fill: parent

                onClicked:{
                    Context.onInstrumentClicked(name);
                }
            }
        }
    }
}
