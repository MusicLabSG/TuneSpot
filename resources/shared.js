.pragma library

// List of string of all supported instruments
var StringGuitar = 6
var StringCello = 4


// ----

var currentSelectedInstrument = "Guitar";

function setInstrument(name) {
    currentSelectedInstrument = name;
}

function getInstrument() {
    return currentSelectedInstrument;
}

function getStringNumberOfSelectedInstrument() {
    if (currentSelectedInstrument === "Guitar")
        return StringGuitar
    if (currentSelectedInstrument === "Cello")
        return StringCello
    return 0
}
