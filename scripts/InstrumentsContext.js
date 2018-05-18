.import "../resources/shared.js" as Shared

var parent_obj;
var main_obj;
var instruments_indicator_obj;
var instruments_selector_obj;
var selected_instrument_obj;
var dragger_obj;

var maxHeight;
var minHeight;

var selectedInstrument = "Guitar";

function onCreate(parent, main, instruments_indicator, instruments_selector, dragger) {
    parent_obj = parent;
    main_obj = main;
    instruments_indicator_obj = instruments_indicator;
    instruments_selector_obj = instruments_selector;
    dragger_obj = dragger;
    loadIndicator();

}

function populateList(id) {
    var path = "../data/icons/"
    id.append({"name":"Cello", "icon":path+"cello.png","rotate":true});
    id.append({"name":"Piano", "icon":path+"piano.png","rotate":false});
    id.append({"name":"Guitar", "icon":path+"guitar.png", "rotate":true});
    id.append({"name":"Free mode", "icon":path+"vocals.png", "rotate":false});
}

function onInstrumentClicked(name) {
    selectedInstrument = name || "Guitar";
    Shared.setInstrument(name);
    selected_instrument_obj.destroy();
    Shared.getInstrument();
    loadIndicator();
    minimize()
}

function minimize() {
    instruments_selector_obj.visible = false;
    instruments_indicator_obj.visible = true;
    main_obj.height = parent_obj.height * 0.13;
}

function maximize() {
    instruments_selector_obj.visible = true;
    instruments_indicator_obj.visible = false;
    main_obj.height = parent_obj.height * 0.6;
}

function onDrawerPositionChanged(percent) {
    main_obj.height = (parent_obj.height * 0.6) * percent;
}

function calculateReal(mouseY) {
    var min = parent_obj.height * 0.13;

    // The mouseY will take negative values if the event is continued out of the box
    var realY = mouseY;
    if (mouseY < 0) {
        realY = Math.abs(mouseY) + min;
    } else {
        // If the event is inside the box then we must calculate the difference
        realY = mouseY - startingPoint;
    }
    return realY;
}

function getSelectedInstrument() {
    return selectedInstrument;
}

function loadIndicator() {
    selected_instrument_obj = Qt.createComponent("../resources/IndicatorText.qml")
    if (selected_instrument_obj.status === 1)
            finishCreation();
        else
            selected_instrument_obj.statusChanged.connect(finishCreation);
}

function finishCreation() {
    if (selected_instrument_obj.status === 1) {
        selected_instrument_obj = selected_instrument_obj.createObject(instruments_indicator);
    }
}
