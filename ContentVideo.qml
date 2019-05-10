import QtQuick 2.1
import QtMultimedia 5.0

Rectangle {

    property string defaultVidSource: "file:///e:/Projects/Qt/Video-Switcher/waterfalls.mp4"
    property alias videoOutput: videoOutput

    id: mediaParent

    width: 400
    height: 400
    color:"black"

    MediaPlayer {
        id: mediaPlayer
        loops: Audio.Infinite
        autoPlay: true
        autoLoad: true
        source: defaultVidSource
        onStopped: function(){
            if(mediaPlayer.loops > 0) {
                mediaPlayer.source = defaultVidSource;
                mediaPlayer.loops = Audio.Infinite;
            }

        }
    }

    VideoOutput {
        id:videoOutput
        source:mediaPlayer
        anchors.fill: parent
        function changeSource(src){
            mediaPlayer.source = src;
        }
        function changeLoop(loop){
            if(loop === 1) {
                mediaPlayer.loops = Audio.Infinite;
            }
            else {
                mediaPlayer.loops = 0;
            }
        }
    }
}
