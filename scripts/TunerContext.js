.pragma library
.import "../resources/shared.js" as Shared
.import "./Observable.js" as Observable

// Implements observer

var lines = [];
var circles = [];
var current_string = -1;
var numberOfLines = 19;

var note_holder_obj
var string_holder_obj;
var lines_container_obj;
var configurator_obj;

function onCreate(note_holder, string_holder, lines_container, configurator) {
    Observable.addObserver(this)
    note_holder_obj = note_holder;
    string_holder_obj = string_holder;
    lines_container_obj = lines_container;
    configurator_obj = configurator;
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
// value -> 100: no tune, 0:almost good tune
function showTuningAccuracy(position, value) {

    // Make all lines default color
    for (var i = 0; i < numberOfLines; i++){
        lines[i].color = "white"
    }

    value = Math.ceil((value / 100) * 9);

    if(position === "Right")
        value = Math.floor(numberOfLines/2) + value;
    if(position === "Left")
        value = Math.floor(numberOfLines/2) - value

    if(position === "Center" || value < 2){
        lines[9].color = "green";
    }
    else
        lines[value].color = "red";
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
        obj.width  = 15;
        obj.height = 15;

        if ( i === current_string){
            obj.x += 6;
            obj.y += 6;
        }

    }

    // Get the string no
    var stringNo = id.substr(id.length - 1);
    stringNo -= 1;

    // Make selection visible
    current_string = stringNo;
    var object = circles[stringNo];
    object.width = 25;
    object.height = 25;
    object.x -= 6;
    object.y -= 6;


    // Notify the backend for the change

    if(Shared.currentSelectedInstrument === "Guitar"){
        configurator_obj.setterName = "guitar"+(current_string + 1);
    } else if(Shared.currentSelectedInstrument === "Cello"){
        configurator_obj.setterName = "cello"+(current_string + 1);
    }
}

// Takes the current info from the backend and shows them in the UI
function tune(note, tunePercentage) {


    tunePercentage = Math.floor(tunePercentage);

    if (tunePercentage > 0) {
        showTuningAccuracy("Right", tunePercentage);
    } else if(tunePercentage === 0 ) {
        showTuningAccuracy("Center", 0);
    } else {
        showTuningAccuracy("Left", Math.abs(tunePercentage));
    }

    // Change the displayed note
    if (note.charAt(1) === "#")
        note_holder_obj.text = note.substring(0,2);
    else
        note_holder_obj.text = note.charAt(0);
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

    // Make all lines default color
    for (i = 0; i < numberOfLines; i++){
        lines[i].color = "white";
    }
    current_string = -1;
}

function update() {
    reconfigure();
}
