# Simple Server-Client Messaging with PQXDH (liboqs) & Signal Protocol (libsignal)

## Overview

This project implements a straightforward server-client architecture for secure message exchange leveraging:

* **PQXDH (Kyber)** key exchange via [liboqs](https://github.com/open-quantum-safe/liboqs) for post-quantum security.
* **Signal Protocol (libsignal)** for encrypted messaging and ratcheting.

The server acts as a relay, forwarding encrypted messages between clients without storing any plaintext.

---

## Features

* Post-quantum secure key exchange with PQXDH (Kyber)
* End-to-end encrypted messaging using Signal Protocol
* Basic multi-client support (via threads or async)
* Simple TCP socket communication
* No persistent storage (stateless relay server)

---

## Prerequisites

* Linux environment (tested on Ubuntu 20.04+)
* `gcc` or `clang` compiler with C11 support
* `liboqs` installed and built ([https://github.com/open-quantum-safe/liboqs](https://github.com/open-quantum-safe/liboqs))
* `libsignal-protocol-c` installed ([https://github.com/signalapp/libsignal-protocol-c](https://github.com/signalapp/libsignal-protocol-c))
* `pthread` library (for multi-threading on the server)

---

## Setup

1. **Clone repositories and build dependencies:**

```bash
# liboqs
git clone https://github.com/open-quantum-safe/liboqs.git
cd liboqs
mkdir build && cd build
cmake ..
make
sudo make install

# libsignal-protocol-c
git clone https://github.com/signalapp/libsignal-protocol-c.git
cd libsignal-protocol-c
mkdir build && cd build
cmake ..
make
sudo make install
```

2. **Build your server and client:**

Assuming you have `server.c` and `client.c` implementing PQXDH + Signal Protocol integration.

```bash
gcc server.c -o server -loqs -lsignal-protocol-c -lpthread
gcc client.c -o client -loqs -lsignal-protocol-c
```

Adjust linker flags if libraries are installed in non-standard paths.

---

## Usage

1. **Start the server:**

```bash
./server
```

Server listens on port 12345 (default, configurable in code).

2. **Start clients in multiple terminals:**

```bash
./client 
```


3. **Key Exchange & Messaging Flow:**

* Clients perform PQXDH key exchange via server relay.
* Shared secret initializes Signal Protocol session.
* Clients send encrypted messages to server tagged with recipient ID.
* Server forwards encrypted messages to target clients.
* Clients decrypt and display messages.

---

## Limitations & Next Steps

* No persistent identity or session storage yet — all volatile.
* Signature verification is currently disabled for simplicity.
* No GUI or advanced error handling.
* Future enhancements:

  * Add identity key management with SQLite or file storage.
  * Implement proper message headers and protocol framing.
  * Support reconnects and offline messaging.
  * Add logging and detailed debugging options.

---

## References

* liboqs: [https://github.com/open-quantum-safe/liboqs](https://github.com/open-quantum-safe/liboqs)
* libsignal-protocol-c: [https://github.com/signalapp/libsignal-protocol-c](https://github.com/signalapp/libsignal-protocol-c)
* PQXDH (Kyber) specs & docs: [https://openquantumsafe.org/liboqs/api/](https://openquantumsafe.org/liboqs/api/)
* Signal Protocol documentation: [https://signal.org/docs/](https://signal.org/docs/)

---

This README is your quick start guide to run and understand the simple PQXDH + Signal Protocol secure messaging demo. Get your hands dirty with the code, and you'll have a future-proof secure messaging baseline.


