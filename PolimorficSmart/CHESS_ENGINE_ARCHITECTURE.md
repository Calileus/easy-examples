# ♟️ Chess Engine Architecture Specification

## Project Overview

This document outlines the modular design for a chess engine based on the Separation of Concerns (SoC) principle. The system is divided into five core modules to ensure high maintainability, testability, and scalability.

## Current Repository Analysis

### Existing Codebase Structure
The current repository contains a comprehensive C++ financial instruments example with:
- **Polymorphic Design**: Abstract base class with derived implementations
- **Smart Pointer Usage**: `unique_ptr`, `shared_ptr`, `weak_ptr`
- **Threading Support**: Thread-safe operations and concurrent processing
- **Testing Framework**: Unit tests and integration tests
- **Build System**: CMake configuration with multiple targets

### Architectural Patterns Already Demonstrated
- **Factory Pattern**: Object creation without exposing concrete types
- **Observer Pattern**: Market data feed with subscriber notifications
- **RAII**: Automatic resource management
- **SOLID Principles**: Single responsibility, open/closed, Liskov substitution

## Chess Engine Architecture

### 1. CCI: Chess Common Interface
**Role**: The "Common Language." This module contains only data structures and definitions. It is a passive layer included by all other modules to ensure data consistency.

#### Key Structures:

```cpp
namespace Chess {
    // Board representation
    struct Grid {
        std::array<std::array<Piece, 8>, 8> board;
        Color current_turn;
        GameFlags flags;
    };
    
    // Piece properties
    struct PieceProperties {
        PieceType type;
        Color color;
        Position position;
        bool has_moved;
        bool en_passant_vulnerable;
    };
    
    // Move representation
    struct Move {
        Position start_pos;
        Position end_pos;
        SpecialFlags flags;
        PieceType promotion_piece;
    };
    
    // Position representation
    struct Position {
        int file;  // 0-7 (a-h)
        int rank;  // 0-7 (1-8)
    };
    
    // Enums
    enum class PieceType { PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING };
    enum class Color { WHITE, BLACK };
    enum class SpecialFlags { NONE, CASTLE_KINGSIDE, CASTLE_QUEENSIDE, EN_PASSANT, PROMOTION };
}
```

**Design Note**: Piece types are handled via grid representation and polymorphism to allow for clean logic in the CPL.

### 2. CBM: Chess Board Manager
**Role**: The "Referee." This module manages the global state of the board and enforces the higher-level rules of Chess.

#### Responsibilities:
- Manages the current game board and a secondary "Validation Grid" for "what-if" scenarios
- Verifies move legality by checking if a move leaves the King in check
- Detects end-game states (Checkmate, Stalemate, Material Draw)

#### Required Interface:

```cpp
class ChessBoardManager {
public:
    bool is_white_king_in_check(const Grid& grid) const;
    bool is_black_king_in_check(const Grid& grid) const;
    bool is_draw(const Grid& grid, Color color_turn) const;
    bool validate_move(const Grid& grid, const Move& move) const;
    bool is_checkmate(const Grid& grid, Color color) const;
    bool is_stalemate(const Grid& grid, Color color) const;
    
private:
    Grid current_board_;
    Grid validation_grid_;
};
```

### 3. CPL: Chess Pieces Logic
**Role**: The "Physicist." This module handles how individual pieces move in a vacuum, ignoring the "Check" rule.

#### Responsibilities:
- Calculates "Raw Logical Moves" based on piece geometry and board occupancy
- Identifies if a square is reachable by a specific piece

#### Required Interface:

```cpp
class ChessPiecesLogic {
public:
    bool is_raw_logical_move(const Grid& grid, const Move& move) const;
    std::vector<Move> list_raw_logical_moves(const Grid& grid, Position position) const;
    bool is_square_attacked(const Grid& grid, Position square, Color by_color) const;
    
private:
    std::vector<Move> get_pawn_moves(const Grid& grid, Position pos) const;
    std::vector<Move> get_knight_moves(const Grid& grid, Position pos) const;
    std::vector<Move> get_bishop_moves(const Grid& grid, Position pos) const;
    std::vector<Move> get_rook_moves(const Grid& grid, Position pos) const;
    std::vector<Move> get_queen_moves(const Grid& grid, Position pos) const;
    std::vector<Move> get_king_moves(const Grid& grid, Position pos) const;
};
```

### 4. CTU: Chess Translation Unit
**Role**: The "Adapter." This handles the translation of external inputs into the engine's internal language.

#### Responsibilities:
- Converts standard chess notations (like FEN or Algebraic) into internal CCI structures
- Allows the engine to interface with different UIs (CLI, GUI) or external AI engines

#### Required Interface:

