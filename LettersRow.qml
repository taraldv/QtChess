import QtQuick 2.15
Row {
    width: parent.width
    height: 40
    Repeater {
        model: ["A", "B", "C", "D", "E", "F", "G" ,"H"]
        Rectangle{
            color: "whitesmoke"
            width: 100
            height: parent.height
            Text{
                text: modelData
                color: "black"
                font.pointSize: 20
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
    }
}
