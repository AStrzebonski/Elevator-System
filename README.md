Aleksander Strzeboński
# Elevator-System - Dokumentacja
## Opis programu
Program pozwala zarządzać i symulować działanie systemu wind w budynku. Windy zarządzane są wedle poniższego algorytmu. Program napisany został w języku C.
## Opis algorytmu
### 1. Algorytm działania windy:
Winda zna numery pięter, na których ma się zatrzymać. Winda porusza się zgodnie ze swoim kierunkiem, zatrzymując się na każdym piętrze na którym ma się zatrzymać i wykreślając to piętro z listy pięter, na których winda ma się zatrzymać, aż do momentu, gdy nie ma już takiego piętra na liście, do którego dałoby się dotrzeć bez zmiany kierunku. Wtedy winda zmienia kierunek na przeciwny i algorytm rozpoczyna się od nowa. Jeżeli winda obsłuży wszystkie przywołania, zatrzymuje się. Przykład: winda jest na drugim piętrze i zmierza na trzecie piętro, ale na liście przywołań ma również piętro pierwsze. Na drugim piętrze wsiada osoba i naciska przycisk z piętrem piątym. Winda obsłuży kolejno piętra trzecie, piąte i na końcu pierwsze, gdyż jadąc w górę, winda obsłuży najpierw wszystkie przywołania ponad nią. Oczywiście, w drodze z piątego piętra na pierwsze może się zdarzyć przywołanie, na przykład, na piętrze drugim, które winda obsłuży. Nie może się natomiast zdarzyć sytuacja, gdy winda jadąc z piątego piętra na pierwsze pojedzie do góry, zanim dotrze do piętra pierwszego.
### 2. Algorytm obsługi przywołań spoza windy, czyli przywołań poprzez kliknięcie przycisku na piętrze:
Gdy zostanie naciśnięty przycisk algorytm decyzyjny przydziela żądanie odpowiedniej windzie. Algorytm oblicza najdłuższą możliwą ścieżkę po której winda dotarłaby do danego piętra z odpowiednim kierunkiem. Przykład: winda jest na drugim piętrze i jedzie do góry. Na czwartym piętrze winda została wezwana przyciskiem w dół. W najgorszym możliwym przypadku winda, zanim zacznie jechać z trzeciego piętra w dół, będzie musiała dojechać do samej góry i wrócić stamtąd z powrotem na czwarte piętro, czyli gdy liczba pięter to dziesięć, najdłuższa możliwa ścieżka wyniesie 14 (8 w górę i 6 w dół). Jeżeli winda stoi, to zakładamy, że najdłuższą możliwą trasą jest różnica pięter. Obliczona dla każdej windy najdłuższa ścieżka posłuży jako składnik funkcji kosztu. Dodatkowo, jeżeli wiadomo, że winda ma w planach zmianę kierunku (na przykład jedzie w górę, ale ma wezwanie do piętra będącego pod nią, lub winda jedzie w górę ale do osoby, która kliknęła, że chce jechać w dół) do funkcji kosztu dodajemy dwukrotność liczby pięter w budynku. Dzieje się tak, gdyż nie chcemy, aby osoba która czeka na windę, która się oddala musiała czekać jeszcze dłużej, bo winda przyjmowałaby kolejne zgłoszenia. Nie chcemy też, aby winda jadąca do danej osoby, która chce jechać w dół przyjmowała zgłoszenia do pięter powyżej tej osoby. Po obliczeniu funkcji kosztu, czyli zsumowaniu najdłuższej drogi i ewentualnie powyższej wartości, wybierana jest winda o najmniejszej funkcji kosztu, której przydzielane jest żądanie.
## Opis struktury Elevator
Jest to struktura, która przechowuje informacje o jednej windzie. Posiada ona pola:
 * ID - numer identyfikacyjny windy,
 * floor - numer piętra, na którym znajduje się winda; piętra numeruje się od zera,
 * dest_floor - tablica zmiennych typu bool; wartość 'true' oznacza, że piętro o danym indeksie znajduje się na liście żądań windy,
 * direction - wartość całkowita określająca kierunek poruszania się windy (dodatnia - w górę, ujemna - w dół, zero - winda stoi w miejscu)
 * change_direction_soon - wartość całkowita określająca czy, i w jaką stronę oczekuje się, że winda zmieni kierunek poruszania się (dodatnia - w górę, ujemna - w dół, zero - nie oczekuje się, że winda zmieni kierunek)
 * stop_and_open - zmienna typu bool; wartość 'true' oznacza, że winda stoi z otwartymi drzwiami na danym piętrze (Nie oznacza to, że direction ma wartość zero. Winda jest w tym stanie tylko chwilowo)
