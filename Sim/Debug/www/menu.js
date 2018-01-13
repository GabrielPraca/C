var Menus;
var DivMenus;
var DivMain;
var DivItens;
var MenuIndex = 0;

var ITEM_WIDTH = 150;

function initMenu() {
	Menus = [
			{	"Menu": "Tela",
				"Itens": [ "Resolução", "Delay", "Método", "Bla 1", "Bla 2" ] },
			{	"Menu": "Câmera",
				"Itens": [ "Delay", "Item 2" ] },
			{	"Menu": "Logs",
				"Itens": [ "Teclado", "PowerUp" ] },
			{	"Menu": "Arquivos",
				"Itens": [ "Item 1", "Item 2" ] },
			{	"Menu": "Menu 5",
				"Itens": [ "Item 1", "Item 2" ] },
			{	"Menu": "Menu 6",
				"Itens": [ "Item 1", "Item 2" ] },
			{	"Menu": "Menu 7",
				"Itens": [ "Item 1", "Item 2" ] }
			];
	DivMain = document.getElementById("DivMain");
	DivMenus = document.getElementById("DivMenus");
	DivItens = document.getElementById("DivItens");
	
	//Cria os menus
	for(var i = 0; i < Menus.length; i++) {
		//Menu
		var _Menu = document.createElement("div");
		_Menu.className = "Menu";
		_Menu.innerHTML = Menus[i].Menu;
		DivMenus.appendChild(_Menu);
		
		//Itens desse menu
		var _Itens = document.createElement("div");
		_Itens.className = "Itens";
		DivItens.appendChild(_Itens);
		for(var j = 0; j < Menus[i].Itens.length; j++) {
			var _Item = document.createElement("div");
			_Item.className = "Item";
			_Item.innerHTML = Menus[i].Itens[j];
			_Itens.appendChild(_Item);
		}
	}
	
	//Coloca um efeito de brilho no menu selecionado
	DivMenus.getElementsByClassName("Menu")[MenuIndex].style.textShadow = "0px 0px 3px #fff";
	
	//Eventos
	window.addEventListener('keydown', onKeyDownMenu, false);
	window.addEventListener('resize', onResizeMenu, false);
	onResizeMenu();
}

function setDivMenusPosition(position) {
	DivMenus.style.left = position.x + 'px';
	DivMenus.style.top = position.y + 'px';
}

function getDivMenusPosition(menuIndex) {
	var position = {"x": 0, "y": 0};
	
	position.x = DivMain.clientWidth / 2 - ITEM_WIDTH / 2 - ITEM_WIDTH * menuIndex;
	position.y = DivMain.clientHeight / 2 - DivMenus.clientHeight / 2;
	
	return position;
}

function getItensPosition(ItensIndex) {
	var position = {"x": 0, "y": 0};
	var MenuPos = getDivMenusPosition(MenuIndex);
	
	position.x = MenuPos.x + ITEM_WIDTH * ItensIndex;
	position.y = MenuPos.y + DivMenus.clientHeight;
	
	return position;
}

function onKeyDownMenu(e) {
	switch(e.keyIdentifier) {
		case "Left":
			if (MenuIndex > 0) {
				DivMenus.getElementsByClassName("Menu")[MenuIndex].style.textShadow = "";
				MenuIndex--;
				DivMenus.getElementsByClassName("Menu")[MenuIndex].style.textShadow = "0px 0px 3px #fff";
				onResizeMenu_transDurat(250);
			}
			break;
		case "Right":
			if (MenuIndex < Menus.length - 1) {
				DivMenus.getElementsByClassName("Menu")[MenuIndex].style.textShadow = "";
				MenuIndex++;
				DivMenus.getElementsByClassName("Menu")[MenuIndex].style.textShadow = "0px 0px 3px #fff";
				onResizeMenu_transDurat(250);
			}
			break;
	}
}

function onResizeMenu() {
	onResizeMenu_transDurat(0);
}

function onResizeMenu_transDurat(delay) {
	DivMenus.style.transitionDuration = delay + "ms";
	
	var position = getDivMenusPosition(MenuIndex);
	setDivMenusPosition(position);
	
	var Itens = DivItens.getElementsByClassName("Itens");
	for(var i = 0; i < Itens.length; i++) {
		position = getItensPosition(i);
		Itens[i].style.left = position.x;
		Itens[i].style.top = position.y;
	}
}