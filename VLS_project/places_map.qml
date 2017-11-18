import QtQuick 2.0
import QtPositioning 5.5
import QtLocation 5.6

Item {
    anchors.fill: parent

    Plugin {
        id: mapPlugin
        name: "osm"
    }

    property variant locationParis: QtPositioning.coordinate(48.8534, 2.3488)

    Map {
        id: map
        anchors.fill: parent
        plugin: mapPlugin
        center: locationParis
        zoomLevel: 12

        MapItemView {
            model: stationModel
            delegate: MapQuickItem {
                id: station
                coordinate: QtPositioning.coordinate(longitude, latitude)

                sourceItem: Column {
                    Image {
                        id: image;
                        source: "marker.png"
                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                if (descr.text == "") {
                                    descr.text=describtion
                                }
                                else {
                                    descr.text=""
                                }
                            }
                        }
                    }
                    Text {
                        id: descr
                        text: ""
                        font.bold: true
                    }
                }
                anchorPoint.x: image.width/2
                anchorPoint.y: image.width
            }
        }
    }
}
