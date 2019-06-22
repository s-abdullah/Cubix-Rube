# Cubix-Rube
This was a graphics project where I created a Rubicks Cube in OpenGL, C++. This applications uses stacked transformations and texture shaidng for the movements of the cube:

![alt text](https://github.com/s-abdullah/Cubix-Rube/blob/master/images/cube.png)

## Controls
### Camera Control
	'q' and 'z' for rotations in the x and negative x direction
	'a' and 'd' for rotations in the y and negative y direction
	'w' and 'x' for rotations in the z and negative z direction

### Cube Controls
	'b' and 'n' for the roations of the first face ('<shift> + b' and '<shift> + n' for negative)

![alt text](https://github.com/s-abdullah/Cubix-Rube/blob/master/images/first.png)

	'g' and 'h' for the roations of the second face ('<shift> + g' and '<shift> + h' for negative)

![alt text](https://github.com/s-abdullah/Cubix-Rube/blob/master/images/second.png)

	'o' and 'p' for the roations of the third face ('<shift> + o' and '<shift> + p' for negative)

![alt text](https://github.com/s-abdullah/Cubix-Rube/blob/master/images/third.png)

	'r' to reset the cube

### Compilation Command
g++ cubix\ rube.cpp -o main -lGL -lglut -lGLU

