# ASCII Shape Manager - Data Structures Assignment

**Course:** Data Structures (Computer Engineering)  
**Author:** Abdullah Sait AVCI  
**Language:** C++ (MinGW)

## 📖 Project Overview
This project is a **C++ Console Application** developed for the Data Structures course at **Sakarya University**. It implements a custom **ASCII rendering engine** using **Nested Linked Lists** to manage and manipulate geometric shapes in a terminal environment.

The core challenge of this assignment was to build a hierarchical data structure without using any standard template libraries (STL), enforcing strict manual memory management and pointer arithmetic.

## 🏗️ Technical Architecture

### 1. Data Structures (Nested Lists)
The project uses a sophisticated nested list structure to manage "Layers" of shapes:
* **Main List (Doubly Linked List):** Represents the layers. Allows for bidirectional navigation (Next/Prev) between different groups of shapes.
* **Inner List (Singly Linked List):** Stored inside each node of the Main List. This list holds the actual `Shape` objects.

### 2. Polymorphism & OOP
The system is built on a strong Object-Oriented foundation:
* **`Shape` (Abstract Base Class):** Defines the interface for all graphics (`draw`, `move`, `resize`).
* **Derived Classes:**
    * `Triangle`: Renders a pyramid using ASCII characters.
    * `Rectangle`: Renders a box shape.
    * `Star`: Renders a diamond shape (calculated as `2*h - 1`).
* **`App` Class:** Acts as the controller, managing the state machine, user input, and file I/O.

### 3. Rendering Engine (Double Buffering)
To prevent console flickering during updates, a custom **`Screen` class** was implemented:
* **Buffer:** Uses a 25x80 character matrix as a frame buffer.
* **Z-Ordering:** Before drawing, shapes are sorted by their `Z-index` (depth). This ensures that shapes with higher priority are correctly drawn on top of others.
* **Clipping:** Includes logic to handle shapes that partially exceed screen boundaries without crashing.

## 🚀 Key Features
* **Random Generation:** Can generate 20+ layers with random shapes, positions, and colors.
* **File I/O:** Capable of saving and loading shape configurations from text files.
* **Interactive Menu:** Users can navigate through layers, delete specific shapes, or clear entire lists.
* **Memory Management:** Custom destructors ensure zero memory leaks by recursively deleting nodes and shapes.

## 📂 Project Structure
```text
G231210035/
├── src/            # Source codes (.cpp)
│   ├── App.cpp     # Main application logic
│   ├── Screen.cpp  # Rendering engine
│   ├── Shape.cpp   # Base class
│   └── ...         # Linked List implementations
├── include/        # Header files (.hpp)
├── doc/            # Project Report
├── bin/            # Executables
└── makefile        # Compilation script
