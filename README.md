**README.md**

# Ozone Hole Evolution Simulator

This C++ program simulates the evolution of ozone holes over Oceania using a 15x15 grid. The simulation spans 24 months, with input read from a .txt file. The file should specify the number of ozone holes, followed by their respective x and y locations. Two sets of data are expected: the original hole locations and the predicted locations after the simulation.

## Usage

1. **Input Format:**
   - Each .txt file should contain two datasets.
   - The first set: Number of holes, followed by x and y locations for each hole.
   - The second set: Predicted hole locations after the simulation.
   
2. **Running the Program:**
   - Compile and execute `OzoneHoleEvolution.cpp`.
   - Adjust simulation duration via the `MONTHS` constant (default is 24 months).

3. **Output:**
   - Original ozone hole locations.
   - Prediction ozone hole locations.
   - Ozone hole locations after the 24-month simulation.
   - Validation of prediction accuracy.

## Example

Consider a file with the following content:

```
3
2 2
4 6
8 10
3
1 1
3 3
9 9
```

This indicates three initial ozone holes at (2, 2), (4, 6), and (8, 10). The prediction suggests holes at (1, 1), (3, 3), and (9, 9). After the 24-month simulation, the program will output the final ozone hole distribution.

## Author

- Andrew Byerly

Feel free to experiment with different initial configurations and simulation durations to observe ozone hole evolution patterns.
