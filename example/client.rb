require 'dicom'
include DICOM

$stdout.sync = true

envoy_ip = ENV["ENVOY_IP"]
ae_title = ENV["AE_TITLE"]
puts 'envoy_ip: ' + envoy_ip
puts 'ae_title: ' + ae_title

client = DClient.new(envoy_ip, 10000, {:host_ae => ae_title})
client.send("example.dcm")

