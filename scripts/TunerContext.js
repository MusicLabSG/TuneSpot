function createLines(id) {
    // Create the graphical content

    var height;
    var numberOfLines = 19;

    for (var i=0; i < numberOfLines; i++){
        // Create 1 small line and 1 big

        height = (i % 2 == 0)? 270 : 220;

        var object = Qt.createQmlObject("import QtQuick 2.2; Rectangle{width:2; height:"+
                                        height+"; opacity: 0.9}", id);
    }

}
