var self;

/*
  Creates the TuningCircle object
 */
function create(parent) {
    var component = Qt.createComponent("../resources/TuningCircle.qml");
    self = component.createObject(parent);
}

function getSize() {
    return self.size;
}

function setPosition(x, y) {
    self.x = x;
    self.y = y;
}

function setColor(color) {
    self.color = color;
}

