#include "dicom.h"

#include <iostream>
#include <sstream>
#include <string>

#include "envoy/network/connection.h"
#include "common/common/assert.h"
#include "common/tcp_proxy/tcp_proxy.h"
#include "dcmtk/ofstd/ofstring.h"
#include "dcmtk/dcmdata/dcdict.h"

namespace Envoy {
namespace Extensions {
namespace NetworkFilters {
namespace Dicom {

Network::FilterStatus DicomFilter::onData(Buffer::Instance& data, bool /*end_stream*/)
{
    DcmDataDictionary dcmdat(false, false);

    if(called_application_entity_title.empty() && data.length() >= 26) {
        char buf_called_ae[17];
        memset(buf_called_ae, 0, 17);
        data.copyOut(10, 16, buf_called_ae);
        called_application_entity_title = std::string(buf_called_ae);
        auto firstSpace = called_application_entity_title.find_first_of(' ');
        if(firstSpace != std::string::npos && firstSpace != 0) {
            called_application_entity_title = called_application_entity_title.substr(0, firstSpace);
        }
        ENVOY_CONN_LOG(debug, "data: {}", read_callbacks_->connection(), data.toString());
        ENVOY_CONN_LOG(info, "called application entity title: {}", read_callbacks_->connection(),
            called_application_entity_title);

        read_callbacks_->connection().streamInfo().filterState().setData(
            TcpProxy::PerConnectionCluster::key(),
            std::make_unique<TcpProxy::PerConnectionCluster>(called_application_entity_title), 
            StreamInfo::FilterState::StateType::Mutable);

        read_callbacks_->connection().readDisable(true);
    }
    return Network::FilterStatus::Continue;
}

Network::FilterStatus DicomFilter::onNewConnection()
{
    ENVOY_CONN_LOG(debug, "onNewConnection", read_callbacks_->connection());
    read_callbacks_->connection().readDisable(false);
    return Network::FilterStatus::StopIteration;
}

void DicomFilter::initializeReadFilterCallbacks(Network::ReadFilterCallbacks& callbacks)
{
    read_callbacks_ = &callbacks;
}

}
}
}
}
