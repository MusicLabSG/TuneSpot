.import "../resources/shared.js" as Shared
.import "./Observable.js" as Observable

var parent_obj;
var main_obj;
var instruments_indicator_obj;
var instruments_selector_obj;
var instruments_list_obj;
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
    if (instruments_list_obj === undefined)
        instruments_list_obj = id;

    var path = "../data/icons/";
    id.append({"name":"Cello", "icon":path+"cello.png","rotate":true, "selected":isSelected("Cello")});
    id.append({"name":"Piano", "icon":path+"piano.png","rotate":false, "selected":isSelected("Piano")});
    id.append({"name":"Guitar", "icon":path+"guitar.png", "rotate":true, "selected":isSelected("Guitar")});
    id.append({"name":"Free mode", "icon":path+"vocals.png", "rotate":false, "selected":isSelected("Free mode")});
}

/*
  Repopulates the list handling any property changes.
*/
function repopulateList() {
    instruments_list_obj.clear();
    populateList(instruments_list_obj);
}

function isSelected(name) {
    return name === selectedInstrument;
}

function onInstrumentClicked(name) {
    selectedInstrument = name || "Guitar";
    Shared.setInstrument(name);
    selected_instrument_obj.destroy();
    Shared.getInstrument();
    loadIndicator();
    minimize();

    Observable.notifyAll();
}

function minimize() {
    instruments_selector_obj.close();
    main_obj.height = parent_obj.height * 0.13;
}

function maximize() {
    instruments_selector_obj.open();
    main_obj.height = parent_obj.height * 0.6;
}

function onDrawerPositionChanged(percent) {
    main_obj.height = (parent_obj.height * 0.6) * percent;
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
