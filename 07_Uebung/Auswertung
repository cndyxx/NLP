Aufgabe 7.1:
In main.cpp line 44 - 46 wird der Text Zeile für Zeile eingelesen und trainiert.
In train_nGramm in nGramm.cpp werden in line 109 - 112 die Startsymbole und das Endsymbol hinzugefügt.
Text Generierung siehe nGramm.cpp generateText line 151 ff.

Aufgabe 7.2.1:
In probabilityHistory in nGramm.cpp line 223 ff. steht die zugehörige Funktion. Es wird eine Historie und ein Suffix
eingegeben, die Funktion berechnet, wie hoch die Wahrscheinlichkeit ist, dass dieses Suffix auf die Historie folgt.

Aufgabe 7.2.2:
In calculateEntropy in nGramm.cpp line 43 ff. wird die Kreuzentropie für einen Testtext berechnet.

Alle Text-Dateien sind in dem Ordner "data" zu finden.
(Hinweis: Immer, wenn im Code Entropie bzw. Entropy steht ist damit eigentlich die Kreuzentropie gemeint.)

Experimentieren mit Kreuzentropie:

    Trainingsdaten: merkel-de-shorter.txt
    Testdaten: merkel-de-shorter.txt

        Trainingsdaten und Testdaten sind die selben:
            für n = 4:
                Cross Entropy 1.74286
            für n = 5
                Cross Entropy 1.07128
            für n = 6:
                Cross Entropy 0.743843
            für n = 7:
                Cross Entropy 0.513737
            ...
            für n = 12
                Cross Entropy 0.090018

    Trainingsdaten: merkel-de-shorter.txt
    Testdaten: 02_inputText_testingEntropy.txt (Testdaten aus gleichem Text, aber Testdaten != Trainingsdaten)

        Trainingsdaten und Testdaten sind unterschiedlich:
            für n = 4:
                Cross Entropy 1.45324
            für n = 5
                Cross Entropy 0.845688
            für n = 6:
                Cross Entropy 0.497134
            für n = 7:
                Cross Entropy 0.26027
            ...
            für n = 12
                Cross Entropy 0.02284

    => Je größer das N desto kleiner ist die Kreuzentropie. Somit ist das Model für ein größeres N besser.
    Voraussetzung: Die Testdaten müssen aus dem Trainingsdaten entnommen werden (90% Trainingsdaten und 10% Testdaten)

Aufgabe 7.3:
In calculateLaplaceDiscount in nGramm.cpp line 8 ff. wird die Laplace-Discounting Wahrscheinlichkeit berechnet.
In der main Funktion kann über die Konsole ausgewählt werden, ob die normale Wahrscheinlichkeit oder die Laplace
Wahrscheinlichkeit verwendet werden soll. Diese führt bei der Historie und der Entropie zu einer anderen Berechnung der
Wahrscheinlichkeit. Beim Text generieren wird die Laplace Wahrscheinlichkeit nicht beachtet, da es dort ohnehin nicht möglich sein sollte,
dass andere Suffixe generiert werden, als die, die tatsächlich im Trainingstext existieren.
