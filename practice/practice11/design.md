# Carter's Board Game Café Program!

## 1. Specification
This program is a lightweight way for the owner of this local board game café to do the following: 
- Maintain a catalog of board games, including the number of available copies.
- Track which customers have borrowed which games.
- Record when games are returned.

The program involves four main classes: `Game`, `Customer`, `LendingRecord`, and `Catalog`. It lets the user list, add, and remove games, see which customers are borrowing the game, and track when the game is due and returned.

---

## 2. Nouns and Verbs

### Key Nouns
- **Game**: Represents a board game in the catalog.
- **Customer**: Represents a person borrowing a game.
- **Lending Record**: Tracks which customer has borrowed which game and its due date.
- **Catalog**: Represents the collection of all games in the café.
- **Due Date**: When a game is set to be returned
- **Overdue Games**: Games that have not been returned by their due date.
- **Borrowing History**: Record of past borrowings by a customer


### Key Verbs
- **List Games**: Display all games and their availability.
- **Check Out Game**: Assign a game to a customer.
- **Return Game**: Mark a game as returned.
- **Add Game**: Adds a new game to the catalog
- **Remove Game**: Removes a game from the catalog
- **Check Overdue Games**: Identify games that are overdue.
- **Borrowing History: A record of all past borrowings by a customer.

---

## 3. Class Design

### Class: `Game`
```cpp
class Game {
public:
    std::string title;
    int totalCopies;
    int availableCopies;

    Game(std::string title, int totalCopies);
    void updateAvailability(int change);
};
```

### Class: `Customer`
```cpp
class Customer {
public:
    std::string name;
    int customerId;

    Customer(std::string name, int customerId);
};
```

### Class: `LendingRecord`
```cpp
class LendingRecord {
public:
    int recordId;
    int customerId;
    std::string gameTitle;
    std::string dueDate;

    LendingRecord(int recordId, int customerId, std::string gameTitle, std::string dueDate);
    void markReturned();
};
```

---

## 4. Class Diagram

```mermaid
classDiagram
    class Game {
        +std::string title
        +int totalCopies
        +int availableCopies
        +Game(std::string title, int totalCopies)
        +void updateAvailability(int change)
    }

    class Customer {
        +std::string name
        +int customerId
        +std::vector<std::string> borrowedGames
        +Customer(std::string name, int customerId)
        +void viewBorrowingHistory()
    }

    class LendingRecord {
        +int recordId
        +int customerId
        +std::string gameTitle
        +std::string dueDate
        +LendingRecord(int recordId, int customerId, std::string gameTitle, std::string dueDate)
        +void markReturned()
        +bool isOverdue()
    }

    class Catalog {
        +std::vector<Game> games
        +void addGame(Game game)
        +void removeGame(std::string title)
        +Game searchGame(std::string title)
    }

    Game "1" --> "0..*" LendingRecord : "is borrowed in"
    Customer "1" --> "0..*" LendingRecord : "creates"
    Catalog "1" --> "0..*" Game : "manages"