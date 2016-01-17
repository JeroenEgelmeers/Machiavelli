# CPPS_Machiavelli
Avans Hogeschool - C++ eindopdracht

# Opdracht
Maak	in	C++ een	applicatie	van	het	spel	Machiavelli.	Zie	de	bij	deze	eindopdracht	geplaatste	pdf	voor	
de	spelregels\*.	Je	moet	in	tweetallen\** een	console	applicatie	maken	die	door	middel	van	tekst	
weergeeft	wat	jouw	gelegde	kaarten zijn	en/of	wat	de	gelegde	kaarten	van	de	tegenspeler	zijn.	Het	is	
niet	verboden	om	ergens	een	grafische	weergave	van	te	hebben,	maar	je	krijgt	hier	geen	extra	
punten	voor. De	console	geeft	ook	aan	wat	voor	keuzes	een	speler	heeft	indien	deze	een	keuze	moet	
maken.

- \*Machiavelli	is	normaalgesproken	een	spel	voor	2	tot	7	spelers,	maar	voor	deze	opdracht	beperken	
we	ons	tot	de	variant	met	2	spelers.
- \**Er	wordt	altijd	per	tweetal	gewerkt	aan	de	eindopdracht.	Trio’s	zijn	niet	meer	toegestaan.	Bij	
uitzondering	kan	de	docent	toestemming	geven	om	de	opdracht	alleen	uit	te	werken.

### Requirements
Je	schrijft	een	game	server,	die	je	geheel	mag	baseren	op	de	voorbeeldcode.	Je	bent	niet	
verplicht	om	een	speciale	client	te	bouwen;	je	kunt	daarvoor	gewoon	telnet	gebruiken.	Zie	
Blackboard voor	extra	informatie	over	telnet.
- Het	moet volledig in	C++ geprogrammeerd	zijn.
- Je	mag	alleen van	de	Standard	Library gebruik	maken,	plus	eigen	code.	Het	gebruik	van	externe	
libraries	zoals	Boost	of	Poco	is niet	toegestaan.	Die	heb	je	ook	helemaal	niet	nodig:	alles	kan	in	
principe	gedaan	worden	met	de	mogelijkheden	die	de	Standard	Library	je	biedt.	(Tip:	maak	goed	
en	veel	gebruik	van	cppreference.com).
- Als	je	casts	gebruikt	mag	er alleen gebruik	worden	gemaakt	van	C++	style	casts (static_cast,	
const_cast, dynamic_cast,	en	reinterpret_cast),	of	de	varianten	hiervoor	die	shared_ptr	je	biedt.
- Er	mag	alleen gebruik	worden	gemaakt	van	smart	pointers (unique_ptr,	shared_ptr,	en	
weak_ptr).	"Gewone"	pointers	mogen	dus	niet	voorkomen!	(Behalve	natuurlijk	voor	stack-based	
of	global	objects;	zie	opmerking	bij	laatste	Maluspunt	hieronder.)
- Er	mogen	geen	memory	leaks	voorkomen	(maar	dat	krijg	je	dus	cadeau bij	correct	gebruik	van	
smart	pointers).
- Alle	code	moet	exception	safe zijn.	Dat	wil	zeggen	dat	het	niet	mogelijk	moet	zijn	dat	memory	
leaks	ontstaan	als	gevolg	van	een	exception. (En	ook	dit	krijg	je	cadeau	wanneer	je	de	smart	
pointers	goed	toepast.)
- Er	moet	exception	handling plaatsvinden.	De	applicatie	mag	nooit een	exception	aan	de	
gebruiker	doorgeven,	dit	moet	door	middel	van	een	berichtje	in	de	console	weergegeven	
worden,	waarna,	mocht	dit	nodig	zijn,	netjes	uit	het	programma	gesprongen	wordt. (In	het	
voorbeeldprogramma	is	de	exception	handling	op	het	hoogste	niveau	al	helemaal	geregeld,	dus	
als	je	hierop	voortborduurt	zul	je	nooit	zomaar	op	een	exception	crashen.)
- De	bouwkaarten	en	de	karakterkaarten	moeten	beide door	middel	van	een	file	stream worden	
ingelezen. (Als	je	niet	gebruik	wilt	maken	van	de	gegeven bestanden	mag	je	het	ook	op	een	
andere	manier	oplossen.	We	willen	echter	wel	graag	zien	dat	je	tekstbestanden	van	enige	
complexiteit	correct	kunt	verwerken.)
- Je	programma	mag	niet	crashen.	Gebeurt	dat	toch,	dan	ter	plekke	repareren	of	anders	geen	
punt	en	later	opnieuw	proberen.

