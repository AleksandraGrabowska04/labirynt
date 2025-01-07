# Labirynt

## Lista funkcjonalności:
- Generowanie labiryntu 
- Przebieg algorytmów:
    - DFS (*Depth-First-Search*)
    - BFS (*Breadth-First Search*)
    - Dijkstra
    - Algorytm gwiazdka (A\*)
- Generowanie wykresów (porównanie efektywności poszczególnych algorytmów na podstawie robionych przez nie liczby kroków)
- Graficzna reprezentacja labiryntów i ścieżek obieranych przez poszczególny algorytm
- Porównanie skuteczności (efficiency) (po ilu "krokach" algorytm jest w stanie znaleźć prawidłowe wyjście) algorytmów rozwiązywania labiryntów między sobą za pomocą wykresów.

## Lista technologii:

- C/C++
- Python
    - Matplotlib (generowanie wykresów)
- Java
    - Java2D (grafika)

## Format zapisywania labiryntów

Dla wszystkich algorytmów labirynt zapisywany jest w postaci macierzy o wymiarach *m x n*.

Macierz reprezentująca labirynt (generowana przez: *maze_generator.c*) zapisywana jest według następującej zasady:

w *m* wierszach, znajduje sie *n* znaków oddzielonych *spacją*, gdzie:

*1* reprezentuje zajęte pole ("scianę"),\
a *0* reprezentuje pole puste.

Wejścia i wyjścia:

Wejście (*s*) zawsze jest w lewym górnym rogu labiryntu, a wyjście (*e*) zawsze w prawym dolnym rogu labirytnu.

Przykładowa macierz:

```
1 1 1 1 1 1 1 1
1 0 1 0 0 0 0 1
1 0 1 0 1 1 1 1
1 0 0 0 1 0 0 1
1 1 0 1 1 0 0 1
1 0 0 0 0 0 0 1
1 1 1 1 1 1 1 1
```

będzie odpowiadać następującemu labiryntowi:

```
┌─┬────┐ 
│s│    │
│ │ ┌──┤
│   │  │
├─ ─┘  │
│     e│
└──────┘ 
```

gdzie:\
*s* - wejście (start),\
*e* - wyjście (exit).