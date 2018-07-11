.import QtQuick 2.0 as QtQuick

var self;

/*
  Creates the TuningCircle object
 */
function create(parent) {
    var component = Qt.createComponent("../resources/TuningCircle.qml");

    if (component.status === QtQuick.Component.Ready)
        finishCreation(component, parent)
    else
        component.statusChanged.connect(new function arrow() {finishCreation(component, parent)});
}

function finishCreation(component, parent) {
    if (component.status === QtQuick.Component.Ready) {
        self = component.createObject(parent);

        if (self === null) {
            print("Error creating object");
        }
    } else if (component.status === QtQuick.Component.Error) {
        print("Error loading component:", component.errorString());
    }
}

function getSize() {
    return self.size;
}

function getHeight() {
    return self.height;
}

function getWidth() {
    return self.width;
}

function setPosition(x, y) {
    if (x != null)
        self.x = x;
    if (y != null) {
        print("setting y");
        self.y = y;
    }
}

function setColor(color) {
    self.color = color;
}

function beginAnimation() {
    if (self.height <= self.size)
        self.animate(true);
}

function revertAnimation() {
    self.animate(false);
    self.height = self.size;
    self.width = self.size;
}

