import matplotlib.pyplot as plt
import numpy as np
from collections import defaultdict # Automatically assigns a default value for keys that do not yet exist

# Reading data from the file
data = defaultdict(lambda: defaultdict(int)) # Dictionary to store data for the plots

with open('results.txt', 'r') as file:
    for line in file:
        parts = line.strip().split()
        if len(parts) == 3:
            maze_size = parts[0]
            algorithm = parts[1]
            steps = int(parts[2])
            data[maze_size][algorithm] = steps

# Preparing data for the plot
maze_sizes = sorted(data.keys()) # Sorting keys in ascending order
algorithms = list(next(iter(data.values())).keys()) # Extracting the names of the algorithms

x = np.arange(len(maze_sizes))  # Indices for maze sizes, e.g., x = array([0, 1, 2]) corresponds to indices: '10x10', '20x20', '30x30'
width = 0.2  # Width of the bars

# Generating a bar plot
fig, ax = plt.subplots(figsize=(10, 6))

for i, algorithm in enumerate(algorithms):
    steps = [data[size][algorithm] for size in maze_sizes] # Extracting the number of steps for each maze size and algorithm
    ax.bar(x + i * width, steps, width, label=algorithm) # Setting bars with appropriate widths, heights, and labels for algorithms

ax.set_xlabel('Maze Size')
ax.set_ylabel('Number of Steps')
ax.set_title('Comparison of Algorithm Efficiency in Maze Solving')
ax.set_xticks(x + width * (len(algorithms) - 1) / 2) # Setting the positions of X-axis labels at the center of the bar groups
ax.set_xticklabels(maze_sizes) # Setting X-axis labels to the maze size values
ax.legend()
ax.grid(axis='y') # Grid lines only for the y-axis
plt.tight_layout() # Adjusting layout to avoid overlapping elements
plt.show()
