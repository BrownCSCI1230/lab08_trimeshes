# Lab 8: Trimeshez Lab

[GitHub Classroom assignment](https://google.com)

## 0. Intro

One of the fundamental applications of computer graphics is to display three-dimensional scenes. The catch, however, is that screens can only display two-dimensional images. Therefore, there needs to be some way to convert a three-dimensional scene to something that can be viewed in two dimensions. A common method, which we will use in this lab, is to compose a scene using only triangles, then project those triangles to the screen, drawing each one sequentially.

In this lab, you will be writing the portion of this process that pertains to tesselating objects. You will be breaking up these 3D objects, or primitives, into a lot of triangles that, when put together, look as much like the desired primitive as possible. Note that curved surfaces can be better approximated using more triangles, but keep in mind that the more triangles we draw the more triangles we compute, and a major motivation behind tessellating objects is to simplify the process of displaying them.

In the Real-Time projects, you will be displaying scenes made up of 3D shapes: Cube, Cone, Cylinder, and Sphere. In this lab, you will be implementing two of the four primitives, Cube and Sphere. You will implement the remaining shapes, Cylinder and Cone, in the Real-Time Project #1. Throughout the rest of this handout there will be a couple of suggestions that we highly encourage you to consider in your design.

By the end of this lab, you will:

1. Understand that primitives are created from a long list vertices and normals
2. Learn how to calculate normals given 3 points
3. Learn how to create and implement a Cube and a Sphere

## 1. Background

Here are a few concepts that you should know before you implement your Cube and Sphere. These concepts are outlined below.

### 📌 1.1. OpenGL’s 3D Coordinate System

Understanding the coordinate system in OpenGL will save you a lot of debugging time later on. It’s simple -- the positive X axis points towards the right of the screen, the positive Y axis points towards the top of the screen, and the positive Z axis points out of the screen towards the viewer. 

![coordinate system](opengl_coor_sys image path)

### 📌 1.2 Drawing a Triangle

#### 🔎 1.2.1 Positions and Normals ####

To draw a single triangle in OpenGL, you will need to provide the 3 vertex positions (x, y, z) and 3 unit vector normals (i, j, k) of the triangle. If you combine multiple triangles together, you’ll end up with a 3D shape. In this lab and in the Real-Time projects, these points will be contained in each primitive’s `std::vector<float> m_vertexData`. `m_vertexData` is a longggg list of vertices and normals. The order in which you provide the vertex positions and unit vector normals dictates how the triangle will be rendered. See the diagram below for details.
> Note: m_vertexData is a vector of floats


![triangle](triangle diagram image path)


![hard-coded cube](cube diagram image path)
> Note: the list of vertices and normals can contain repeats since the vertex/normal will appear in the same place

(Fun Fact?)

#### 🔎 1.2.2 Calculating Normals ####


![cross product](cross product image path)

> Note: Order of cross product matters! If the lighting of the triangle is off, it’s likely that your normals are wrong. Remember the right-hand rule?

> Note: `glm::cross` and `glm::normalize` are super helpful for calculating the normals.

#### 🔎 1.2.3 Counter-clockwise Order and Alternating Position and Normals ####

As you can see, `m_vertexData` alternates between vertex positions and normals. The positions are simply the (x,y,z) coordinates of the vertices in world space, and the normals are unit vectors that are perpendicular to the face of the triangle. Most importantly, notice the order in which we provide the vertices for the triangle. The vertex positions and normals are in counter-clockwise order. This is important because of backface culling.

#### 🔎 1.2.4 Backface Culling ####

Backface culling determines the visibility of an object. In other words, one side of the triangle will be visible to the viewer, and the other side of the triangle will be invisible. You can read more about [backface culling here](https://en.wikipedia.org/wiki/Back-face_culling)!

![gif of rotating triangle showing both sides of the triangle](gif file path)

If your triangle is not visible, it’s likely that your points are in the wrong order. Remember, positions and normals have to go in counterclockwise order!

#### 🔎 1.2.5 Composing Multiple Triangles to Create a 3D Shape Mesh ####

If you combine multiple triangles together, you get a 3D mesh! Neat, right?

TODO: include screenshots of the Cube, Cone, Cylinder, and Sphere primitives

### Stencil Code and Interacting with the UI ###
TODO: explanation of UI and stencil code. Will do this after we write the code lol

📝 **Task 1**

In the Triangle class, fill out the `tessellate_triangle()` function stub. Use the coordinate points (-0.5, -0.5, 0), (0.5, -0.5, 0), (0, 0.5, 0). Don’t forget the normals!

Your triangle should look like this:

![task1 triangle](triangle screenshot image path)

## 2. Cube

Now it’s time to start creating the primitives 🤗😇😎. Each primitive is centered at the origin, and has a radius of 1. In other words, they lie in the range [-0.5, 0.5] on all axes. 

You’ll notice that there are sliders on the left side of the screen that control the shape parameters. These parameters control the number of triangles used to tessellate each face of the Cube. 


![Cube tessellation params](image path)

📝 **Task 2.1**

In the Cube class, implement the `makeTile()` function stub. This function generates a plane composed of two triangles. Don’t forget the normals!

<details>
  <summary>What are the makeTile() inputs and outputs?</summary>
	
makeTile() takes in 3 inputs:
- `glm::vec3 topLeft`
- `glm::vec3 bottomLeft`
- `glm::vec3 bottomRight`
- `glm::vec3 topRight`

These inputs represent 3D coordinates of the top left, bottom left, bottom right, and top right vertex positions of the tile.
	
![example diagram](img path)
	
`makeTile()` returns a vector of floats that holds the positions and normals of the tile, which then can be concatenated to `m_vertexData`. Don’t forget about counter-clockwise order!
	
</details>

Your tile should look like this:

![task2 tile](gif path)

📝 **Task 2.2**

In the Cube class, implement the positive x side of the Cube in the `makeFace()` function stub. Use the `makeTile()` function you wrote in Task 2.1. 

<details>
  <summary>What are the makeFace() inputs?</summary>
	
You’ll notice in the `makeFace()` function call, we have provided the coordinates of the 4 corners of the positive x face. Refer to the stencil code for more information about the inputs to the `makeFace()` function.
	
</details>

> Note: Don’t forget that param 1 controls the number of triangles in each row and column!

<details>
  <summary>🤔Hint: How do I use the `makeTile()` function?</summary>
	
The key here is to know what the four points you need to pass into `makeTile()`. Take a look at how parameter 1  affects the tessellation of the plane, and how it changes the intervals of where the vertex positions are located.
	
</details>

You should end up with something that looks like this:

![task2 cube side](image path)

You will use what you write here to generate all six sides of the Cube for the next task.

📝 **Task 2.3**

Now that you have one side of the Cube, you should be able to implement all 6 sides of your Cube using the `makeFace()` function you implemented. It may be helpful to draw a diagram of the Cube to figure out the positions of all its corners!

Your Cube should now look like this:

![task2.2 cube gif][gif path]

## 3. Sphere

Yay! Congratulations on making your Cube! 🙌 It’s to time to make a Sphere 🥳🎉 This is a wee bit more complicated, but don’t worry we’ll walk you through it!

The shape parameters for Sphere are slightly different than Cube. The first parameter controls the number of ‘layers’ in the vertical direction, and the second parameter controls the number of ‘layers’ in the horizontal direction, as shown below. You can also think about this in terms of latitude and longitude -- param 1 controls latitude, and param 2 controls longitude. In term of spherical coordinates, parameter 1 controls 𝜙 and parameter 2 controls 𝜃.

<details>
  <summary>How Parameters 1 and 2 Affects Sphere Diagram</summary>

	*TODO insert image*
	
</details>

<details>
  <summary>Spherical Coordinates Diagram</summary>

TODO insert image
	
Remember polar coordinates (*r*, 𝜃) from high school geometry? Spherical coordinates (*r*, 𝜃, 𝜙) are like polar coordinates, but in 3D! Read this [Wikipedia article on the Spherical Coordinate System](https://en.wikipedia.org/wiki/Spherical_coordinate_system) if you need a refresher!

</details>

### 📌 3.1 Oranges! 🦧🍊🍊🍊

Let’s start by thinking of the sphere as an orange. Oranges are made up of slices and each slice is made up of segments. We can build an orange (aka a sphere) by procedurally generating a collection of orange slices (aka a sphere slice). In the following task, you will implement this orange slice.

![orange slice](image path)

<details>
  <summary>How does thinking of orange slices relate to this?</summary>
	
The number of slices in the orange are controlled by param 2 (which is used to calculate 𝜃). The number of segments are controlled by param 1 (which is used to calculate 𝜙). Using both these parameters, we can determine the exact 3D location of each vertex!
	
</details>

By using 𝜃 and 𝜙, we can get every vertex position by rotating a vector about the origin. 

> Note: You may find the following useful in your implementation: `glm::radians()`, `glm::sin()`, and `glm::cos()`
> Note: Everything is in radians!

📝 **Task 3.1.1**

Copy your `makeTile()` function from your Cube class into the Sphere class. You will use this function when implementing Sphere.

📝 **Task 3.1.2**

In the Sphere class, implement a slice of the Sphere in the `make_slice()` function stub. Use your `makeTile()` function that you copied over. This is the most difficult task, so we have provided a few hints below if you get stuck. Try thinking about how you may calculate 𝜙 and how you may use that to generate a slice. Try implementing your ideas, and if you get stuck, you may reveal a hint or ask one of the TA’s for help!

<details>
  <summary>What are the `make_slice()` inputs?</summary>
	
You’ll notice that the inputs of the `make_slice()` function are `currentTheta` and `nextTheta`. `currentTheta` is the 𝜃 of all the vertices on the left side of the slice, and `nextTheta` is the 𝜃 of all the vertices on the right side of the slice. 

</details>

<details>
  <summary>🤔Hint: How do I calculate 𝜙?</summary>
	
	𝜙 = 𝜋 / param1
	
Refer to the diagram in section 3 to understand the reasoning behind this calculation. 
	
</details>

<details>
  <summary>🤔Hint: How do I use 𝜃 and 𝜙 to calculate my four points for makeTile()?</summary>
	
**Note:** The start and end angles of 𝜙!

You can get the 3D position using the following equations:

	x = r * sin(𝜃) * cos(𝜙)

	y = r * sin(𝜃) * sin(𝜙)

	z = r * cos(𝜃)
	
</details>

<details>
  <summary>🤔Hint: Help! But the top and bottom of the slice are triangles???</summary>
	
Don’t worry, that’s okay! You can still use your `makeTile()` function to make these triangles. Remember that `makeTile()` generates a plane consisting of two triangles. But what if the two triangles were overlapping 🤔🤔🤔. Then the tile would look like a triangle, right?
	
In order to make code cleaner and more concise, it’s a good idea to reuse functions where you can. Sometimes, in Computer Graphics that means you will have overlapping triangles, but that’s okay because they are going to appear in the same place anyway 😁.
	
Think about what input vertex positions to `makeTile()` would yield a triangle, and use that to make the top and bottom of your slice!
	
(If you really don’t want to use `makeTile()` for the top and bottom triangles, you may implement them separately from your `makeTile()` calls.)
	
</details>

<details>
	<summary>🤔Hint: Pseudocode</summary>

```cpp
For each segment {
	// calculate currentPhi
	// calculate nextPhi

	// using currentTheta and currentPhi, calculate the bottomLeft point 
	// using nextTheta and currentPhi, calculate the bottomRight point 
	// using currentTheta and nextPhi, calculate the topLeft
	// using nextTheta and nextPhi, calculate the topRight point 

	makeTile(topLeft, bottomLeft, bottomRight, topRight)
	// add output of makeFace to m_vertexData
}
```
	
</details>

📝 **Task 3.2**

Once you have finished making a singular slice of the orange, it’s time to make the whole orange! Implement the `make_orange()` function stub in the Sphere class. 

<details>
	<summary>🤔Hint: Pseudocode</summary>
	
```cpp
For each orange_slice {
	// calculate the currentTheta
	// calculate the nextTheta
	make_slice();

	// add vertices and normals to m_vertexData
}
```
	
</details>

## End

Now you’re ready to show your work to a TA and get checked off! Congrats on finishing the Trimeshez lab 🥳🎉

🥟 **Food for Thought** 🍾🥂
Next week, you will be learning how to use OpenGL to render triangle meshes. OpenGL uses VBOs (vertex buffer objects) which store a list of vertices similar to `m_vertexData` in this lab. You’ll learn more about this next week, but we just wanted to give you a brief intro. Good luck!
