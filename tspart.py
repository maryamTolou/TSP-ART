from PIL import Image
import numpy as np
import matplotlib.pyplot as plt
from scipy.spatial.distance import pdist, squareform
from tsp_solver.greedy_numpy import solve_tsp

# image_path = input("Enter your picture exact location:")
# number_of_points = input("Enter no of points you want:")
number_of_points = 900
image_path = 'Monalisa.png'
# tsp_answers = []

# dithering image
original_image = Image.open(image_path)
bw_image = original_image.convert('1', dither=Image.NONE)

# bw_image.show()
bw_image_array = np.array(bw_image, dtype=np.int)
# COORDINATE:
black_indices = np.argwhere(bw_image_array == 0)
chosen_black_indices = black_indices[
    np.random.choice(black_indices.shape[0],
                     replace=False,
                     size=number_of_points)]

fw = open("coordinate.txt", 'w')
fw.write(str(number_of_points) + '\n')
for k in range(0,len(chosen_black_indices)):
    fw.write(str(chosen_black_indices[k][1]) + " " + str(chosen_black_indices[k][0]) + '\n')

# print(chosen_black_indices[0])


plt.figure(figsize=(6, 8), dpi=100)
plt.scatter([x[1] for x in chosen_black_indices],
            [x[0] for x in chosen_black_indices],
            color='black', s=1)
plt.gca().invert_yaxis()

plt.xticks([])
plt.yticks([])
plt.show()



distances = pdist(chosen_black_indices)
distance_matrix = squareform(distances)
# print(len(distance_matrix[0]))
# print(distance_matrix[0][1])



optimized_path = solve_tsp(distance_matrix)
print(optimized_path)
'''
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
'''
plt.show()

