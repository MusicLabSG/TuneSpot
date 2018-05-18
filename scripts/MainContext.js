var firstY;
var isSwipe;

function onClick(mouseY) {
    firstY = mouseY;
}

function isSwipe(mouseY) {
    console.log(mouseY - firstY)
    // We assume that the swipe corresponds to a upward movement of at least 40 pixels
    if (mouseY - firstY > 1)
        return true;

    return false;
}



