.pragma library
// A simple observable implementation

var listOfObservers = []

// Adds an observer; the observer must implement the update() method.
function addObserver(observer) {
    listOfObservers.push(observer);
}

// Removes an observer
function removerObserver(observer) {
    // TODO
}

// Notifies all observers
function notifyAll() {
    for (var i = 0; i < listOfObservers.length; i++)
        listOfObservers[i].update();
}
