# AppOale
Aplicatie simpla de organizare pentru oale de otel folosite in fluxul tehnologic de fabricare a otelului. /Simple app used for organizing steel ladles used in the making of steel

# Dependente/Dependencies:
-gtk3 (gtk3-3.24.38 last used)
-libxlsxwriter (libxlsxwriter-1.1.5-1 last used)

Instructiuni pentru instalarea bibliotecii gtk3 pot fi gasite aici /Instructions for installing gtk3 can be found here: https://www.gtk.org/docs/installations/.

# Descriere

In prima fereastra se introduc oalele. Se introduce "Nume", "Nr.sarje" si "Observatii si se apasa butonul "Input"; oala va aparea in tabelul de mai jos. Butonul "Organize" ordoneaza descrescator oalele in functie de numar de sarje, iar butonul "Clear" sterge toate oalele.

Cand se apasa butonul "Map" se va deschide o fereastra noua unde se va introduce "Numar de saptamani"(numar intreg pozitiv), "Numar de oale folosite/zi"(numar intreg pozitiv) si "Data incepere(zi de luni)"(data in format XX.XX.XXXX ; de exemplu 01.01.2001). Se apasa butonul "Creare mapa" si va aparea in tabelul de mai jos harta si atentionarile in dreapta. Butonul "Creare fisier excel" va crea un fisier excel numit "~Harta.xlsx" ce fa vi in format similar cu tabelul creat anterior.
