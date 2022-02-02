## **1. Opis projektu.**

Gra multiplayer „kółko i krzyżyk” w oparciu o technologię
blockchain

## **2. Wymagania**

1. Mechanika gry zawarta w Smart contractach (solidity)
2. Smart kontrakt wystawiony na „Rinkbey testnet” lub inny
   testnet
3. Graficzny klient gry (c++)
4. System zapytań do sieci Rinkbey poprzez ws JSON RPC
5. Ekran tworzenia gry
6. Ekran dołączania do gry
7. Ekran gry
8. Ekran rezultatu gry

## **3. Przebieg realizacji**

1. Stworzenie logiki gry zawartej w Smart kontrakcie.

   Funkcjonalności:

   - Tworzenie nowej gry
   - Dołączanie do istniejącej gry
   - Rozpoczynanie gry po dołączeniu obu graczy
   - Reagowanie na ruchy graczy
   - Zapisywanie informacji o wygranym

2. Smart Kontrakt wystawiony na sieć Rinkbey pod adresem
   bloku:
   **0x0cEB962a0160bcF2C9F6a8cD2a7F285419b8c**

3. Graficzny klient gry stworzony jest przy pomocy biblioteki
   **SFML.** Biblioteka ta służy do wyświetlania aplikacji w postaci
   okienkowej i pozwala na renderowanie prostych grafik.

## **4. Instrukcja użytkownika**

Po uruchomieniu aplikacji użytkownikowi ukaże się ekran
tworzenia gry wraz z listą zasad jakie w niej obowiązują.

![Create page](https://github.com/SMasiu/blockchain_tic_tac_toe/blob/main/docs/images/create_page.png?raw=true)

Po kliknięci przyciska „Start game” użytkownik zostanie przekierowany na strone
z grą.

![Game page](https://github.com/SMasiu/blockchain_tic_tac_toe/blob/main/docs/images/game_page.png?raw=true)

W lewym górnym rogu użytkownik może zobaczyć jaka figura
odpowiada któremu graczowi. Na środku widać czyja jest teraz
tura. Użytkownik ma możliwość kliknięcia w 1 z 9 kafelków aby
umieścić tam swoją figurę jeśli ten nie będzie wcześniej zajęty.

![Game in progress page](https://github.com/SMasiu/blockchain_tic_tac_toe/blob/main/docs/images/game_in_proggres_page.png?raw=true)

Po kliknięciu na danym kafelku ukaże się figura gracza który ją
kliknął. Gdy jeden z graczy zdoła umieścić 3 swoje figury w
pionie, poziomie albo po skosie wygrywa on grę oraz pokazuje
się ekran rezultatu gry.

Pokaże się on również gdy planszą będzie pełna i żaden z
graczy nie wygra.

![Game result](https://github.com/SMasiu/blockchain_tic_tac_toe/blob/main/docs/images/result_page.png?raw=true)

Na ekranie rezultatu gry użytkownik może zobaczyć kto wygrał.
Oraz jaki jest ogólny wynik z wszystkich odbytych dotychczas
gier. Wynik gracza z większą ilością wygranych gier będzie
wyświetlony na zielono natomiast gracza z mniejszą ilością
będzie czerwony. W przypadku remisu oba mają kolor biały.

Pod wynikami jest przycisk po kliknięciu którego gra rozpocznie
się na nowo.

## **5. Podsumowanie i wnioski.**

Część graficzna oraz część blockchainowa zostały
zrealizowanie, jednakże te części nie zostały połączone ze sobą.

Podczas pisania części graficznej wynikł problem z
podłączeniem do blockchaina gdyż c++ nie posiadał żadnych
bibliotek ułatwiających komunikację pomiędzy blockchainem.

Wnioski płynące z tego są takie że w różnych technologiach
czas wykonania tego samego zadania może się bardzo różnić
zwłaszcza w przypadku nowych technologii.
