var canvasFundo;
var ctxFundo;
var QtdePontos = 10000;
var internalId = -1;

function initFundo() {
	canvasFundo = document.getElementById('Fundo');
	ctxFundo = canvasFundo.getContext('2d');
	
	window.addEventListener('resize', onResizeFundo, false);
	startFundo();
}

function onResizeFundo(){
	canvasFundo.width  = window.innerWidth;
	canvasFundo.height = window.innerHeight;
	ctxFundo.fillStyle = 'black';
	ctxFundo.fillRect(0, 0, canvasFundo.width, canvasFundo.height);
	draw();
}

function startFundo() {
	intervalId = setInterval(draw, 1000 / 30);
	onResizeFundo();
}

function stopFundo() {
	if (intervalId != -1) {
		clearInterval(intervalId);
		intervalId = -1;
	}
}

function draw() {
	var i=0;
	var tick = new Date().getTime();
	//Clear
	ctxFundo.fillStyle = 'rgba(0, 0, 0, 0.15);';
	ctxFundo.fillRect(0, 0, canvasFundo.width, canvasFundo.height);
	//Cor gradiente
	var grad= ctxFundo.createLinearGradient(canvasFundo.width, 0, 0, 0);
	grad.addColorStop(0, '#020205');
	grad.addColorStop(0.5, '#252550');
	grad.addColorStop(1, '#020205');
	ctxFundo.strokeStyle = grad;
	//Desenha a onda
	for(; i < canvasFundo.width + 100;) {
		ctxFundo.beginPath();
		ctxFundo.lineWidth = 30 + i * 0.1;
		
		var x1 = canvasFundo.width - i + 50;
		var y1 = canvasFundo.height / 2 + Math.sin((i - tick / 10) / 200) * (20 + i / 50);
		i += 10;
		var x2 = canvasFundo.width - i + 50;
		var y2 = canvasFundo.height / 2 + Math.sin((i - tick / 10) / 200) * (20 + i / 50);
		i -= 5;
		
		ctxFundo.moveTo(x1, y1);
		ctxFundo.lineTo(x2, y2);
		ctxFundo.stroke();
	}
}