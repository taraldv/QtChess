import QtQuick 2.15

Column {
    width: 35
    leftPadding: 5
    rightPadding: 5
    //height: parent.height
    z: -1
    // color: "yellow"
    Rectangle{
        height: 30
        width: parent.width
        color: "whitesmoke"
    }

    Rectangle{
        color: "whitesmoke"
        height: 100
        width: parent.width
        Text{
            text: "8"
            color: "black"
            font.pointSize: 20
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
    Rectangle{
        color: "whitesmoke"
        height: 100
        width: parent.width
        Text{
            text: "7"
            color: "black"
            font.pointSize: 20
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
    Rectangle{
        color: "whitesmoke"
        height: 100
        width: parent.width
        Text{
            text: "6"
            color: "black"
            font.pointSize: 20
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
    Rectangle{
        color: "whitesmoke"
        height: 100
        width: parent.width
        Text{
            text: "5"
            color: "black"
            font.pointSize: 20
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
    Rectangle{
        color: "whitesmoke"
        height: 100
        width: parent.width
        Text{
            text: "4"
            color: "black"
            font.pointSize: 20
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
    Rectangle{
        color: "whitesmoke"
        height: 100
        width: parent.width
        Text{
            text: "3"
            color: "black"
            font.pointSize: 20
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
    Rectangle{
        color: "whitesmoke"
        height: 100
        width: parent.width
        Text{
            text: "2"
            color: "black"
            font.pointSize: 20
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
    Rectangle{
        color: "whitesmoke"
        height: 100
        width: parent.width
        Text{
            text: "1"
            color: "black"
            font.pointSize: 20
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}
