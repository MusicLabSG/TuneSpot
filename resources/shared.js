.pragma library

var currentSelectedInstrument = "Guitar";

function setInstrument(name) {
    currentSelectedInstrument = name;
}

function getInstrument() {
    return currentSelectedInstrument;
}

