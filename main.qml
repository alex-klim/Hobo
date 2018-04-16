import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4

import cpp.helptypes 1.0

Window {
    visible: true
    width: 670
    height: 450
    title: qsTr("Hello World")

    GridLayout {
    }

    RowLayout {
    }

    GridLayout {
        x: 20
        y: 63
        columnSpacing: 25
        rowSpacing: 5
        rows: 2
        columns: 8

        Label {
            id: label
            text: qsTr("Starting URL")
        }

        Item {
            id: spacer
            Layout.maximumHeight: 15
            Layout.maximumWidth: 15
            Layout.preferredHeight: 14
            Layout.preferredWidth: 14
        }

        Label {
            id: label1
            text: qsTr("Searching word")
        }

        Item {
            id: spacer1
            Layout.preferredHeight: 14
            Layout.preferredWidth: 14
        }

        Label {
            id: label2
            text: qsTr("Threads")
        }

        Item {
            id: spacer2
            Layout.preferredHeight: 14
            Layout.preferredWidth: 14
        }

        Label {
            id: label3
            text: qsTr("URL limit")
        }

        Item {
            id: spacer3
            Layout.preferredHeight: 14
            Layout.preferredWidth: 14
        }

        TextField {
            id: startUrl
            Layout.columnSpan: 2
            Layout.preferredWidth: 200
            Layout.alignment: Qt.AlignHCenter
            placeholderText: qsTr("http://anysite.com")
        }

        TextField {
            id: searchWord
            Layout.columnSpan: 2
            placeholderText: qsTr("developer")
        }

        TextField {
            id: maxThreads
            Layout.columnSpan: 2
            Layout.preferredWidth: 50
            placeholderText: qsTr("2")
        }

        TextField {
            id: maxUrls
            Layout.columnSpan: 2
            Layout.preferredWidth: 50
            placeholderText: qsTr("10")
        }
    }

    ColumnLayout {
        x: 44
        y: 118
        spacing: 10

        TableView {
            id: tableView
            Layout.rowSpan: 7
            Layout.columnSpan: 8
            Layout.preferredHeight: 224
            Layout.preferredWidth: 431

            TableViewColumn {
                    role: "url"
                    title: "URL"
                    width: 310
            }
            TableViewColumn {
                    role: "status"
                    title: "Status"
                    width: 119
            }

            model: {
              id: tmodel;
            }
        }

        ListModel {
            id: linkModel
        }

        ProgressBar {
            id: progressBar
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.columnSpan: 8
            Layout.preferredHeight: 19
            Layout.preferredWidth: 354

            minimumValue: 0;
            maximumValue: 100;
        }
    }

    ColumnLayout {
        x: 492
        y: 149
        spacing: 40

        Button {
            id: button
            text: qsTr("Button")
            onClicked: {
                dmanager.fetchPage(startUrl.text, searchWord.text);
            }
        }

        Button {
            id: button1
            text: qsTr("Button")
            onClicked: {
            }
        }

        Button {
            id: button2
            text: qsTr("Button")
            onClicked: {

            }
        }
    }

}
