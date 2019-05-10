import QtQuick 2.1
import QtQuick.Window 2.1
import com.techadvise.videocontroller 1.0

Window {
    property string vidSource: "file:///e:/Projects/Qt/Video-Switcher/waterfalls.mp4"

    id: root
    color: "black"
    width: 400
    height: 400
    visible: true


    ContentVideo {
        id: contentVideo
        anchors.fill: parent
        defaultVidSource: vidSource
    }

    VideoController {
        id: videoController
        onVideoSrcChanged: function(src, loop){
            console.log("Video source change:", src);


            contentVideo.videoOutput.changeSource(src);
            contentVideo.videoOutput.changeLoop(loop);
        }
    }
}
