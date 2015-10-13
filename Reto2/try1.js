// Comprueba si un número es entero no negativo
nonegint = function(x) {
	return x >= 0 && (x%1) == 0;
}

solve = function(s, a) {
	if (!nonegint(s))
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
			else if ((solt=solve(nuevo = s/ai, resto)) != false)
				return solt + "; " + ai + " * " + nuevo + " = " + s;
			else if ((solt=solve(nuevo = ai/s, resto)) != false)
				return solt + "; " + ai + " / " + nuevo + " = " + s;
			else if ((solt=solve(nuevo = s*ai, resto)) != false)
				return solt + "; " + nuevo + " / " + ai + " = " + s;
			else if ((solt=solve(nuevo=s, resto)) != false)
				return solt;
		}
		return false;
	}
}

var sol = window.prompt("Valor a buscar","");
var list = window.prompt("Valores disponibles (separados por comas)","").split(", ").join(",").split(",")
alert("[" + list.join(", ") + "] -> " + sol + ":\n\n" + solve(sol,list));