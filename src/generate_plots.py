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
maze_sizes = data.keys()
algorithms = list(next(iter(data.values())).keys()) # Extracting the names of the algorithms

x = np.arange(len(maze_sizes))  # Indices for maze sizes, e.g., x = array([0, 1, 2]) corresponds to indices: '10x10', '20x20', '30x30'
width = 0.2  # Width of the bars

# Generating a bar plot
fig1, ax1 = plt.subplots(figsize=(10, 6))

for i, algorithm in enumerate(algorithms):
    steps = [data[size][algorithm] for size in maze_sizes] # Extracting the number of steps for each maze size and algorithm
    ax1.bar(x + i * width, steps, width, label=algorithm) # Setting bars with appropriate widths, heights, and labels for algorithms

ax1.set_xlabel('Maze Size')
ax1.set_ylabel('Number of Steps')
ax1.set_title('Comparison of Algorithm Efficiency in Maze Solving')
ax1.set_xticks(x + width * (len(algorithms) - 1) / 2) # Setting the positions of X-axis labels at the center of the bar groups
ax1.set_xticklabels(maze_sizes) # Setting X-axis labels to the maze size values
ax1.legend()
ax1.grid(axis='y') # Grid lines only for the y-axis


# Calculating and plotting average steps
avg_steps = {algorithm: np.mean([data[size][algorithm] for size in maze_sizes]) for algorithm in algorithms}

# Generating the average steps plot
fig2, ax2 = plt.subplots(figsize=(8, 5))
algorithms = list(avg_steps.keys())
avg_values = list(avg_steps.values())

ax2.bar(algorithms, avg_values, color='skyblue')
ax2.set_xlabel('Algorithms')
ax2.set_ylabel('Average Steps')
ax2.set_title('Average Number of Steps for Each Algorithm')
ax2.grid(axis='y')

# Generating a line plot for algorithm efficiency
fig3, ax3 = plt.subplots(figsize=(10, 6))

line_styles = ['-', '--', '-.', ':'] # Different line styles
markers = ['o', 's', '^', 'D']       # Different marker styles
colors = ['b', 'g', 'r', 'm']        # Different colors

for i, algorithm in enumerate(algorithms):
    steps = [data[size][algorithm] for size in maze_sizes] # Extracting steps for each maze size and algorithm
    ax3.plot(maze_sizes, steps, 
             label=algorithm, 
             linestyle=line_styles[i % len(line_styles)], # Cycle through line styles
             marker=markers[i % len(markers)],           # Cycle through markers
             color=colors[i % len(colors)],             # Cycle through colors
             markersize=8)                              # Increase marker size for better visibility

ax3.set_xlabel('Maze Size')
ax3.set_ylabel('Number of Steps')
ax3.set_title('Algorithm Efficiency Across Maze Sizes')
ax3.legend()
ax3.grid(axis='both') # Grid lines for both axes

plt.tight_layout() # Adjusting layout to avoid overlapping elements
plt.show()