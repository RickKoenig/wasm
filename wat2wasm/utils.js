function fetchAndInstantiate(url, importObject) {
    return fetch(url).then(response =>
        response.arrayBuffer()
    ).then(bytes =>
        WebAssembly.instantiate(bytes, importObject)
    ).then(results =>
        results.instance
    );
}

// slightly faster than above, but web server has to return the
// right MIME type
async function fetchAndInstantiate2(url, importObject) {
    const fetchPromise = fetch(url);
    const { instance } = await WebAssembly.instantiateStreaming(fetchPromise, importObject);
    return instance;
}

function wasmInfo(url) {
    console.log("wasmInfo: " + url);
    WebAssembly.compileStreaming(fetch(url))
    .then(function(mod) {
      var imports = WebAssembly.Module.imports(mod);
      console.log(imports);
      var exports = WebAssembly.Module.exports(mod);
      console.log(exports);
      console.log("done, wasmInfo: " + url);
    }
  );    
}
