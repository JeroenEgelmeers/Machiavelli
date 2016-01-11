# CPPS_Machiavelli
Avans Hogeschool - C++ eindopdracht

# Requirements
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

# Maluspunten:
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

# Bonuspunten (gaan we nog niet voor):
- De	paarse	kaarten zijn	lastig	te	implementeren,	omdat	ze	qua	spelregels	op	allerlei	plekken	in	je	
software	architectuur	ingrijpen.	De	moeilijkste	kaart	is	in	dit	verband:	het	Kerkhof,	en	die	levert	
je	+0,5	punt	op als		je	hem	correct	hebt	ingebouwd.	Als	je	ook	de	rest	van	de	paarse	kaarten	goed	
hebt	geïmplementeerd	verdien	je	nog	eens	+0,5	punt;	in	totaal	dus	+1	punt	extra	te	verdienen	
met	het	volledig	implementeren	van	alle	paarse	kaarten.
- De	toestand	van	het	spel	wordt	constant	opgeslagen d.m.v. file	streaming.	Wanneer het	spel	
wordt	onderbroken	(of onverhoopt	crasht)	moet	de	toestand	weer	ingeladen	kunnen	worden	en	
verder	gegaan	waar	men	was	gebleven. Correcte	implementatie hiervan levert	+2 punten. Vergis	
je	niet,	dit	is	lastiger	dan	je	denkt.	Uitdaging!
