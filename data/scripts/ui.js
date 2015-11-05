var UI = {VERSIION: '0.1'};

UI.View = function() {
    var _paper = Raphael(0, 0, window.innerWidth, window.innerHeight);

    this.Container = function(x, y, w, h) {
        var r = _paper.rect(x + h/2 - 1, y + h/2 - 1, 2, 2, 5);
        r.attr({"fill":"#ffffff", "stroke":"#ffffff", "stroke-width":2, cursor:"move"});
        r.show().animate({"x":x, "width":w}, 500, ">", function() {
            r.animate({"fill":"#7687A1", "fill-opacity":0.9, "stroke-width":1, "y":y, "height":h}, 500, ">");
        });
    };

    //this.HMenu = function(str, ) {
    //
    //};
    //
    //this.VMenu = function() {
    //
    //};
};