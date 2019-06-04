import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.4
import "shared"

ApplicationWindow {
    id: mainWindow
    visible: true
    width: 640
    height: 480
    title: qsTr("Log Filter")
    readonly property int infoGroup: 1
    readonly property int warningGroup: 2
    readonly property int errorGroup: 3
    property int infoState: 3
    property int warningState: 3
    property int errorState: 3

   ColumnLayout{
       id: mainColumn
       anchors.top: parent.top
       anchors.left: parent.left
       anchors.right: parent.right
       anchors.topMargin: 10
        RowLayout{
            id: buttonsRow
            Layout.alignment: Qt.AlignCenter
            CheckBox{
               id: infoCheckBox
               checked: true
                onClicked: {
                    infoState++;
                    if(infoState % 2 == 0){
                        logger.removeContainerValuesByKeyWrapper(infoGroup);
                    } else {
                        logger.getContainerValuesByKeyWrapper(infoGroup);
                    }
                    logger.listToCommonStringWrapper();
                    areaMessages.text = "";
                    areaMessages.text = logger.commonString
                }
            }
            Label{
               id: infoCheckBoxLabel
               text: "Show info messages"
            }
            CheckBox{
               id: warningCheckBox
               checked: true
               onClicked: {
                   warningState++;
                   if(warningState % 2 == 0){
                       logger.removeContainerValuesByKeyWrapper(warningGroup);
                   } else {
                       logger.getContainerValuesByKeyWrapper(warningGroup);
                   }
                   logger.listToCommonStringWrapper();
                   areaMessages.text = "";
                   areaMessages.text = logger.commonString;
               }
            }
            Label{
               id: warningCheckBoxLabel
               text: "Show warning messages"
            }
            CheckBox{
               id: errorCheckBox
               checked: true
               onClicked: {
                   errorState++
                   if(errorState % 2 == 0){
                       logger.removeContainerValuesByKeyWrapper(errorGroup);
                   } else {
                       logger.getContainerValuesByKeyWrapper(errorGroup);
                   }
                   logger.listToCommonStringWrapper();
                   areaMessages.text = ""
                   areaMessages.text = logger.commonString
               }
            }
            Label{
               id: errorCheckBoxLabel
               text: "Show error messages"
            }
        }
   }
   ScrollView{
        id: scrollAreaMessages
        anchors.bottom: parent.bottom
        anchors.top: mainColumn.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 10

        TextArea{
             id: areaMessages
             text: ""
        }
   }
   Timer{
        id: appTimer
        interval: 1000; running: true; repeat: true
        onTriggered: {
            if((infoState % 2 == 1) && (warningState % 2 == 1) && (errorState % 2 == 1)){
                logger.getAllContainerWrapper();
                logger.listToCommonStringWrapper();
                areaMessages.text = ""
                areaMessages.text = logger.commonString
            }
        }
   }
}
