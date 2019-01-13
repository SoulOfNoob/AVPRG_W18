AVPRG Projektkonzept
====================

Einleitung
----------

Es geht um ein Projekt als Prüfungsleistung der Vorlesung AVPRG des Studiengangs Media Systems.
Das Projekt umfasst das Entwickeln einer Software unter der Verwendung der OpenCV Bibliothek unter C++ und / oder der WebAudio API mit JavaScript im Webbrowser.
Die fertige Software oder der fertige Prototyp wird dann am 18.12.2018 im Rahmen der Projektpräsentationen des Dept. MT Präsentiert.
Der Name des Projektes lautet "Feel the Sound".

Projektziel
-----------

Unser Ziel ist es ein haptisches Audio interface zu entwickeln.
Der User hat eine Fläche vor sich auf der sich Markierungen und Objekte befinden.
Darüber befindet sich eine Webcam die mit dem Computer verbunden ist auf dem die Software läuft.
Die Position, Anordnung und Ausrichtung der Objekte steuert einen digitalen Synthesizer und die Eingaben werden in Echtzeit verarbeitet und ein entsprechender Ton ausgegeben.
Außerdem soll der User in der Lage sein anhand von mehreren Objekten/Punkten oder einem Faden Filterfunktionen zu erstellen und mit diesen eine, vom User ausgewählte, Audiospur verändern zu können.
Des Weiteren sind Tastenfelder vorhanden mit denen man verschiedene Noten spielen kann wie auf einem Keyboard.
Der User soll haptisch erfassen können was für Einstellungen welche Wirkung auf den Sound haben und somit ein auditives Feedback haben.

Anforderungsanalyse
-------------------

Der User ..
-   kann die Software größtenteils über das haptische Audio interface steuern.
-   kann eigene Audiodateien auswählen und durch das haptische Interface bearbeiten.
-   kann mit dem haptischen Interface einen Oszillator steuern.
-   kann im haptischen Interface auf Tasten "drücken" um Noten zu erzeugen.
-   kann im haptischen Interface einstellen, ob der User die Töne vom Oszillator, den Klang der Noten oder den Sound der Audiodatei bearbeiten will.
-   kann im haptischen Interface einstellen, ob überhaupt Sound abgespielt wird, ob die Audiodatei wiederholt werden soll sowie die Lautstärke.
-   kann mit einer Schnur oder mehreren Objekten/Punkten eine Kurve erstellen und mit dieser, die vom User erstellten Töne oder die vom User ausgewählte Audiodatei beeinflussen.
-   kann mit dem haptischen Interface einen Equalizer konfigurieren und diesen auf die vom User erstellten Töne oder die vom User ausgewählte Audiodatei wirken lassen.
-   Auswahl des Filter Types
-   Frequenz
-   Detune
-   Q
-   Gain
-   findet sich auf der Fläche mit den Markierungen gut zurecht.

Technische Rahmenbedingungen
----------------------------

Laptop mit Windows 10 mit angeschlossener USB-Webcam
Unter verwendung von C++ und der OpenCV Bibliothek
Audio Ausgabe über Webbrowser und der WebAudio API (JavaScript)
Kein WLAN notwendig
Die Wahl der Programmiersprache(n) basiert auf den Projektvorgaben.
Die Wahl der Hardware ist begründet in der notwendigen mobilität des Projektes Zwecks vor Ort Präsentation.

Technisches Konzept
-------------------
![](https://lh5.googleusercontent.com/0zdj5botM56gcdoncz68f8zQKuFmEzIcAe2t5kGe2qpUxHJ0IPfuprE-iDyMWN7-GppgHkhEUlny_sRk_xNb6YnS2ojgSRAL-LHFN1EJMTDrVzWnTcMT2rGkneui5RBD3zlZky5H)

Um aus Punkten in der "makeCurve"-Methode eine Filterfunktion zu machen, nutzen wir Polynominterpolation.
Die "sendData"-Methode versuchen wir mit einer seriellen Schnittstelle umzusetzen.
Sollte dies nicht Funktionieren wollen wir Sockets verwenden.

Bedienkonzept
-------------

Das User Interface besteht aus einer Fläche mit Markierungen, die auf einem Tisch ausgebreitet wird. Darüber wird eine Kamera montiert.
Auf der Fläche befinden sich mehrere Objekte, wie Würfel oder Pyramiden, die der User bewegen und ausrichten kann.
Jedes Objekt steht für einen Soundeffekt (node). Die Orientierung des Objektes steht für den Wert eines Parameters des Effektes und die Position der Objekte steuert die Reihenfolge der Effekte.
Position und Ausrichtung werden dann in Echtzeit ausgewertet und angewendet.
Weiterhin befinden sich markierte Bereiche auf der Fläche die Noten repräsentieren und bei Gesten im jeweiligen Bereich einen Klang auslösen.

Zeitplan
--------
![](https://lh3.googleusercontent.com/hosDGRpYhONH8O9levmUPlmhYf1PDrsaT8ix1aDtVwNIfTwrW4nnNJ4MJjFWFFbbc5a6IWpjdw2SqDMc6TppeezjsPICMS9__xywhsiTZwwMh1GdaMQ0LQjUtVHWbKCZtZhMFPFn)

Teamplanung
-----------

- Erstellen eines intuitiven Designs - Beide
- C++ Grundlage - Jan Ryklikas
- Grundlage JS - Leif Heyne
- Besorgen der Kamera - Leif Heyne
- Schaffen einer Schnittstelle - Jan Ryklikas
- Erkennen von Veränderungen - Beide
- Herausfinden von richtigen Werten - Beide
- Schreiben der Updatefunktion - Leif Heyne