```cpp
class ChessTranslationUnit {
public:
    Grid fen_to_internal(const std::string& fen_string) const;
    std::string internal_to_fen(const Grid& grid) const;
    Move algebraic_to_move(const std::string& algebraic, const Grid& grid) const;
    std::string move_to_algebraic(const Move& move, const Grid& grid) const;
    
private:
    PieceType char_to_piece_type(char c) const;
    Color char_to_color(char c) const;
    Position algebraic_to_position(const std::string& pos) const;
};
```

### 5. CGH: Chess Game Handler
**Role**: The "Orchestrator." The entry point of the application that manages the lifecycle of a game session.

#### Responsibilities:
- Instantiates all necessary modules
- Manages game metadata: Unique Game IDs, move logs (History), and turn management
- Time Control: Tracks player clocks and handles timeouts

#### Required Interface:

```cpp
class ChessGameHandler {
public:
    void start_new_game();
    void load_game_from_fen(const std::string& fen);
    bool make_move(const std::string& algebraic_move);
    bool make_move(const Move& move);
    std::string get_current_fen() const;
    std::vector<Move> get_legal_moves() const;
    GameState get_game_state() const;
    
    // Time control
    void start_timer(Color color);
    void stop_timer(Color color);
    std::chrono::milliseconds get_time_remaining(Color color) const;
    
private:
    std::unique_ptr<ChessBoardManager> board_manager_;
    std::unique_ptr<ChessPiecesLogic> pieces_logic_;
    std::unique_ptr<ChessTranslationUnit> translation_unit_;
    
    Grid current_grid_;
    std::vector<Move> move_history_;
    std::chrono::milliseconds white_time_;
    std::chrono::milliseconds black_time_;
    std::string game_id_;
};
```

## Migration Plan from Current Repository

### Phase 1: Foundation Setup (Week 1-2)

#### 1.1 Repository Restructuring
```
ChessEngine/
├── include/
│   ├── cci/           # Chess Common Interface
│   │   ├── chess_types.h
│   │   ├── grid.h
│   │   ├── move.h
│   │   └── position.h
│   ├── cbm/           # Chess Board Manager
│   │   └── board_manager.h
│   ├── cpl/           # Chess Pieces Logic
│   │   └── pieces_logic.h
│   ├── ctu/           # Chess Translation Unit
│   │   └── translation_unit.h
│   └── cgh/           # Chess Game Handler
│       └── game_handler.h
├── src/
│   ├── cci/
│   ├── cbm/
│   ├── cpl/
│   ├── ctu/
│   └── cgh/
├── tests/
│   ├── unit/
│   ├── integration/
│   └── performance/
├── examples/
├── CMakeLists.txt
└── README.md
```

#### 1.2 Leverage Existing Patterns
- **Adapt Financial Instrument Polymorphism**: Use the same abstract base class pattern for chess pieces
- **Reuse Smart Pointer Patterns**: Apply `unique_ptr` for ownership, `shared_ptr` for shared state
- **Adapt Threading Infrastructure**: Use existing thread-safe patterns for concurrent move generation
- **Migrate Testing Framework**: Adapt current test structure for chess-specific tests

#### 1.3 CCI Implementation
```cpp
// Adapt from financial_instrument.h pattern
class Piece {
public:
    virtual ~Piece() = default;
    virtual std::vector<Move> get_possible_moves(const Grid& grid) const = 0;
    virtual PieceType get_type() const = 0;
    virtual Color get_color() const = 0;
    
protected:
    Position position_;
    Color color_;
    bool has_moved_;
};
```

### Phase 2: Core Logic Development (Week 3-4)

#### 2.1 CPL Implementation
- **Adapt Thread-Safe Patterns**: Use existing `ThreadSafeLogger` and mutex patterns
- **Apply Factory Pattern**: Create piece factory similar to `createInstrument()`
- **Implement Move Generation**: Use vector operations and algorithms from current codebase

#### 2.2 CBM Implementation
- **Validation Grid**: Use dual-grid pattern similar to market simulation
- **Rule Enforcement**: Apply state management patterns from portfolio tracking
- **End-Game Detection**: Implement using existing atomic and threading patterns

#### 2.3 CTU Implementation
- **String Processing**: Leverage existing parsing and validation patterns
- **Format Conversion**: Use existing serialization concepts
- **Error Handling**: Apply exception safety patterns from current codebase

### Phase 3: Integration and Testing (Week 5-6)

#### 3.1 CGH Implementation
- **Module Orchestration**: Use existing market simulation orchestration patterns
- **Game State Management**: Apply portfolio management patterns
- **Time Control**: Use existing timing and synchronization patterns

