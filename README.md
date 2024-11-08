# Website Blocker

This project is a simple C++ program that modifies the system `hosts` file to block or unblock specified websites. 
It redirects specified domains to `127.0.0.1` (localhost), effectively blocking access to those sites from the device.

> **Note**: This program requires administrator/root privileges to modify the system's `hosts` file.

## Features
- Block specific websites by redirecting them to localhost.
- Unblock websites by removing entries from the `hosts` file.
- Cross-platform support for Windows and Linux systems.

## Requirements
- C++ Compiler (such as **g++**)
- Administrator/root privileges to modify the `hosts` file.

## How to Compile and Run

### 1. Clone the Repository
```bash
git clone https://github.com/abua0020/website-blocker.git
cd website-blocker
