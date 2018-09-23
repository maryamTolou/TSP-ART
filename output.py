from PIL import Image
import numpy as np
import matplotlib.pyplot as plt

optimized_path = solve_tsp(distance_matrix)
optimized_path_points = [chosen_black_indices[x] for x in optimized_path]

plt.figure(figsize=(8, 10), dpi=100)
plt.plot([x[1] for x in optimized_path_points],
         [x[0] for x in optimized_path_points],
         color='black', lw=1)
plt.xlim(0, 600)
plt.ylim(0, 800)
plt.gca().invert_yaxis()
plt.xticks([])
plt.yticks([])
plt.show()