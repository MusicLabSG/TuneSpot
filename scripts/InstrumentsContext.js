.import "../resources/shared.js" as Shared

var instruments_indicator_obj;
var instruments_selector_obj;
var selected_instrument_obj

var selectedInstrument = "Guitar";

function onCreate(instruments_indicator, instruments_selector) {
    instruments_indicator_obj = instruments_indicator;
    instruments_selector_obj = instruments_selector;
    loadIndicator();
}

function populateList(id) {
    id.append({"name":"Guitar"});
    id.append({"name":"Cello"});
}

function onInstrumentClicked(name) {
    selectedInstrument = name || "Guitar";
    Shared.setInstrument(name);
    instruments_selector_obj.visible = false;
    instruments_indicator_obj.visible = true;
    selected_instrument_obj.destroy();
    Shared.getInstrument();
    loadIndicator();
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
