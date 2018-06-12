.pragma library
.import "../resources/shared.js" as Shared

var lines = [];
var circles = [];
var previous_circle = -1;
var numberOfLines = 19;

var note_holder_obj
var string_holder_obj;
var lines_container_obj;

function onCreate(note_holder, string_holder, lines_container) {
    note_holder_obj = note_holder;
    string_holder_obj = string_holder;
    lines_container_obj = lines_container;
    createLines(lines_container);
    createCircles();
}

function createLines(id) {
    // Create the graphical content

    var height;

    var counter = 0;
    for (var i=0; i < numberOfLines; i++) {
        // Create 1 small line and 1 big

        height = (i % 2 == 0)? 270 : 220;

        var object = Qt.createQmlObject("import QtQuick 2.2; Rectangle{width:2; height:"+
                                        height+"; opacity: 0.9}", id);
        lines[counter] = object;
        counter++;
    }
}


// Colors the specified line.
// position -> Left || Right || Center: perfect tune
// value -> 1: no tune, 9:almost good tune
function showTuningAccuracy(position, value) {

    // Make all lines default color
    for (var i = 0; i < numberOfLines; i++){
        lines[i].color = "white"
    }

    if(position === "Right")
        value = numberOfLines/2 + value;

    if(position === "Center")
        lines[numberOfLines / 2].color = "green"
    else
        lines[value].color = "red"
}

// Creates the circles, acting as the selected string
function createCircles() {

    var counter = 0;
    for (var i=0; i < Shared.getStringNumberOfSelectedInstrument(); i++) {

        var component = Qt.createComponent("../resources/StringCircle.qml");
        var object = component.createObject(string_holder_obj);;
        object.id = "String"+ (counter+1)
        circles[counter] = object;
        counter++;
    }
}

function onStringClicked(id) {
    // Reset selection
    for (var i = 0; i < circles.length; i++) {
        var obj = circles[i];
        obj.width  = 10;
        obj.height = 10;

        if ( i === previous_circle){
            obj.x += 5;
            obj.y += 5;
        }

    }

    // Get the string no
    var stringNo = id.substr(id.length - 1);
    stringNo -= 1;

    // Make selection visible
    previous_circle = stringNo;
    var object = circles[stringNo];
    object.width = 20;
    object.height = 20;
    object.x -= 5;
    object.y -= 5;
}

// Resets all variables and recalculates them
function reconfigure() {

    // Delete all string circles
    if (circles.length > 0){
        for (var i = circles.length - 1; i >= 0 ; i--) {
            circles[i].destroy();
            circles.splice(i,1);
        }
    }

    // Create the new
    createCircles();
}
