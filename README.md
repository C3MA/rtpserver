== Generate Test Content

gst-launch -v gstrtpbin name=r filesrc location=foobar.mkv ! decodebin2
! videorate ! videoscale ! video/x-raw-yuv,width=12,height=10 !
ffmpegcolorspace ! video/x-raw-rgb ! rtpvrawpay ! r.send_rtp_sink_0
r.send_rtp_src_0 ! udpsink host=localhost port=5000 r.send_rtp_sink_0 !
 udpsink port=5001 sync=false async=false udpsrc port=5002 !
r.recv_rtcp_sink_0
