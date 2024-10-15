# Labirynt

## Lista funkcjonalności:
- generowanie labiryntu 
- przebieg algorytmów:
    - dfs
    - bfs
    - Dijkstra
    - algorytm gwiazdka (A*)
- generowanie wykresów (porównanie efektywności poszczególnych algorytmów na podstawie robionych przez nie liczby kroków)
- graficzna reprezentacja labiryntów i ścieżek obieranych przez poszczególny algorytm

<!---algorytm gwiazdka (A*)-->

## Lista technologii:

- C/C++
- Python
    - matplotlib (generowanie wykresów)
- Java
    - Java2D (grafika)

## Format zapisywania labiryntów

Wstępnie (dla wszystkich algorytmów) labirynt zapisywany jest w postaci macierzy o wymiarach *m x n*.

Macierz reprezentująca labirynt zapisaywana jest według następującej zasady:

w *m* wierszach, znajduje sie *n* znaków oddzielonych *spacją*, gdzie:

*1* reprezentuje zajęte pole ("scianę"),\
a *0* reprezentuje pole puste.

Wejścia i wyjścia:

Przyjęte jest, że wejscie (s) zawsze jest w lewym górnym rogu labiryntu, a wyjście (e) zawsze w prawym dolnym rogu labirytnu.

Przykładowa macierz:

```
0 1 0 0 0 0
0 1 0 1 1 1
0 0 0 1 0 0
1 0 1 1 0 0
0 0 0 0 0 0
```

będzie odpowiadać następującemu labiryntowi:

```
┌s┬────┐ 
│ │    │
│ │ ┌──┤
│   │  │
├─ ─┘  │
│      │
└─────e┘ 
```

gdzie:\
s - wejście (start),\
e - wyjście (exit).