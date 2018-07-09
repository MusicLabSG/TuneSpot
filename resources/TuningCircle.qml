import QtQuick 2.0

Rectangle {
    property int size: 20
    property int maxHeight: 200
    property int minWidth: 5

    signal animate(bool start)

    id: circle
    height: size; width: size
    opacity: 0.9
    radius: width * 0.5

    // Tuning animation
    onAnimate: {
        if (start === true)
            animation.start();
        else
            animation.stop
    }


    ParallelAnimation {
        id: animation
        PropertyAnimation {
                duration: 5000;
                easing.type: Easing.OutInQuad;
                property: "height";
                target: circle;
                to: circle.maxHeight;
        }
        PropertyAnimation {
                duration: 5000;
                easing.type: Easing.OutInQuad;
                property: "width";
                target: circle;
                to: circle.minWidth;
        }
    }
}
