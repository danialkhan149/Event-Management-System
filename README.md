# 🎓 University Event Management System (DSA Project)

A console-based University Event Management System built in C++ as a Data Structures Lab project.  
The system efficiently manages events, participants, registrations, and VIP prioritization using multiple data structures.

---

## 📌 Project Overview

This project simulates a real-world university event management system (similar to Nexus-style events).  
It handles:

- Event creation and management
- Participant registration
- VIP priority handling
- Event capacity tracking
- Data persistence using file handling
- Relationship visualization using graphs

---

## 👨‍💻 Developed By

- Hafiz Danial Ahmed Khan
- Muhammad Ali

Purpose: Data Structures & Algorithms Project
---

## 🧠 Data Structures Used

| Data Structure | Purpose |
|----------------|--------|
| Linked List | Custom implementation for Queue & Stack |
| Queue | Pending registrations (FIFO) |
| Priority Queue (Heap) | VIP registrations |
| Stack | Verified registrations & undo feature |
| Binary Search Tree (BST) | Event storage & searching |
| Hash Table | Fast participant lookup by CNIC |
| Graph (Adjacency List) | Event-module relationships |

---

## ⚙️ Features

### 🎟 Event Management
- Add, delete, update, and search events
- Capacity and fee handling

### 👥 Participant System
- Registration with validation
- CNIC-based identification
- Profile management

### ⭐ VIP System
- Priority-based registration using heap
- Higher priority users processed first

### 📊 Analytics & Tracking
- Revenue calculation
- Registration history
- Verified users tracking

### 🌐 Graph Module
- BFS and DFS traversal
- Event-module relationship mapping

### 💾 File Handling
- Persistent storage using text files:
  - `events.txt`
  - `pending.txt`
  - `verified.txt`

---

## 🧩 System Architecture

The system is built using Object-Oriented Programming (OOP) and modular design:

- Event Management Module (BST)
- Registration System (Queue + Heap)
- User Directory (Hash Table)
- Network Visualization (Graph)
- Verification System (Stack)

---

## 📁 Project Structure
```bash
project/
│
├── src/
│   ├── main.cpp
│   ├── EventManagementSystem.cpp
│   ├── Participant.cpp
│   ├── Registration.cpp
│   ├── Event.cpp
│   ├── Graph.cpp
│   ├── HashTable.cpp
│   ├── LinkedQueue.cpp
│   ├── LinkedStack.cpp
│   ├── PriorityQueue.cpp
│   └── EventBST.cpp
│
├── include/
│   ├── EventManagementSystem.h
│   ├── Participant.h
│   ├── Registration.h
│   ├── Event.h
│   ├── Graph.h
│   ├── HashTable.h
│   ├── LinkedQueue.h
│   ├── LinkedStack.h
│   ├── PriorityQueue.h
│   └── EventBST.h
│
├── data/
│   ├── events.txt
│   ├── pending.txt
│   └── verified.txt
│
├── build/
│   └── system.exe
│
├── .gitignore
└── README.md
```
---

## 📦 Requirements

- C++ Compiler (g++ / MinGW / MSVC)
- C++11 or above

---

## ⚙️ How to Compile & Run

### Using g++ (Linux / MinGW)

```bash
g++ src/*.cpp -Iinclude -o system
./system