## Pliki
Program składa się z pliku głównego _main.c_ oraz pliku _ElevatorSystem.c_ z implementacją funkcji pozwalających zarządzać windą i jego pliku nagłówkowego _ElevatorSystem.h_
## Instrukcja użytkownika
Po skompilowaniu kodu i uruchomieniu programu, otwiera się konsola, w której można wywoływać funkcje określające działanie windy. Poprzez wpisywanie odpowiednich poleceń, odpowiednie funkcje są wywoływane. Na ekranie wświetla się informacja o dostępnych opcjach i jak ich użyć. Funkcje są zabezpieczone od wywołania z niepożądanymi wartościami z poziomu pliku _ElevatorSystem.c_. Należy jednak pamiętać, że do konwersji danych przesyłanych przez użytkownika na zmienną typu integer została użyta funkcja atoi(), co oznacza, że wpisanie nie-integera poskutkuje konwersją na 0 i to 0 będzie przekazane do funkcji.
### Funkcje dostępne dla użytkownika
#### Funkcje zarządzające
* Elevator_Clear_Demands(int ID) - (komenda 'clear') czyści listę żądań windy o podanym ID.
* Elevator_Change_Status(int ID, int new_ID, int floor, int direction, bool stop_and_open) - (komenda 'change') ustawia część parametrów windy.
* print_status() - (komenda 'status') wyświetla informacje o stanie wszysktich wind zwracaną przez funkcję Elevator_Status().
#### Funkcje odzwierciedlające normalną pracę windy
* Elevator_Pickup(int floor, int direction) - (komenda 'pickup') ekwiwalent wciśnięcia przycisku o kierunku zgodnym ze znakiem zmiennej _direction_ na piętrze o numerze _floor_. Funkcja ta przyjmuje żądanie i przydziela je odpowiedniej windzie.
* Elevator_Demand(int ID, int dest_floor) - (komenda 'demand') ekwiwalent wciśnięcia przycisku o numerze _dest_floor_ w windzie o podanym ID. Funkcja ta dodatkowo zamyka drzwi windy jeżeli są otwarte.
* Elevator_Step() - (komenda 'step') symulacja upływu czasu. Dla każdej windy, jeżeli drzwi windy są otwarte, to funkcja ta je zamyka. Jeżeli drzwi są zamknięte i winda ma niezerowy kierunek ruchu, to funkcja przemieszcza windę o jedno piętro. Można wywołać ją dowolną ilość razy.
## Dodatkowe funkcje i własności 
W pliku nagłówkowym _ElevatorSystem.h_ zdefiniowane są makra:
 * ELEV_NB - określa liczbę wind w budynku. Obecnie ustawione jest na 16, ale można je zmieniać, z zachowaniem rozsądku, w dowolny sposób.
 * FLOOR_NB - określa liczbę pięter. Również można zmieniać w dowolny sposób.
 ### Istotne funkcje używane w programie
 * Longest_Path(int current_floor, int demanded_floor, int current_direction, int demanded_direction) - określa najdłuższą możliwą drogę windy do wezwania oraz czy winda będzie musiała zmienić kierunek po przybyciu do wezwania lub w trakcie drogi do wezwania.
 * Refresh() - odświeża stan windy, w szczególności, wykreśla obsłużone piętra z listy żądań, otwiera drzwi, zmienia kierunek poruszania się windy.
 ## Komentarz
 Problem jest dosyć złożony i z pewnością dałoby się stworzyć bardziej zaawansowany i lepszy algorytm. Algorytm wymyśliłem sam, nie chciałem posiłkować się gotowymi rozwiązaniami. Program dałoby się przenieść na platformę embedded. Oczywiście należałoby wtedy zmienić sposób wywołania funkcji z pliku ElevatorSystem.c oraz dopisać coś co przekazywałoby zmiany w strukturze _Elevator_ do układów peryferyjnych.
