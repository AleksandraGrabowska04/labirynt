## Klasa MazeGraph
Jest to reprezentacja grafu nieskierowanego (z zakładaną wagą 1). Wewnętrznie używa listy sąsiadów (adjancency list) z dodatkiem tego, że każdy węzeł ma przypisane opcjonalnie koordynaty, które odwzorowują pozycje na mapie labiryntu. Węzły można pozyskać jako indeksy (zwykły int), z których potem można uzyskać strukturę `MazeGraphNode` przechowującą odpowiednie koordynaty.

- `AddVertex(int x, int y)`
    - Dodaje nowy węzeł do grafu, bez żadnych połączeń. Opcjonalnie można podać koordynaty. **Uwaga:** Duplikaty nie są sprawdzane, co oznacza, że może istnieć wiele węzłów z tymi samymi koordynatami, zostanie to zapewnie niedługo zabronione.
    Zwraca indeks dodanego węzła

- `AddEdge(int x, int y)`
    - Dodaje nową krawędź do grafu między dwoma węzłami, podanymi jako indeksy. Wyrzuca exception jeżeli jakiś węzeł nie istnieje, lub jeżeli identyczna krawędź już istnieje

- `Print()`
    - Wypisuje graph reprezentowany jako lista sąsiadów

- `GetNumVerticies()`
    - Zwraca liczbę węzłów w grafie

- `GetAdjacentNodes(int v)`
    - Przyjmuje indeks węzła jako `v`, i zwraca listę wskaźników do struktury `MazeGraphNode` dla węzłów które są połączone z węzłem `v` (istnieje między nimi krawędź)

- `GetAdjacentNodes(int v)`
    - Zachowanie podobne jak w `GetAdjaventNodes` lecz zwraca listę indeksów węzłów

- `GetGraphNode(int v)`
    - Zwraca wskaźnik do struktury `MazeGraphNode` zależnie od podanego indeksu

- `GetIndexFromCoords(int x, int y)`
    - Zwraca indeks węzła dla którego przypisany są podane koordynaty

- `EdgeExists(int v, int w)`
    - Zwraca True jeżeli istnieje krawędź między podanymi indeksami

## Klasa MazeMap
Jest to reprezentacja mapy labiryntu odpowiednia do tej która jest podana w pliku README, Zakładane jest 1 = true, 0 = false przy interakcji z metodami tej klasy.

- Tworzenie
    - Manualnie w kodzie - Trzeba podać ilość wierszy i kolumn, oraz listę inicjalizującą, z podanymi koordynatami w których mają pojawić się ściany. Przykład:
    
    `MazeMap map(3, 3, {{0, 0}, {0, 1}, {1, 0}});`
    Utworzy taki labirynt
    ```
    1 1 0
    1 0 0
    0 0 0
    ```
    - Wczytując z pliku - Wystarczy przekazać nazwę pliku jako napis, rozmiar nie jest wymagany i jest automatycznie kalkulowany z pliku. Ilość kolumn jest zakładana jedynie na podstawie liczb w pierwszym wierszu, na ten moment **nie ma sprawdzania błędów** i zakładany jest poprawny format!

- `ToMazeGraph(int startPosRow = 1, int startPosCol = 1)`
    - Tworzy i zwraca `MazeGraph` z odpowiednio przypisanymi koordynatami do mapy i odpowiednimi połączeniami takimi jak można by było się spodziewać. W argumentach podana jest pozycja startowa. **Uwaga**: Jeżeli od punktu startowego nie istnieją połączenia do jakiś węzłów, to nie zostaną uwzględnione w grafie!

- `MarkWall(int row, int col)`
    - Ustawia ścianę na wyznaczonej pozycji

- `ClearWall(int row, int col)`
    - Usuwa ścianę na wyznaczonej pozycji

- `Print()`
    
- `Get(int row, int col)`
    - Zwraca true jeżeli na danej pozycji znajduje się ściana.

- `GetFullRow(int row, vector<bool>& out)`
    - Zwraca całą kolumnę jako listę, rezultat jest przekazywany do listy przekazanej w argumencie

- `GetFullCol(int col, vector<bool>& out)`
    - Zwraca cały wiersz, rezultat jest przekazywany do listy przekazanej w argumencie

- `ExportText(const char* filename)`
    - Zapisuje do pliku tekstu podanego w argumencie odwzorowanie mapy

- `ExportBinary(const char* filename)`
    - Zapisuje do pliku binarnego podanego w argumencie odwzorowanie mapy

- `ReadText(const char* filename)`
    - Odczytuje odwzorowanie mapy z pliku tekstowego **Zakładany jest poprawny format**

- `ReadBinary(const char* filename)`
    - Odczytuje odwzorowanie mapy z pliku binarnego **Zakładany jest poprawny format**

- `Clear()`
    - Usuwa wszystkie ściany z labiryntu


## Struktury plików:
### Plik przejścia (lista koordynatów).
Pierwsze 4 bajty: ilośc węzłów zawartych w pliku. Kolejno pary 4 bajtowych wartości, odpowiednio wiersz i kolumna.

### Binarny plik mapy labiryntu
Pierwsza para liczb 4-bajtowych odpowiednio: liczba wierszy oraz kolumn. Kolejno do każdego bajtu pakowane są bity w kolejności little-endian gdzie 1 oznacza ścianę a zero wolne pole, w ten sposób po koleji jest zapisywany każdy wiersz. **Jeżeli wiersz się skończy, to używany jest już następny bajt dla kolejnego wiersza**