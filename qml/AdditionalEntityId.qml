// Copyright 2021 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3

RowLayout {
    id: additionalEntityId

    property string targetEntityId
    property string targetEntityType

    Component.onCompleted: {
        controller.update_available_entity_ids("Host", "getDataDialogDestinationEntityId")
        targetEntityId = targetEntityIdComboBox.currentText
        displayStatisticsDialog.regenerateSeriesLabel()
    }

    Label {
        text: "Target Entity Id: "
    }

    ComboBox {
        id: getDataDialogDestinationEntityId
        model: [
            "Host",
            "User",
            "Process",
            "Domain",
            "Topic",
            "DomainParticipant",
            "DataWriter",
            "DataReader",
            "Locator"]
        onActivated:  {
            controller.update_available_entity_ids(currentText, "getDataDialogDestinationEntityId")
            targetEntityId = targetEntityIdComboBox.currentText
            targetEntityType = currentText
            displayStatisticsDialog.regenerateSeriesLabel()
        }
    }

    ComboBox {
        id: targetEntityIdComboBox
        textRole: "id"
        model: entityModelSecond

        Component.onCompleted: {
            targetEntityId = targetEntityIdComboBox.currentText
        }

        onActivated:  {
            targetEntityId = currentText
            displayStatisticsDialog.regenerateSeriesLabel()
        }
    }
}