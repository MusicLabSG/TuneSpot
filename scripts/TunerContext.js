.pragma library
.import "../resources/shared.js" as Shared
.import "../resources/colors.js" as Color
.import "./Observable.js" as Observable
.import "./TuningCircleContext.js" as TuningCircle

// Implements observer

var lines = [];
var circles = [];
var current_string = -1;
var numberOfLines = 19;

var note_holder_obj
var string_holder_obj;
var lines_container_obj;
var tuning_circle_holder_obj;
var configurator_obj;

function onCreate(note_holder, string_holder, lines_container, tuning_circle_holder, configurator) {
    Observable.addObserver(this)
    note_holder_obj = note_holder;
    string_holder_obj = string_holder;
    lines_container_obj = lines_container;
    configurator_obj = configurator;
    tuning_circle_holder_obj = tuning_circle_holder;
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
                                        height+"; opacity: 0.4}", id);
        lines[counter] = object;
        counter++;
    }

    TuningCircle.create(tuning_circle_holder_obj);
}


// Colors the specified line.
// value -> 100: no tune, 0:almost good tune
function showTuningAccuracy(value) {

    if ((value >= 0 && value < 7) || (value < 0 && value > -7))
        TuningCircle.setColor(Color.green);
    else
        TuningCircle.setColor(Color.red);

    // Make sure the circle stays inside the visible workspace
    value = (value/100) * (string_holder_obj.width/2) - TuningCircle.getSize()/2

    TuningCircle.setPosition(value, 0);

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

    showTuningAccuracy(tunePercentage);

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
