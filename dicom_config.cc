#include "dicom.h"
#include "envoy/registry/registry.h"
#include "envoy/server/filter_config.h"


namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace Dicom {

class DicomConfigFactory : public Server::Configuration::NamedNetworkFilterConfigFactory
{
public:
    Network::FilterFactoryCb createFilterFactoryFromProto(const Protobuf::Message& /*config*/,
                                                          Server::Configuration::FactoryContext& /*context*/) override
    {
        return [](Envoy::Network::FilterManager& filter_manager) -> void {
            filter_manager.addReadFilter(std::shared_ptr<DicomFilter>(new DicomFilter()));
        };
    }

    ProtobufTypes::MessagePtr createEmptyConfigProto() override
    {
        return std::unique_ptr<google::protobuf::Message>(new google::protobuf::Empty());
    }

    std::string name() override
    {
        return "envoy.filters.network.dicom_proxy";
    }

    bool isTerminalFilter() { return false; }
};

REGISTER_FACTORY(DicomConfigFactory, Server::Configuration::NamedNetworkFilterConfigFactory);

}
}
}
}
