var maxFreq = 480;
var minFreq = 400;

var prefHeight = 45;
var prefWidth = 80;
var maxHeight = 60;
var maxWidth = 105;

var currentFreq = 440;
var startingY = -1;

function changeFrequency(mouseY) {
    if (startingY === -1) {
        startingY = mouseY;
        return currentFreq;
    }

    var diff = startingY - mouseY;
    // Make the percision bigger
    diff *= 0.3
    startingY = mouseY;
    currentFreq -= diff;

    // Check bounds
    if (currentFreq < minFreq)
        currentFreq = minFreq;
    if (currentFreq > maxFreq)
        currentFreq = maxFreq;

    return Math.ceil(currentFreq);
}

function resetY() {
    startingY = -1;
}
