"use strict";

Module.onRuntimeInitialized = function() {
    init();
};

function init() {
    console.log("emscripten initialized !!");
    var Xslider = document.getElementById("xvalSlider");
    var Xval = document.getElementById("xval");
    var Yslider = document.getElementById("yvalSlider");
    var Yval = document.getElementById("yval");
    var result = document.getElementById("result");

    Xslider.setAttribute("min", -10);
    Xslider.setAttribute("max", 10);
    Xslider.setAttribute("step", .25);
    Xslider.value = 5;
    Yslider.setAttribute("min", -20);
    Yslider.setAttribute("max", 20);
    Yslider.setAttribute("step", .25);
    Yslider.value = 12;

    var updateLabels = function(xval, yval, dist2) {
    Xval.innerText = "xval: " + xval;
    Yval.innerText = "yval: " + yval;
    result.innerText = dist2;
    };

    var listener = function() {
        //const dist2 = Module.ccall('dist2', 'number', ['number', 'number'], [Xslider.value, Yslider.value]);

        const c_dist2 = Module.cwrap('dist2', 'number', ['number', 'number']);
        // Now call it like a regular JS function
        const dist2 = c_dist2(Xslider.value, Yslider.value);

        updateLabels(Xslider.value, Yslider.value, dist2.toFixed(3));
    };

    Xslider.onchange = listener;
    Xslider.oninput = listener;
    Yslider.onchange = listener;
    Yslider.oninput = listener;
    listener();
    //wasmInfo('dist2.wasm');
}

