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

#include <sstream>      // std::ostringstream

#include <fastdds-monitor/backend/backend_types.h>
#include <fastdds-monitor/model/model_types.h>
#include <fastdds-monitor/utils.h>

#include <QDebug>

namespace backend {

const EntityId ID_ALL = EntityId::all();
const EntityId ID_NONE = EntityId::invalid();

models::EntityId backend_id_to_models_id(
        const EntityId id)
{
    std::ostringstream stream;
    if (id == ID_ALL)
    {
        stream << models::ID_ALL;
    }
    else if (id == ID_NONE)
    {
        stream << models::ID_INVALID;
    }
    else
    {
        stream << id;
    }
    return utils::to_QString(stream.str());
}

EntityId models_id_to_backend_id(
        const models::EntityId id)
{
    std::ostringstream stream;
    if (id == models::ID_ALL)
    {
        return EntityId::all();
    }
    else if (id == models::ID_INVALID)
    {
        return EntityId::invalid();
    }
    else
    {
        return EntityId(id.toInt());
    }
}

// PROCESS
QString process_pid(
        backend::EntityId process_id)
{
    // TODO
    return backend_id_to_models_id(process_id);
}

// DDS GUID
QString entity_guid(
        backend::EntityId id)
{
    // TODO
    return backend_id_to_models_id(id);
}

// TOPIC
QString topic_type(
        backend::EntityId id)
{
    // TODO
    return backend_id_to_models_id(id);
}

QString entity_kind_to_QString(
        const EntityKind& entity_kind)
{
    switch (entity_kind)
    {
        case EntityKind::HOST:
            return "HOST";
        case EntityKind::USER:
            return "USER";
        case EntityKind::PROCESS:
            return "PROCESS";
        case EntityKind::DOMAIN:
            return "DOMAIN";
        case EntityKind::TOPIC:
            return "TOPIC";
        case EntityKind::PARTICIPANT:
            return "PARTICIPANT";
        case EntityKind::DATAWRITER:
            return "DATAWRITER";
        case EntityKind::DATAREADER:
            return "DATAREADER";
        case EntityKind::LOCATOR:
            return "LOCATOR";
        default:
            return "INVALID";
    }
}

EntityKind string_to_entity_kind(
        const QString& entity_kind)
{
    static std::unordered_map<std::string, EntityKind> const conversionTable = {
        {"Host", EntityKind::HOST},
        {"User", EntityKind::USER},
        {"Process", EntityKind::PROCESS},
        {"Domain", EntityKind::DOMAIN},
        {"Topic", EntityKind::TOPIC},
        {"Participant", EntityKind::PARTICIPANT},
        {"DomainParticipant", EntityKind::PARTICIPANT},
        {"DataWriter", EntityKind::DATAWRITER},
        {"DataReader", EntityKind::DATAREADER},
        {"Locator", EntityKind::LOCATOR}
    };

    auto it = conversionTable.find(utils::to_string(entity_kind));
    if (it != conversionTable.end())
    {
        return it->second;
    }
    else
    {
        return EntityKind::INVALID;
    }
}

DataKind string_to_data_kind(
        const QString& data_kind)
{
    static std::unordered_map<std::string, DataKind> const conversionTable = {
        {"FASTDDS_LATENCY", DataKind::FASTDDS_LATENCY},
        {"NETWORK_LATENCY", DataKind::NETWORK_LATENCY},
        {"PUBLICATION_THROUGHPUT", DataKind::PUBLICATION_THROUGHPUT},
        {"SUBSCRIPTION_THROUGHPUT", DataKind::SUBSCRIPTION_THROUGHPUT},
        {"RTPS_PACKETS_SENT", DataKind::RTPS_PACKETS_SENT},
        {"RTPS_BYTES_SENT", DataKind::RTPS_BYTES_SENT},
        {"RTPS_PACKETS_LOST", DataKind::RTPS_PACKETS_LOST},
        {"RTPS_BYTES_LOST", DataKind::RTPS_BYTES_LOST},
        {"RESENT_DATA", DataKind::RESENT_DATA},
        {"HEARTBEAT_COUNT", DataKind::HEARTBEAT_COUNT},
        {"ACKNACK_COUNT", DataKind::ACKNACK_COUNT},
        {"NACKFRAG_COUNT", DataKind::NACKFRAG_COUNT},
        {"GAP_COUNT", DataKind::GAP_COUNT},
        {"DATA_COUNT", DataKind::DATA_COUNT},
        {"PDP_PACKETS", DataKind::PDP_PACKETS},
        {"EDP_PACKETS", DataKind::EDP_PACKETS},
        {"DISCOVERY_TIME", DataKind::DISCOVERY_TIME},
        {"SAMPLE_DATAS", DataKind::SAMPLE_DATAS}
    };

    auto it = conversionTable.find(utils::to_string(data_kind));
    if (it != conversionTable.end())
    {
        return it->second;
    }
    else
    {
        return DataKind::INVALID;
    }
}

StatisticKind string_to_statistic_kind(
        const QString& statistic_kind)
{
    static std::unordered_map<std::string, StatisticKind> const conversionTable = {
        {"NONE", StatisticKind::NONE},
        {"MEAN", StatisticKind::MEAN},
        {"STANDARD_DEVIATION", StatisticKind::STANDARD_DEVIATION},
        {"MAX", StatisticKind::MAX},
        {"MIN", StatisticKind::MIN},
        {"MEDIAN", StatisticKind::MEDIAN},
        {"COUNT", StatisticKind::COUNT},
        {"SUM", StatisticKind::SUM}
    };

    auto it = conversionTable.find(utils::to_string(statistic_kind));
    if (it != conversionTable.end())
    {
        return it->second;
    }
    else
    {
        return StatisticKind::NONE;
    }
}

std::string get_info_value(
        EntityInfo info,
        std::string key)
{
    if (info.contains(key))
    {
        if (info[key].is_string())
        {
            return info[key].get<std::string>();
        }
        else if (info[key].is_number_integer())
        {
            return std::to_string(info[key].get<int>());
        }
        else if (info[key].is_number_float())
        {
            return std::to_string(info[key].get<double>());
        }
        else if (info[key].is_boolean())
        {
            return std::to_string(info[key].get<bool>());
        }
        else
        {
            return info[key].dump();
        }
    }
    else
    {
        return ("No key " + key);
    }
}

} // namespace backend