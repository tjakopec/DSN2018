

var podaci={klima: "0", rasvjeta: "0", grijanje: "0"};
var dweetId="dsn2018";
ucitajAPI();
postaviOznakeCelija();

document.body.onclick= function(e){
	e=window.event? event.srcElement: e.target;
	//console.log(e);
	if(e.nodeName==="IMG" || e.className && e.className.indexOf('celija')!=-1){
		celijaKlik(e.nodeName==="IMG" ? e.parentNode : e);
	}
		
 }



 function celijaKlik(e){
	 var kontrola = e.className.replace("celija ","");
	 postaviOznakuUcitanje(kontrola);
	 switch(kontrola){
		 case "klima":
		 	podaci.klima = podaci.klima=="0" ? "1" : "0";
			 break;
		case "rasvjeta":
		 	podaci.rasvjeta = podaci.rasvjeta=="0" ? "1" : "0";
			 break;
		case "grijanje":
		 	podaci.grijanje = podaci.grijanje=="0" ? "1" : "0";
		 	break;

		 default:
		 	break;
	 }
	 odradiAPI();
	 postaviOznakeCelija();
 }

 function postaviOznakeCelija(){
	document.getElementById("klima").src="img/klima_" + podaci.klima  + ".svg";
	document.getElementById("rasvjeta").src="img/rasvjeta_" + podaci.rasvjeta  + ".svg";
	document.getElementById("grijanje").src="img/grijanje_" + podaci.grijanje  + ".svg";
}

 function postaviOznakuUcitanje(elementId){
	document.getElementById(elementId).src="img/ucitavam.svg";
}

function odradiAPI(){
	console.log(podaci);
	dweetio.dweet_for(dweetId, podaci);
	ucitajAPI();
}

function ucitajAPI(){
	dweetio.get_latest_dweet_for(dweetId, function(err, dweet){
		if(dweet!=null){
			podaci=dweet[0].content;
			console.log(podaci);
			postaviOznakeCelija();
		}  
	});
}
 