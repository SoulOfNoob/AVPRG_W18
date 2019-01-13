
var allFrequencies = [
    8.1757989156,       8.6619572180,       9.1770239974,
    9.7227182413,       10.3008611535,      10.9133822323,
    11.5623257097,      12.2498573744,      12.9782717994,
    13.7500000000,      14.5676175474,      15.4338531643,
    16.351597831287414, 17.323914436054505, 18.354047994837977,
    19.445436482630058, 20.601722307054366, 21.826764464562746,
    23.12465141947715,  24.499714748859326, 25.956543598746574,
    27.5,               29.13523509488062,  30.86770632850775,
    32.70319566257483,  34.64782887210901,  36.70809598967594,
    38.890872965260115, 41.20344461410875,  43.653528929125486,
    46.2493028389543,   48.999429497718666, 51.91308719749314,
    55,                 58.27047018976124,  61.7354126570155,
    65.40639132514966,  69.29565774421802,  73.41619197935188,
    77.78174593052023,  82.4068892282175,   87.30705785825097,
    92.4986056779086,   97.99885899543733,  103.82617439498628,
    110,                116.54094037952248, 123.47082531403103,
    130.8127826502993,  138.59131548843604, 146.8323839587038,
    155.56349186104046, 164.81377845643496, 174.61411571650194,
    184.9972113558172,  195.99771799087463, 207.65234878997256,
    220,                233.08188075904496, 246.94165062806206,
    261.6255653005986,  277.1826309768721,  293.6647679174076,
    311.1269837220809,  329.6275569128699,  349.2282314330039,
    369.9944227116344,  391.99543598174927, 415.3046975799451,
    440,                466.1637615180899,  493.8833012561241,
    523.2511306011972,  554.3652619537442,  587.3295358348151,
    622.2539674441618,  659.2551138257398,  698.4564628660078,
    739.9888454232688,  783.9908719634985,  830.6093951598903,
    880,                932.3275230361799,  987.7666025122483,
    1046.5022612023945, 1108.7305239074883, 1174.6590716696303,
    1244.5079348883237, 1318.5102276514797, 1396.9129257320155,
    1479.9776908465376, 1567.981743926997,  1661.2187903197805,
    1760,               1864.6550460723597, 1975.533205024496,
    2093.004522404789,  2217.4610478149766, 2349.31814333926,
    2489.0158697766,    2637.02045530296,   2793.825851464031,
    2959.955381693075,  3135.9634878539946, 3322.437580639561,
    3520,               3729.3100921447194, 3951.066410048992,
    4186.009044809578,  4434.922095629953,  4698.63628667852,
    4978.031739553295,  5274.04091060592,   5587.651702928062,
    5919.91076338615,   6271.926975707989,  6644.875161279122,
    7040,               7458.620184289437,  7902.132820097988,
    8372.018089619156,  8869.844191259906,  9397.272573357044,
    9956.06347910659,   10548.081821211836, 11175.303405856126,
    11839.8215267723,   12543.853951415975];


    window.onload = function() {
        init();
      }
    

    transmitter = null; 

    function connect() {
        var socket = new WebSocket("ws://localhost:12345");
        socket.onopen = function() {
            console.log('socket connected');
            new QWebChannel(socket, function(channel) {
                // make dialog object accessible globally
                transmitter = channel.objects.transmitter;
                transmitter.sendJSON.connect(function(payload) {
                        payload = JSON.parse(payload);
                        console.log("payload" +payload);
                        distortion.curve = MyDistortionCurv(payload);
                        
                });
            });
        }
    
        
    socket.onclose = function() {
        console.log('socket Closed');
        setTimeout(function() {
            connect();
          }, 1000);
    };
     
    
    socket.onerror = function() {
    	console.log('socket Error');
    };
      }
      
      connect();

   



    setInterval(function(){
        console.log('send request');
        if (! transmitter ) { return; }
        transmitter.getJSON();
      
    }, 1000);



