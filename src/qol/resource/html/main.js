function hasQt() {
  return typeof qt !== "undefined";
}

function zeroPad(num, length, radix) {
  var str = num.toString(radix || 10);
  while (str.length < length) {
    str = "0" + str;
  }
  return str.toUpperCase();
}

if (!hasQt()) {
  window.ol = require("openlayers");
}

function createDefaultChannel(callback) {
  if (hasQt()) {
    createChannel(qt.webChannelTransport, callback);
  } else {
    var qol = {
      mapDir: "",
      view: {
        centerLon: 104.3282,
        centerLat: 23.5564,
        minZoom: 5,
        maxZoom: 18,
        zoom: 14
      }
    };
    window.qol = qol;
    if (callback) {
      callback();
    }
  }
}

function createChannel(transport, callback) {
  var webChannel = new QWebChannel(transport, function(channel) {
    var objects = channel.objects;
    window.qol = objects.qol;
    window.qolview = objects.qolview;
    if (callback) {
      callback();
    }
  });
  return webChannel;
}

function loadMap(mapDir) {
  var controls = [];
  //
  var fullScreenControl = new ol.control.FullScreen({
    keys: true
  });
  controls.push(fullScreenControl);
  //
  var mousePosControl = new ol.control.MousePosition({
    coordinateFormat: function(coords) {
      var stringifyFunc = ol.coordinate.createStringXY(6);
      return "[" + stringifyFunc(coords) + "]";
    },
    projection: "EPSG:4326",
    className: "map-mouse-pos",
    target: document.getElementById("mouse-pos")
  });
  controls.push(mousePosControl);
  //
  var overviewMapControl = new ol.control.OverviewMap({});
  controls.push(overviewMapControl);
  //
  var rotateControl = new ol.control.Rotate({
    autoHide: true
  });
  controls.push(rotateControl);
  //
  var scaleLineControl = new ol.control.ScaleLine({});
  controls.push(scaleLineControl);
  //
  var zoomSliderControl = new ol.control.ZoomSlider({});
  controls.push(zoomSliderControl);
  //
  var zoomToExtendControl = new ol.control.ZoomToExtent({});
  controls.push(zoomToExtendControl);
  //
  var map = new ol.Map({
    target: "map",
    layers: [
      new ol.layer.Tile({
        source: new ol.source.XYZ({
          tileUrlFunction: function(coord) {
            var x = zeroPad(coord[1], 8, 16);
            var y = zeroPad(-coord[2] - 1, 8, 16);
            var z = zeroPad(coord[0], 2, 10);
            return mapDir + "/L" + z + "/R" + y + "/C" + x + ".jpg";
          }
        })
      })
    ],
    view: new ol.View({
      minZoom: qolview.minZoom,
      maxZoom: qolview.maxZoom
    }),
    controls: ol.control
      .defaults()
      .extend({
        attribution: false
      })
      .extend(controls),
    interactions: ol.interaction
      .defaults()
      .extend([new ol.interaction.DragRotateAndZoom()])
  });
  window.map = map;

  resetMap();
  binding();
}

function resetMap() {
  map.getView().animate({
    center: ol.proj.fromLonLat([qolview.centerLon, qolview.centerLat]),
    zoom: qolview.zoom,
    duration: 300
  });
}

function binding() {
  if (hasQt()) {
    qolview.focusPoints.connect(focusPoints);
  }
}

function focusPoints() {
  //
}

function focusSource(source) {
  if (!source) {
    return;
  }
  var features = source.getFeatures();
  if (features.length === 0) {
    return;
  }
  var feature0 = features[0];
  geometry = feature0.getGeometry();
  if (!geometry) {
    return;
  }
  var coordinates = geometry.getCoordinates();
  if (coordinates.length === 0) {
    return;
  }
  map.getView().fit(geometry, {
    duration: 300,
    constrainResolution: false,
    padding: [50, 50, 50, 50]
  });
}

$("#user-toolbar").toolbar({
  content: "#user-toolbar-options",
  position: "top"
});
