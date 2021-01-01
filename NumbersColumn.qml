import QtQuick 2.15

Column {
    width: 35
    Rectangle{
        width: parent.width
        height: 40
        color: "whitesmoke"
    }

    Repeater{
        model: ["8", "7", "6", "5", "4", "3", "2" ,"1"]
        Rectangle{
            color: "whitesmoke"
            height: 100
            width: parent.width
            Text{
                text: modelData
                color: "black"
                font.pointSize: 20
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
    }
    Rectangle{
        width: parent.width
        height: 40
        color: "whitesmoke"
    }
}