function init(){
    context = new AudioContext();

    //Maste gain
    masterGain = context.createGain();
    masterGain.gain.value = .1;
    console.log(masterGain)
    // Load musik
    musikURL = "../musik/"
    sound = null;
   
    
    //playButton
    playStopButton = document.getElementById("playStopButton");
    isPlaying = false;
    playStopButton.addEventListener("click", function (e) {
        if(sound){
            if (isPlaying) {
                sound.pause();
                document.getElementById("playStopButton").innerHTML = "Play";
            } else {
                sound.play();
                document.getElementById("playStopButton").innerHTML = "Stop";
            }
            isPlaying = !isPlaying;
            
        }
    });
    
    // Distortion
    distortion = context.createWaveShaper();
   
    
    playStopButton = document.getElementById("playStopButton");
    
    //selector
    sel = document.getElementById('list');
    
    sel.addEventListener("click",function() {loadAudio(sel.value)})
    
    isDistortion = false;
    distortionButton = document.getElementById("distortionButton");
    
    distortionButton.addEventListener("click", toggleDistationWave);
    
   
document.getElementById("gainSlider").addEventListener("input", function (e) {
   
    var gainValue = (this.value / 40);
    document.getElementById("gainOutput").innerHTML = gainValue + " %";
    masterGain.gain.value = gainValue;
    console.log(masterGain)
});
    
    
    const inputElement = document.getElementById("input");
    inputElement.addEventListener("change", handleFiles, false);
    function handleFiles() {
        const fileList = this.files; /* now you can work with the file list */
        console.log(fileList)
        
        fillSelect(fileList);
    }
}

function loadAudio(name){
    if(isPlaying){
        if(sound){
            if (isPlaying) {
                sound.pause();
                document.getElementById("playStopButton").innerHTML = "Play";
            } else {
                sound.play();
                document.getElementById("playStopButton").innerHTML = "Stop";
            }
            isPlaying = !isPlaying;

        }
    }
    sound = new Audio([musikURL + name]);
    source = context.createMediaElementSource(sound);
    source.connect(masterGain);
    masterGain.connect(context.destination)
    sound.loop = true;
}



function toggleDistationWave(){
    if(isPlaying){
        if(!isDistortion){
            console.log("on");
            source.disconnect();
            source.connect(distortion);
            distortion.connect(masterGain);
            masterGain.connect(context.destination);
            document.getElementById("distortionButton").innerHTML = "Distortion On";
        }
        else{
            console.log("off"); 
            source.disconnect();
            source.connect(masterGain);
            masterGain.connect(context.destination);
            document.getElementById("distortionButton").innerHTML = "Distortion Off";
        }
        isDistortion = !isDistortion;
    }
}

function fillSelect(array){
    
    for(var i = 0; i < array.length; i++) {
        var opt = document.createElement('option');
        opt.innerHTML = array[i].name;
        opt.value = array[i].name;
        sel.appendChild(opt);   
    }
}


// Curve later replace
function makeDistortionCurve(amount) {
    var n_samples = 44100,
    curve = new Float32Array(n_samples);


    for (i = 0; i < n_samples; i++ ) {
        var x = i * 2 / n_samples - 1;
        curve[i] = (Math.PI + amount) * x / (Math.PI + (amount * Math.abs(x)));
    }
    console.log(curve)

    return curve;
};

function MyDistortionCurv(array){
    MyCurve = new Float32Array(array.length)
    max_of_array = Math.max.apply(Math, array);
    min_of_array = Math.min.apply(Math, array);
    max_of_array -= min_of_array;
    console.log(array)

    for(i = 0;i< array.length; i++){
        var val = array[i];
        val -= min_of_array;
        val -= 0.5*max_of_array;
        val *=2;
        val /= max_of_array
        MyCurve[i] = val;
        
    }
    console.log(MyCurve)
    return MyCurve;
}
