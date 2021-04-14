Aleksander Strzeboński
# Elevator-System - Dokumentacja
## Opis programu
Program pozwala zarządzać i symulować działanie systemu wind w budynku. Windy zarządzane są wedle poniższego algorytmu. Program napisany został w języku C.
## Opis algorytmu
### 1. Algorytm działania windy:
Winda zna numery pięter, na których ma się zatrzymać. Winda porusza się zgodnie ze swoim kierunkiem, zatrzymując się na każdym piętrze na którym ma się zatrzymać i wykreślając to piętro z listy pięter, na których winda ma się zatrzymać, aż do momentu, gdy nie ma już takiego piętra na liście, do którego dałoby się dotrzeć bez zmiany kierunku. Wtedy winda zmienia kierunek na przeciwny i algorytm rozpoczyna się od nowa. Jeżeli winda obsłuży wszystkie przywołania, zatrzymuje się. Przykład: winda jest na drugim piętrze i zmierza na trzecie piętro, ale na liście przywołań ma również piętro pierwsze. Na drugim piętrze wsiada osoba i naciska przycisk z piętrem piątym. Winda obsłuży kolejno piętra trzecie, piąte i na końcu pierwsze, gdyż jadąc w górę, winda obsłuży najpierw wszystkie przywołania ponad nią. Oczywiście, w drodze z piątego piętra na pierwsze może się zdarzyć przywołanie, na przykład, na piętrze drugim, które winda obsłuży. Nie może się natomiast zdarzyć sytuacja, gdy winda jadąc z piątego piętra na pierwsze pojedzie do góry, zanim dotrze do piętra pierwszego.
### 2. Algorytm obsługi przywołań spoza windy, czyli przywołań poprzez kliknięcie przycisku na piętrze:
Gdy zostanie naciśnięty przycisk algorytm decyzyjny przydziela żądanie odpowiedniej windzie. Algorytm oblicza najdłuższą możliwą ścieżkę po której winda dotarłaby do danego piętra z odpowiednim kierunkiem. Przykład: winda jest na drugim piętrze i jedzie do góry. Na czwartym piętrze winda została wezwana przyciskiem w dół. W najgorszym możliwym przypadku winda, zanim zacznie jechać z trzeciego piętra w dół, będzie musiała dojechać do samej góry i wrócić stamtąd spowrotem na czwarte piętro, czyli gdy liczba pięter to dziesięc najdłuższa możliwa ścieżka wyniesie 14 (8 w górę i 6 w dół). Jeżeli winda stoi, to zakładamy, że najdłuższą możliwą trasą jest różnica pięter. Obliczona dla każdej windy najdłuższa ścieżka posłuży jako składnik funkcji kosztu. Dodatkowo, jeżeli wiadomo, że winda ma w planach zmianę kierunku (na przykład jedzie w górę, ale ma wezwanie do piętra będącego pod nią, lub winda jedzie w górę ale do osoby, która kliknęła, że chce jechać w dół) do funkcji kosztu dodajemy dwukrotność liczby pięter w budynku. Dzieje się tak, gdyż nie chcemy, aby osoba która czeka na windę, która się oddala musiała czekać jeszcze dłużej, bo winda przyjmowałaby kolejne zgłoszenia. Nie chcemy też, aby winda jadąca do danej osoby, która chce jechać w dół przyjmowała zgłoszenia do pięter powyżej tej osoby. Po obliczeniu funkcji kosztu, czyli zsumowaniu najdłuższej drogi i ewentualnie powyższej wartości, wybierana jest winda o najmniejszej funkcji kosztu, której przydzielane jest żądanie.
## Opis struktury Elevator
Jest to struktura, która przechowuje informacje o jednej windzie. Posiada ona pola:
 * ID - numer identyfikacyjny windy,
 * floor - numer piętra, na którym znajduje się winda; piętra numeruje się od zera,
 * dest_floor - tablica zmiennych typu bool; wartość 'true' oznacza, że piętro o danym indeksie znajduje się na liście żądań windy,
## Instrukcja użytkownika
Po uruchomieniu programu otwiera się konsola, w której można wywoływać funkcje określające działanie windy. Poprzez wpisywanie odpowiednich poleceń odpowiednie funkcje są wywoływane. Na ekranie wświetla się informacja o dostępnych opcjach.
### Dostępne funkcje dla użytkownika
#### Elevator_Clear_Demands(int ID) - komenda 'clear'
Czyści listę żądań windy o podanym ID
#### Elevator_Change_Status(int ID, int new_IP, int floor, 

