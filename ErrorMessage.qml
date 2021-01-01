import QtQuick 2.0

Rectangle {
    width: parent.width
    height: 20
    color: "whitesmoke"
    Row{
        spacing: 20
        Text{
            id:errorTest
            text: ""
            font.family: "Helvetica"
            font.pointSize: 10
            color: "red"
        }
        Text{
            id:xCancel
            text: ""
            color: "black"
            font.pointSize: 10
            MouseArea {
                hoverEnabled: true
                cursorShape: Qt.PointingHandCursor
                anchors.fill: parent
                onPressed: {
                    errorTest.text = "";
                    xCancel.text = "";
                }
            }

        }

    }
    Connections {
        target: cppSocket
        function onServerError(error) {
            errorTest.text = error;
            xCancel.text = "X";
        }
    }
}
