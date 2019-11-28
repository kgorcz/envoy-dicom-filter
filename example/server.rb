require 'dicom'
include DICOM

$stdout.sync = true
s = DServer.new(104, :host_ae => "MY_DICOM_SERVER")
s.start_scp("/app/")

