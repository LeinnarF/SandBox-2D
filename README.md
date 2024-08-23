# Sandbox-2D

This project is a cellular automata sandbox written in C++ using the Raylib library. It simulates the behavior of various elements like sand, water, fire, oil, and more, allowing users to interact with and observe the different interactions between these elements.

![Cellular Automata Sandbox](./resources/sandbox.gif)

## Features

- **Elemental Simulation**: Simulates various elements such as sand, water, stone, lava, smoke, cement, acid, oil, fire, and gunpowder.
- **Dynamic Interactions**: Elements react to one another, creating dynamic and realistic behaviors like burning, dissolving, flowing, and exploding.
- **Scalable Design**: The project is designed with scalability in mind, making it easy to add new elements and behaviors.

## Getting Started

### Prerequisites

- **C++ Compiler**: Ensure you have a C++17 compatible compiler installed.
- **Raylib**: Install the Raylib library for rendering and input handling. You can find installation instructions on the [Raylib GitHub repository](https://github.com/raysan5/raylib).

### Installation

##### Clone the repository

```
git clone https://github.com/LeinnarF/SandBox-2D.git
```

#### For Windows

Follow the instruction on the [Raylib GitHub repository](https://github.com/raysan5/raylib/wiki/Working-on-Windows)

##### Using Visual Studio with vcpkg

```
  vcpkg install raylib:x64-windows
```

### Project Structure

- **main.cpp**: The entry point of the application.
- **grid.h / grid.cpp**: Contains the grid class that manages the state of the simulation.
- **element.h / element.cpp**: Contains the logic for each element's behavior.
- **handler.cpp**: Manages the update and draw loops for the simulation, ensuring scalability and maintainability.

### Adding New Elements

To add a new element to the sandbox:

1. **Define the Element**: Add a new `enum` value for your element in `elementEnum.h`.
2. **Implement Element Logic**: Create the necessary logic for your element in `element.cpp`.
3. **Update the Handler**: Add your element's update and draw functions to the maps in `handler.cpp`.
4. **Color Management**: Define the color for your element in the `ColorManager::elementColor` method.

### Controls

- **Mouse Click**: Add the currently selected element to the grid.
- Select the element at the right panel.
