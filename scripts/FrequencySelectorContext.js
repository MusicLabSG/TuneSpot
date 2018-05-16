var currentFreq = 440;
var startingY = -1;

function changeFrequency(mouseY) {
    if (startingY === -1) {
        startingY = mouseY;
        return currentFreq;
    }

    var diff = startingY - mouseY;
    startingY = mouseY;
    currentFreq -= diff;
    currentFreq = Math.ceil(currentFreq);
    return currentFreq;
}

function resetY() {
    startingY = -1;
}
