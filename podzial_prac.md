# Podzial prac:

### Jakub Malinowski (przewodniczący):

- [x] Proceduralne generowanie labiryntu w postaci wstępnej (numerycznej/macierzowej) (w C) (tygodnie 1-5):
    - [x] Algorytm generacji labiryntu (tygodnie 1-3).
    - [x] Zamiana labiryntu w postaci danych/postaci numerycznej na plik tekstowy (plik ".txt") (tygodnie 4-5).
- [x] Algorytm A* (A gwiazdka) (w C) (tygodnie 6+).
    - [x] prosta implementacja algorytmu.
    - [x] opracowanie w oparciu o własną strukturę danych.

### Krystian Dzikiewicz:

- [x] Opracowanie struktury danych, która będzie przechowywała dane ("mapę") labiryntu (C++) (tygodnie 1-2, później poprawki).
- [x] Algorytmy dfs i bfs (tygodnie 3-5).
- [ ] Testy jednostkowe (integracja z github CI) (tygodnie 6+)

### Ola Grabowska:

- [x] Algorytm Dijkstry (tygodnie 2+).
    - [x] ogólna implementacja algorytmu.
    - [x] implementacja na własnej strukturze danych (grafowa).
    - [x] opracowanie w oparciu o nową strukturę danych
- [x] Generowanie wykresów (mathplotlib) (tygodnie 4+).

### Jakub Markowski:

- [x] Graficzna reprezentacji obieranych ścieżek i labiryntu (Java2D) (tygodnie 1-9).
    - [x] graficzna reprezentacja labiryntu (tygodnie 1-5).
        - [x] Przykład reprezentowania graficznego labiryntów tzw. "hard-coded" (tygodnie 1-2).
        - [x] Generowanie reprezentacji graficznej labiryntów na podstawie labiryntu zapisanego w postaci tekstowej (pliku ".txt") (tygodnie 3-5).
    - [x] graficzna reprezentacja/animacja ścieżek (tygodnie 5-9).
    - [x] doszlifowywanie grafiki (tygodnie 10+)\
    \
\

### Still to do:

- [x] Poprawki i doszlifowywanie "main.cpp" (tygodnie 10+)
    - [x] "opakowanie" w funkcje powtarzających się/wykonywanych wiele razy partii programu.
    - [x] Dodanie (funkcji z) "maze_generator.c" jako części "main.cpp"
    - [ ] (Opcjonalnie) Przyjmowanie argumentów z wywoływania programu przez wiersz poleceń (termninal)
        - [x] częściowo wykonane/zrobione
    - [x] ogólne "czyszczenie" kodu.
- [ ] Naprawienie problemów i niedociągnięć z xmake.
    - [x] częściowo wykonane/zrobione
- [ ] (Opcjonalnie) Graficzny Interfejs Użytkownika w oknie reprezentacji graficznej.
- [ ] Integracja "main.cpp" z "Main.java" (póki co: przyjmowanie plików tekstowych z wynikami generowanymi przez "main.cpp" do "Main.java")
    - [x] częściowo zrealizowane (na razie po prostu wrzucanie przez program main.cpp plików będących wynikami działań algorytmów na labiryncie do katalogu o ścieżce: *src/main/resources/*).
- [ ] Integracja "main.cpp" z tworzeniem wykresów na podstawie wyników (długości/ilości kroków wykonanych przez poszczególne algorytmy).
- [x] Dynamiczne alokowanie pamięci (rozmiaru struktury danych przechowującej macierz/"tablicę" labiryntu) w "maze_generator.c" zamiast "fixed-size"/rozmiaru o stałej wielkości/liczbie określonej przez macro na początku w definicjach programu - aby było to bardziej kompatybilne z zadeklarowanym już w "main.cpp" przyjmowaniem argumentów z wiersza poleceń (w trakcie wywoływania programu) i w ten sposób określania (***za każdym razem innego - wtedy - z góry niezdefiniowanego***) rozmiaru labiryntu.

tydzień 1 = 15.10.2024 - 21.10.2024 \
tydzień 2 = 22.10.2024 - 28.10.2024 \
tydzień 3 = 29.10.2024 - 04.11.2024 \
tydzień 4 = 05.11.2024 - 11.11.2024 \
tydzień 5 = 12.11.2024 - 18.11.2024 \
tydzień 6 = 19.11.2024 - 25.11.2024 \
tydzień 7 = 26.11.2024 - 02.12.2024 \
tydzień 8 = 03.12.2024 - 09.12.2024 \
tydzień 9 = 10.12.2024 - 16.12.2024
