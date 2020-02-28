Enescu Tudor 335CC
	
	Pentru a putea genera mesh-ele necesare temei, am scris biblioteca MyObject2D,
in care se alfa metoda CreateBird, care genereaza forma pasarii si formele aferente
obstacolelor.
	
	Modelul pasarii este alcatuit astfel:
5		        6
            3 2  
            0 1  9
        4            11
		         10
		         
8               7   

unde, patratul 0-1-2-3 reprezinta un ochi, patratul 5-6-7-8 reprezinta corpul, din care
am colorat doar triungiurile 5-4-6, 6-4-7 si 8-4-7, 4 este centrul in functie de care 
calculez raza hitbox-ului, care este circular si triunghiul 9-10-11, care reprezinta
ciocul. Toate elementele descrise fac parte din acelasi mesh.
	
	Obstacolele sunt reprezentate de 2 dreptungiuri si sunt caracterizate de inaltimea
obstacolului de jos(generat aleator), distanta dintre cel de sus si cel de jos, care 
este o constanta aleasa de mine, si pozitia pe axa OX, care se modifica in functie de
deltaTimeSeconds si o viteza constanta aleasa de mine.
	
	Generarea obstacolelor se face la intervale de timp constante(prestabilite) si
numarul maxim de obstacole retinute la un moment dat sunt 6. Odata ce aceasta limita
este atinsa, cel mai din stanga obstacol fata de axa OX este sters.
	
	Deplasarea pasarii pe axa OY se face dupa urmatoarele considerente:
	-am stabilit o acceleratie, care ramane constanta
	-la fiecare apel al metodei Update, recalculez viteza in functie de acceleratie si
	deltaTimeSeconds dupa formula: v = v0 - a * t
	-dupa recalcularea vitezei, recalculez pozitia pe axa OY, in functie de acelasi
	deltaTimeSeconds, acceleratie si viteza proaspat recalculata, dupa fromula: 
	y = y0 - v * t - a^2 * t / 2
	-in functie de aceasta coordonata, se face translatia

	Rotatia pasarii se face dupa urmatoarele considerente:
	-am considerat ca la viteza imprimata la apasarea tastei SPACE pasarea este 
	rotita cu pi / 4 si la o viteza aproximativ egala in modul, dar de sens opus,
	este rotita cu -pi / 4
	-am calculat ecuatia dreptei care trece prin punctele (v1, -pi / 4) si (v2, pi / 4)
	si am folosit-o pentru a calcula, la fiecare apel al lui Update, ungiul de rotaie al
	pasarii, pe care l-am si aplicat mesh-ei

	Am afisat un dreptunghi de dimensiunea ferestrei, pentru a realiza fundalul.

	Dimesnsiunea redusa a pasarii imi permite folosirea unui hitbox circular pentru
pasare, motiv pentru care coliziunea intre pasare si obstacol sau pasare si marginile
(superioara si inferioara) ferestrei se face in baza distantei fata de centrul mesh-ei(4).
In urma unei coliziuni, programul se inchide, nu inainte de a afisa scorul final.
	
	Punctarea se face in functie de o variabila care imi indica daca centrul pasarii(4)
se afla in spatiul unui obstacol sau nu. Daca centrul se afla in afara unui obstacol, iar
variabila imi indica contrariul, inseamna ca am trecut cu succes de un obstacol, scorul fiind
incrementat si afisat la consola.

	Jocul nu va incepe decat dupa prima apasare a tastei SPACE, care imprima la fiecare apasare
o viteza prestabilita.