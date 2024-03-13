# My Radar - Air Traffic Simulator

## Introduction

Welcome to **My Radar**, an air traffic simulator developed as a project during the first year of Epitech. This project aims to simulate air traffic control scenarios where planes interact with control towers. It offers a simple yet insightful simulation of air traffic management.

## Building the Project

To build **My Radar**, follow these simple steps:

1. Clone the repository to your local machine:

    ```
    git clone https://github.com/EnzoDubeaurepaire/my_radar.git
    ```

2. Navigate to the project directory:

    ```
    cd my_radar
    ```

3. Build the project using `make`:

    ```
    make
    ```

## Launching the Simulator

Once the project is built successfully, you can launch the simulator using the following command:

```
./my_radar [OPTIONS]
```
Replace [OPTIONS] with either -h to display the helper or the path to the list of planes and control towers.

The file containing the planes and control towers must have the following syntax :

  Each line is either :
  * A 'x_takeoff' 'y_takeoff' 'x_landing' 'y_landing' 'speed' 'takeoff_delay'
    for a plane
    
  * T 'x_position' 'y_position' 'radius'
    for a tower
