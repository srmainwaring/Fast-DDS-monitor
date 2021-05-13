import QtQuick 2.7
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.1
import Theme 1.0

MenuBar {
    id: monitorMenuBar

    signal toolBarHidden
    signal initMonitorButtonHidden
    signal dispDataButtonHidden
    signal refreshButtonHidden

    signal leftSidebarHidden
    signal rightSidebarHidden

    Menu {
        title: qsTr("&File")
        Action {
            text: qsTr("&Quit")
            onTriggered: Qt.quit()
        }
    }
    Menu {
        title: qsTr("&Edit")
        Action {
            text: qsTr("Init New Monitor")
            onTriggered: dialogInitMonitor.open()
        }
        Action {
            text: qsTr("Display New Data")
            onTriggered: dataKindDialog.open()
        }
        Action {
            text: qsTr("&Refresh")
            onTriggered: controller.refresh_click()
        }
    }
    Menu {
        title: qsTr("&View")
        implicitWidth: 250
        Action {
            text: (toolBar.isVisible) ? "Hide Shorcuts Toolbar" : "Show Shorcuts Toolbar"
            onTriggered: toolBarHidden()
        }
        Action {
            text: qsTr("Customize Shorcuts Toolbar")
            onTriggered: customizeShorcutsToolbarDialog.open()
        }
        MenuSeparator { }
        Action {
            text: (panels.showLeftSidebar) ? "Hide Left sidebar" : "Show Left Sidebar"
            onTriggered: leftSidebarHidden()
        }
        Action {
            text: (panels.showRightSidebar) ? "Hide Right sidebar" : "Show Right Sidebar"
            onTriggered: rightSidebarHidden()
        }
    }

    Menu {
        title: qsTr("&Help")
        Action {
            text: qsTr("Documentation")
        }
        Action {
            text: qsTr("Release Notes")
        }
        MenuSeparator { }
        Action {
            text: qsTr("Join Us on Twitter")
            onTriggered: Qt.openUrlExternally("https://twitter.com/EProsima")
        }
        Action {
            text: qsTr("Search Feature Requests")
            onTriggered: Qt.openUrlExternally("https://github.com/eProsima/Fast-DDS-monitor/issues")
        }
        Action {
            text: qsTr("Report Issue")
            onTriggered: Qt.openUrlExternally("https://github.com/eProsima/Fast-DDS-monitor/issues/new")
        }
        MenuSeparator { }
        Action {
            text: qsTr("About")
            onTriggered: aboutDialog.open()
        }
    }

    Dialog {
        id: customizeShorcutsToolbarDialog
        title: "Customize Shortcuts Toolbar"
        anchors.centerIn: Overlay.overlay
        standardButtons: DialogButtonBox.Close

        GridLayout {
            columns: 2

            CheckBox {
                id: initMonitorCheckBox
                checked: true
                indicator.width: 20
                indicator.height: 20
                onCheckStateChanged: initMonitorButtonHidden()
            }
            Label {
                text: "Init New Monitor"
            }
            CheckBox {
                id: displayNewDataCheckBox
                checked: true
                indicator.width: 20
                indicator.height: 20
                onCheckStateChanged: dispDataButtonHidden()
            }
            Label {
                text: "Display New Data"
            }
            CheckBox {
                id: refreshCheckBox
                checked: true
                indicator.width: 20
                indicator.height: 20
                onCheckStateChanged: refreshButtonHidden()
            }
            Label {
                text: "Refresh"
            }
        }
    }
}