#!/bin/bash

# Requirement for this script is gstreamer-tools

# 
if [ ! -f /usr/bin/gst-launch ]; then
 echo "YOU MUST install the required tool!"
 sudo aptitude install gstreamer-tools
fi

# the command itself
/usr/bin/gst-launch  \
      videotestsrc pattern=red \
   !  video/x-raw-rgb, format=\(fourcc\)RGB, width=12, height=10, frame-rate=1/1 \
   !  rtpvrawpay \
   !  udpsink host=127.0.0.1 port=5000
