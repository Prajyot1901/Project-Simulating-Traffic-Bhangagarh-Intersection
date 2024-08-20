# Traffic Simulation at Bhangagarh Junction

## Project Overview

This project simulates traffic at the Bhangagarh junction using real-world data(Note: The project has been built on real-world data,but can not provide the data due to security reasons. Hence attached a randomised data with the project) and C++ with the Simple and Fast Multimedia Library (SFML) for rendering. The simulation models the behavior of vehicles at the junction, with each vehicle adhering to traffic laws as a typical law-abiding driver would. 

For convenience, the simulation groups five bikes together and considers them as equivalent to a single car. The project leverages concepts from Group Theory for random sequence generation and Queuing Theory to model the queue dynamics and vehicle behavior at the junction.

## Features

- **Realistic Traffic Simulation**: The traffic behavior at Bhangagarh junction is modeled based on real data, providing a realistic representation of vehicle movement and interaction.
- **SFML Graphics**: The project uses SFML to visually simulate the traffic, providing a clear and interactive way to observe the simulation in real-time.
- **Law-Abiding Vehicle Behavior**: Vehicles in the simulation behave according to traffic rules, mimicking the actions of real drivers at the junction.
- **Group Handling**: To simplify the simulation, a group of five bikes is treated as a single car.
- **Theoretical Foundations**:
  - **Group Theory**: Used to generate random sequences, ensuring variability in vehicle arrival and behavior.
  - **Queuing Theory**: Applied to model the formation and clearing of queues, along with the overall vehicle behavior at the junction.

## Getting Started

### Prerequisites

- **C++ Compiler**: Ensure you have a C++17 compatible compiler installed.
- **SFML**: The project requires SFML for graphics. You can download it from [SFML's official website](https://www.sfml-dev.org/download.php).

### Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/prajyot1901/Project-Simulating-Traffic-Bhangagarh-Intersection.git
2. Copy the source code from the file Simulator_test1/Simulator_Test1/Simulator.cpp
3. Download the Randomised-Traffic-Data.csv file in the same directory as the source code.
4. Download SFML and link to the project. Take reference of the Youtube video: https://www.youtube.com/watch?v=2jOzJ8SIpr8&list=PL6xSOsbVA1eaJnHo_O6uB4qU8LZWzzKdo&index=3
5. Now the Installation is complete You can run the code with any enviornment.
