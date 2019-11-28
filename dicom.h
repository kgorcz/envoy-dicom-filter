#include "envoy/network/filter.h"
#include "common/common/logger.h"

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace Dicom {

class DicomFilter : public Network::ReadFilter, Logger::Loggable<Logger::Id::filter>
{
public:
    Network::FilterStatus onData(Buffer::Instance& data, bool end_stream) override;
    Network::FilterStatus onNewConnection() override;
    void initializeReadFilterCallbacks(Network::ReadFilterCallbacks& callbacks) override;

private:
    Network::ReadFilterCallbacks* read_callbacks_{};
    // Destination DICOM application name
    std::string called_application_entity_title;
};

}
}
}
}