### Maluspunten:
- Slecht	C++-gebruik	(C++	niet	gebruiken	zoals	het	bedoeld	is):	– 1 punt.
- Slechte	architectuur:	– 0,5 punt.	(We	zijn	ons	bewust	dat	het	assessment	vooral	over	C++ moet	
gaan	en	minder	over	architectuur,	maar	als	onderdeel	van	de	minor	Software	Architectuur	
verwachten	we	op	dit	vlak	geen	prutswerk.	Bovendien:	je	weet	toch	dat	je	minder werk	hebt	als	
het	design	goed	is	?!)
- Nergens	een	file	stream	gebruikt:	– 0,5	punt.
- Geen	C++-style	casts,	maar	klassieke	C-casts:	– 0,5	punt	per	geval.
- Raw	pointers	i.p.v.	smart	pointers:	– 0,5	punt	per	geval. Let	op:	dit	gaat	natuurlijk	alleen	over	
pointers	die	naar	heap-objecten	wijzen.	Als	je	stack-based	of	global	objects	hebt,	hoeven die	niet	
in	smart	pointers	verpakt	te	worden.	Doorgeven	van	het	adres	van	een	dergelijk	object	is	dan	
weliswaar	een	ruwe	pointer,	maar	niet	eentje	die	met	new	is	gemaakt	en	met	delete	moet	
worden	opgeruimd. Die	zijn	gewoon	toegestaan	(hoewel	je	dan	nog	steeds	goed	moet	opletten	
wat	de	life	time	en	scope	van	deze	objecten	zijn,	anders	riskeer	je	dangling	pointers…).

### Bonuspunten (gaan we nog niet voor):
- De	paarse	kaarten zijn	lastig	te	implementeren,	omdat	ze	qua	spelregels	op	allerlei	plekken	in	je	
software	architectuur	ingrijpen.	De	moeilijkste	kaart	is	in	dit	verband:	het	Kerkhof,	en	die	levert	
je	+0,5	punt	op als		je	hem	correct	hebt	ingebouwd.	Als	je	ook	de	rest	van	de	paarse	kaarten	goed	
hebt	geïmplementeerd	verdien	je	nog	eens	+0,5	punt;	in	totaal	dus	+1	punt	extra	te	verdienen	
met	het	volledig	implementeren	van	alle	paarse	kaarten.
- De	toestand	van	het	spel	wordt	constant	opgeslagen d.m.v. file	streaming.	Wanneer het	spel	
wordt	onderbroken	(of onverhoopt	crasht)	moet	de	toestand	weer	ingeladen	kunnen	worden	en	
verder	gegaan	waar	men	was	gebleven. Correcte	implementatie hiervan levert	+2 punten. Vergis	
je	niet,	dit	is	lastiger	dan	je	denkt.	Uitdaging!

# Informatie over de applicatie
### Runnen van de applicatie.
Zorg aller eerst dat telnet is geactiveerd op je systeem. Dit dient op een windows computer via de instellingen nog gedaan te worden (beknopt: Windows Control Panel -> Programs and Features -> Turn Windows features on or off -> check Telnet Client.
Vanaf dat moment kun je in een Command Prompt window telnet als commando gebruiken.).

Vervolgens start je een CMDprompt en type je daar: telnet localhost 1080
