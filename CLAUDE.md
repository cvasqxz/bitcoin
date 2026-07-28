# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is a Bitcoin Core fork called "Chaucha" - a cryptocurrency implementation based on Bitcoin Core 29.x. The codebase has been rebranded from Bitcoin to Chaucha throughout, including binary names, configuration directories, and user agent strings.

## Build System and Common Commands

This project uses CMake as its primary build system:

### Building the Project
```bash
# Configure build with default options
cmake -B build

# Build all targets (use -j N for N parallel jobs)
cmake --build build

# Install (optional)
cmake --install build
```

### Build Options
Key CMake configuration options:
- `-DBUILD_GUI=ON/OFF` - Build chaucha-qt GUI (default: OFF)
- `-DBUILD_DAEMON=ON/OFF` - Build chauchad daemon (default: ON)
- `-DBUILD_CLI=ON/OFF` - Build chaucha-cli (default: ON)
- `-DBUILD_TESTS=ON/OFF` - Build test_chaucha (default: ON)
- `-DBUILD_BENCH=ON/OFF` - Build bench_chaucha (default: OFF)
- `-DENABLE_WALLET=ON/OFF` - Enable wallet functionality (default: ON)
- `-DWITH_ZMQ=ON/OFF` - Enable ZeroMQ notifications (default: OFF)
- `-DWITH_SQLITE=ON/OFF` - Enable SQLite wallet support (default: ON if wallet enabled)
- `-DWITH_BDB=ON/OFF` - Enable Berkeley DB wallet support (default: OFF)

### Testing
```bash
# Run all unit tests
ctest --test-dir build

# Run specific unit test executable
build/bin/test_chaucha

# Run functional tests
build/test/functional/test_runner.py

# Run individual functional test
build/test/functional/feature_rbf.py
```

### Development Commands
```bash
# Build only what's needed for unit tests after changes
cmake --build build --target test_chaucha

# Clean build
rm -rf build && cmake -B build && cmake --build build
```

## High-Level Architecture

### Core Components

**Consensus Layer** (`src/consensus/`):
- Transaction and block validation rules
- Merkle tree implementations
- Amount handling and consensus parameters

**Network Layer** (`src/net*`, `src/p2p*`):
- Peer-to-peer communication
- Network message handling
- Connection management and peer selection
- Address management (`addrman.cpp`)

**Chain Management** (`src/chain.*`, `src/validation.*`):
- Blockchain state management
- Block storage and retrieval
- UTXO set management via `CCoinsView`
- Chain tip management and reorganization handling

**Wallet** (`src/wallet/`):
- Descriptor and legacy wallet implementations
- Transaction creation and signing
- Key management and derivation
- Coin selection algorithms

**RPC Interface** (`src/rpc/`):
- JSON-RPC server implementation
- Blockchain, wallet, network, and mining RPC methods
- Request handling and authentication

**GUI** (`src/qt/`):
- Qt-based desktop application
- Wallet interface and transaction management
- Network monitoring and configuration

### Key Architectural Patterns

**Node Architecture**:
- `ChainstateManager` manages multiple chainstates (main, snapshot, IBD)
- `CTxMemPool` handles transaction pool with policy validation
- `PeerManager` coordinates P2P protocol logic
- `CConnman` manages network connections

**Threading Model**:
- Main thread handles validation and consensus
- Network thread manages P2P connections
- Separate threads for RPC, GUI, and background tasks
- Extensive use of mutexes and thread-safe data structures

**Storage**:
- LevelDB for blockchain data and UTXO set
- Berkeley DB or SQLite for wallet storage
- Custom serialization framework throughout

## Project-Specific Considerations

### Chaucha Modifications
- All binary names use "chaucha" prefix instead of "bitcoin"
- Configuration directory changed from `.bitcoin` to `.chaucha`
- User agent string shows "Chauchera" instead of "Satoshi"
- Network protocol and consensus rules may differ from Bitcoin
- This is on branch `29.x`, with `master` as the main development branch

### Testing Framework
- Unit tests use Boost.Test framework (`src/test/`)
- Functional tests use Python framework (`test/functional/`)
- Fuzz testing available (`src/test/fuzz/`)
- Benchmark suite available (`src/bench/`)

### Dependencies
The project relies on several key external libraries managed through CMake:
- secp256k1 for cryptographic operations (built as subtree)
- LevelDB for database storage (built as subtree)
- libevent for network event handling
- Boost for various utilities (conditionally)
- Qt5 for GUI (optional)

### Code Organization
- Core consensus code is isolated in `src/consensus/` and `src/script/`
- Kernel library (`src/kernel/`) provides consensus-only interface
- Common utilities in `src/util/` and `src/common/`
- Platform-specific code isolated in `src/compat/`
- Test utilities in `src/test/util/`