#### 3.2 Testing Strategy
```cpp
// Adapt existing test framework
class ChessTests : public ::testing::Test {
protected:
    void SetUp() override {
        board_manager = std::make_unique<ChessBoardManager>();
        pieces_logic = std::make_unique<ChessPiecesLogic>();
        translation_unit = std::make_unique<ChessTranslationUnit>();
    }
    
    std::unique_ptr<ChessBoardManager> board_manager;
    std::unique_ptr<ChessPiecesLogic> pieces_logic;
    std::unique_ptr<ChessTranslationUnit> translation_unit;
};
```

#### 3.3 Performance Testing
- **Move Generation Benchmarks**: Use existing timing patterns
- **Memory Usage**: Apply existing memory management patterns
- **Concurrent Testing**: Leverage existing threading test infrastructure

### Phase 4: Advanced Features (Week 7-8)

#### 4.1 AI Integration
- **Engine Interface**: Use existing async operation patterns
- **Move Evaluation**: Apply portfolio calculation patterns
- **Search Algorithms**: Use existing recursive and iterative patterns

#### 4.2 GUI/Web Interface
- **Event System**: Use existing observer patterns from market data feed
- **State Synchronization**: Apply existing thread-safe update patterns
- **Protocol Handling**: Use existing translation and adapter patterns

#### 4.3 Performance Optimization
- **Cache-Friendly Data Structures**: Apply existing memory layout patterns
- **SIMD Operations**: Use existing vectorization concepts
- **Parallel Processing**: Leverage existing threading infrastructure

## Code Reuse Opportunities

### 1. Smart Pointer Patterns
```cpp
// Current: Financial instruments
std::shared_ptr<FinancialInstrument> instrument = std::make_shared<Stock>("AAPL", 150.0, 100);

// Chess: Game pieces
std::shared_ptr<Piece> piece = std::make_unique<Pawn>(Position(4, 4), Color::WHITE);
```

### 2. Thread-Safe Operations
```cpp
// Current: Thread-safe portfolio
class ThreadSafePortfolio {
    mutable std::mutex mutex_;
    std::vector<std::shared_ptr<FinancialInstrument>> instruments_;
};

// Chess: Thread-safe board
class ThreadSafeBoard {
    mutable std::shared_mutex mutex_;
    Grid current_position_;
    std::vector<Move> move_history_;
};
```

### 3. Factory Pattern
```cpp
// Current: Instrument factory
std::unique_ptr<FinancialInstrument> createInstrument(const std::string& type, ...);

// Chess: Piece factory
std::unique_ptr<Piece> createPiece(PieceType type, Position pos, Color color);
```

### 4. Observer Pattern
```cpp
// Current: Market data feed
class MarketDataFeed {
    std::vector<std::weak_ptr<ThreadSafePortfolio>> subscribers_;
};

// Chess: Game event system
class GameEventNotifier {
    std::vector<std::weak_ptr<GameObserver>> observers_;
};
```

## Implementation Priorities

### High Priority (Core Functionality)
1. **CCI Data Structures** - Foundation for all modules
2. **CPL Move Generation** - Core chess logic
3. **CBM Rule Enforcement** - Game legality
4. **Basic CGH** - Game orchestration

### Medium Priority (Usability)
1. **CTU Translation** - External interface
2. **Testing Framework** - Quality assurance
3. **Basic AI** - Computer opponent
4. **CLI Interface** - User interaction

### Low Priority (Advanced Features)
1. **GUI Interface** - Visual representation
2. **Web API** - Remote access
3. **Advanced AI** - Strong engine
4. **Performance Optimization** - Speed improvements

## Success Metrics

### Technical Metrics
- **Code Coverage**: >90% for core modules
- **Performance**: <1ms per move generation
- **Memory Usage**: <100MB for full game
- **Thread Safety**: Zero race conditions in testing

### Functional Metrics
- **Rule Compliance**: 100% FIDE rule accuracy
- **Move Validation**: 100% legal move detection
- **End-Game Detection**: Accurate checkmate/stalemate detection
- **Translation Accuracy**: 100% FEN/Algebraic conversion

### Architectural Metrics
- **Modularity**: Clear separation of concerns
- **Testability**: All modules independently testable
- **Extensibility**: Easy to add new features
- **Maintainability**: Clear code organization and documentation

## Conclusion

This chess engine architecture leverages the existing repository's strong foundation in modern C++ patterns, smart pointer usage, and thread-safe operations. The migration plan provides a clear path from the current financial instruments example to a fully functional chess engine while maintaining code quality and architectural integrity.

The modular design ensures that each component can be developed, tested, and optimized independently, making the project manageable and scalable. The reuse of existing patterns and infrastructure accelerates development while maintaining the high standards demonstrated in the current codebase.
