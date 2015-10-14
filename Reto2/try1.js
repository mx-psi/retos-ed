// Comprueba si un número es entero positivo
posint = function(x) {
	return x >= 1 && (x%1) == 0;
}

solve = function(s, a) {
	if (!posint(s))
		return false;
	var n = a.length;
	if (n == 2) {
		if (a[0] + a[1] == s)
			return a[0] + " + " + a[1] + " = " + s;
		else if (a[0] - a[1] == s)
			return a[0] + " - " + a[1] + " = " + s;
		else if (a[1] - a[0] == s)
			return a[1] + " - " + a[0] + " = " + s;
		else if (a[0] * a[1] == s)
			return a[0] + " * " + a[1] + " = " + s;
		else if (a[0] / a[1] == s)
			return a[0] + " / " + a[1] + " = " + s;
		else if (a[1] / a[0] == s)
			return a[1] + " / " + a[0] + " = " + s;
		else 
			return false;
	} else {
		for (var i = 0; i < n; i++) {
			var ai = a[i];
			var resto = a.concat();
			resto.splice(i, 1);
			var nuevo, solt;
			if ((solt=solve(nuevo = s-ai, resto)) != false)
				return solt + "; " + ai + " + " + nuevo + " = " + s;
			else if ((solt=solve(nuevo = ai-s, resto)) != false)
				return solt + "; " + ai + " - " + nuevo + " = " + s;
			else if ((solt=solve(nuevo = s+ai, resto)) != false)
				return solt + "; " + nuevo + " - " + ai + " = " + s;
			else if (ai != 1 && (solt=solve(nuevo = s/ai, resto)) != false)
				return solt + "; " + ai + " * " + nuevo + " = " + s;
			else if ((solt=solve(nuevo = ai/s, resto)) != false)
				return solt + "; " + ai + " / " + nuevo + " = " + s;
			else if (ai != 1 && (solt=solve(nuevo = s*ai, resto)) != false)
				return solt + "; " + nuevo + " / " + ai + " = " + s;
			else if ((solt=solve(nuevo=s, resto)) != false)
				return solt;
		}
		return false;
	}
}

var rand = confirm("Pulsa Aceptar para generar valores aleatorios, o Cancelar para introducirlos a mano");
if (rand) {
	var posibles = [1,2,3,4,5,6,7,8,9,10,25,50,75,100]; var pl = posibles.length;
	var num_valores = 6;
	var sol = Math.floor(Math.random()*900)+100;
	var list = [];
	for (var i = 0; i < num_valores; i++)
		list[i] = posibles[Math.floor(Math.random()*pl)];
} else {
	var sol = window.prompt("Valor a buscar","");
	var list = window.prompt("Valores disponibles (separados por comas)","").split(", ").join(",").split(",")
	for (var i in list) list[i] = parseInt(list[i], 10);
}
alert("[" + list.join(", ") + "] -> " + sol + ":\n\n" + solve(sol,list));
