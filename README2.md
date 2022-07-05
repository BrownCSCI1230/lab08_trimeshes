# Lab 8: Trimeshez Lab

## 0. Intro
One of the fundamental applications of computer graphics is to display 3D objects and scenes. Recall the Realtime pipeline from lecture below.

![realtime pipeline hightlight input data][url]

The first part of the pipeline is the input data where we provide vertex positions, normals, triangle connectivity information, etc. for trimeshes which are collections of triangles. We will use trimeshes to model 3D objects and scenes in this lab and in the Realtime projects.

In the Realtime projects, you will be displaying scenes made up of the following 3D shapes: Cube, Cone, Cylinder, and Sphere. In this lab, you will be implementing two of the four shapes, Cube and Sphere. In the first Realtime Project, you will implement the remaining shapes, Cylinder and Cone. Throughout the rest of this handout there will be a couple of suggestions that we highly encourage you to consider in your design.

By the end of this lab, you will:
1. Learn to use trimeshes as a way to (approximately) represent an object ('s surface)
2. Implement a Cube and a Sphere

## 1. Representing Objects via Trimeshes
We can represent any \~_surface_~ as a triangle mesh. Conveniently, most objects in the world are defined by a surface. These objects are usually a closed surface bounding a volume like a primitive 3D shape (for example, a Cube). 

![gif of exploding trimesh][url]

With that said, some things cannot be so easily represented by a trimesh. For example, you don't typically think about fog as a surface, so it doesn't make sense to represent it as a trimesh. There are other ways to represent objects like fog, such as volumetric rendering. If you're interested, you can read more about volumetric rendering [here](https://en.wikipedia.org/wiki/Volume_rendering). 

### 1.1 Level-of-Detail (Tessellation Level)
Recall from the Ray projects that you represented the 3D shapes as implicit equations. This technically allows for infinite resolution (up to floating point limits). On the other hand, trimeshes are approximations. The more triangles used to represent a surface, the more realistic the rendering, but the more computation is required. The number of triangles used, and thus the level-of-detail of the 3D shape, is called the \~_tessellation level_~. 

~[increasing tessellation image][https://i.stack.imgur.com/uT6do.jpg]

## 2. Trimeshes In Code
Trimeshes are composed of triangles (duh) which are then composed of vertex positions (for rendering the triangle) and normals (for lighting the triangle). 

### 2.1 A Single Triangle
As you can probably guess, we render a triangle from a triplet of vertex positions in `std::vector<float> vertexPositions`. It's important to note, in our case, the winding order of the vertices is \~_counter-clockwise_~. 

![vertex positions and triangles][url]

#### 2.1.1 Per-Face Normals
If we want every point on the triangle to have the same normal, we can use per-face normals. Since we have 3 vertices, we can form two vectors to calculate the normal by taking the cross product of those two vectors.

![per face normal][https://i.stack.imgur.com/WzZ1l.jpg]

#### 2.1.2 Per-Vertex Normals
What if we want every triangle vertex to have a different normal? Then we use per-vertex normals. An example of a situation where we would want per-vertex normals is for curved surfaces. 

![curved surface normals][https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcR8POJPG4fGELGDbSflJFVyeboNzoPWS-IEjA&usqp=CAU]
![cone with normals at tip][url]

For our purposes, we will be using per-vertex normals. Each triangle is represented by a sextuplet of vertex positions and normals in `std::vector<float> vertexData` (we use `vertexData` since it's shorter than `vertexPositionsAndNormals`). Again, the winding order of vertices and normals is \~_counter-clockwise_~. 

#### 2.1.3 Why Do Normals And Winding Order Matter?
As you've already seen in the Ray projects and in Lab 06 Lighting, you need normals to properly shade objects. 

In this lab and in the Realtime projects, you need the correct winding order of positions and normals to properly render the objects. This is because of backface culling. Backface culling is a rendering technique that determines which side of the triangle is visible. 

![backface culling gif][url]

You can read more about backface culling [here](https://www.easytechjunkie.com/what-is-back-face-culling.htm).

### 2.2 Multiple Triangles, Or, A Trimesh
If you combine multiple triangles together, you'll end up with a trimesh! Recall that tessellation levels determines the number of triangles used in the trimesh. How do we represent a collection of triangles? Well, we've already seen a possible solution: just append the additional triangle information onto the back of the list. In our case, this list is still represented as `std::vector<float> vertexData`.

![cube vertex data img][url]

> Notice that `vertexData` can contain repeats since the vertex/normal will appear in the same place!

<details>
  <summary> Extra: Hand on...surely there's a more efficient way to represent a triangle mesh </summary>
  Yes, of course there is a more efficient way! Look at all the repeated vertex data :( Instead of triangle meshes, we can use [triangle strips](https://en.wikipedia.org/wiki/Triangle_strip), [triangle fans](https://en.wikipedia.org/wiki/Triangle_fan), etc. 
</details>

## 3. Creating Your Own Trimeshes
Well, now we know the most important things:
1. A shape can be represented as a variable number of triangles, depending on the level of detail
2. A collection of triangles can be represented via a list of positions and normals

Now, all that remains is to make our own implementation. At a high level, we are going to take a shape, a level of detail, and spit out the list!

### 3.1 Our Stencil Code
Take a look at our stencil code. The only files you need to concern yourself with are the files in the shapes folder. Notice that `Triangle`, `Cube`, `Sphere`, `Cone`, and `Cylinder` inherit from `OpenGLShape`. For this lab, you'll only be working with `Triangle`, `Cube`, and `Sphere`. Check the comments within the code for how exactly to edit each shape. 

For our purposes, **each shape is centered at the origin and has a radius of 0.5. In other words, they lie in the range \[-0.5, 0.5] on all axes.** 

You'll notice on the left side of the UI, there are toggles to change the shape and sliders to change parameter 1 and parameter 2. The parameters control the tessellation level of each shape. We'll go into detail about what specifically the parameters do later in the handout. 

Most importantly, notice that each shape inherits `std::vector<float> m_vertexData` from `OpenGLShape`. You'll be editing this list with the positions and normals for each shape. **Note that `m_vertexData` alternates between vertex positions and normals!**

![m_vertexData][url]

On the right side of the UI, you will eventually see the shapes generated from `m_vertexData`. You won't see anything right now because `m_vertexData` is empty. 

|**_Task 1:_**|
|:---|
|In the `Triangle` class, fill out the `setVertexData()` function stub.|
|Use the following coordinate points: <ul><li>(-0.5, -0.5, 0)</li><li>(0.5, -0.5, 0)</li><li>(-0.5, 0.5, 0)</li></ul>|

Your triangle should look like this:

![triangle gif][url]
  
Notice that if you spin the triangle around, it'll disappear. This is backface culling!

### 3.2 Creating a Cube
Now that you've rendered a triangle, it's time to render a Cube :) 

#### 3.2.1 Creating a Tile
|**_Task 2:_**|
|:---|
|In the `Cube` class, fill out the `makeTile()` function stub.|
|Uncomment the `makeTile()` function call in `setVertexData()`. Note that you'll use this function for the next task.|

Your tile should look like this:

![tile gif][url]

#### 3.2.2 Creating a Face, w/ Tessellation
Now, that you have your tile, you can create one face of the Cube! Notice how parameter 1 controls the number of tiles in each row and column:

![shape tessellation img][url]

|**_Task 3:_**|
|:---|
|In the `Cube` class, fill out the `makeFace()` function stub.|
|Comment out the `makeTile()` function call in `setVertexData()` and uncomment the `makeFace()` function call. This will render the positive z face of the Cube. <ul><li>The face should tessellate differently depending on parameter 1.</li><li>Use the `makeTile()` function you wrote in the previous task in `makeFace()`.</li></ul>|

Your face should look like this:

![face tessellation gif][url]

#### 3.2.3 Bringing It All Together: Creating a Cube
|**_Task 4:_**|
|:---|
|Implement all 6 sides of your Cube using the `makeFace()` function you implemented.|
|<ul><li>You should call `makeFace()` in `setVertexData()`.</li><li>It might be helpful to draw a diagram of the Cube to figure out the positions of all its corners! Remember that the Cube has a radius of 0.5 and lies in the bounds \[-0.5, 0.5] on all axes.</li></ul>|

Your Cube should look like this:
![cube gif][url]

### 3.3 Creating a Sphere
Yay! Congratulations on making your Cube! It's time to make a Sphere. 

![sphere parameter gif][url]
![exploding wedges gif][url]

We can think of the Sphere like an orange. Oranges are made up of wedges and each wedge is made up segments. We can build an orange (aka a sphere) by procedurally generating a collection of orange wedges. 

As shown above, the shape parameters for Sphere are slightly different than Cube. The first parameter controls the number of 'segments' (like latitude), and the second parameter controls the number of 'wedges' (like longitude). 

Like Cube, the Sphere is centered at the origin and has a radius of 0.5, so it lies in the bounds \[-0.5, 0.5] on all axes. 

#### 3.3.1 Spherical Coordinates Make Things Easier
We can represent this 'orange wedge and segment' idea using spherical coordinates. In terms of spherical coordinates, parameter 1 controls 𝜙 and parameter 2 controls 𝜃. 

<details>
  <summary>Refresher: The Spherical Coordinate System</summary>

Remember polar coordinates (*r*, 𝜃) from high school geometry? Spherical coordinates (*r*, 𝜃, 𝜙) are like polar coordinates but in 3D! The spherical coordinate system specifies a 3D point in space using (*r*, 𝜃, 𝜙). for more details, read this [Wikipedia article on the Spherical Coordinate System](https://en.wikipedia.org/wiki/Spherical_coordinate_system) :)
</details>

| Coordinate | Diagram |
| :---------------------------------------------------------------: | :---------------------------------------------------------------: |	
| *r*: the radial distance from the origin. For sphere, `r=0.5` | <img src="handout_images/amog-us-among-us.gif" width="300"> |	
| 𝜃: the polar angle. For sphere, this is in radians. | <img src="handout_images/amog-us-among-us.gif" width="300"> |
| 𝜙: the azimuthal angle. For sphere, this is in radians. | <img src="handout_images/amog-us-among-us.gif" width="300"> |

#### 3.3.2 Creating a Wedge
|**_Task 5:_**|
|:---|
|Implement the `makeTile()` function stub in the `Sphere` Class.|
|<ul><li>This function should look very similar to the `makeTile()` function in the `Cube` class.</li><li>Note that the normals are calculated differently from those in Cube. The normals for Sphere are per-vertex normals. Refer to the diagram for what your normals should look like.</li></ul> ![sphere normals diagram][url]|

|**_Task 6:_**|
|:---|
|Implement the `makeWedge()` function stub in the `Sphere` Class.|
|Uncomment the `makeWedge()` function call in `setVertexData()`. <ul><li>Use the `makeTile()` function from task 5.</li><li>Remember that we are making a wedge, so you need to pay attention to parameter 1 and 𝜙.</li><li>Remember that everything is in radians!</li><li>You may find these function calls helpful:<ul><li>`glm::radians`</li><li>`glm::sin`</li><li>`glm::cos`</li></ul></li><li>You may also find these equations useful:<ul><li>`x = r * sin(𝜃) * cos(𝜙)`</li><li>`y = r * sin(𝜃) * sin(𝜙)`</li><li>`z = r * cos(𝜃)`</li></ul></li></ul>|

Your wedge should look like this:

![wedge gif][url]

#### 3.3.3 Creating a Sphere
|**_Task 7:_**|
|:---|
|Implement the `makeOrange()` function stub in the `Sphere` Class.|
|Comment out the `makeWedge()` function call in `setVertexData()` and uncomment the `makeOrange()` function call. <ul><li>Remember that everything is in radians!</li><li>Remember that we are making multiple wedges (aka a Sphere), so you need to pay attention to parameter 2 and 𝜃.</li></ul>|

Your sphere should look like this:

![sphere gif][url]

## 4. End
Now you're ready to show your work to a TA and get checked off! Congrats on finishing the Trimeshez lab. 

### Food For Thought
Next week, you'll be learning how to use OpenGL to render triangle meshes. OpenGL uses VBOs (vertex buffer objects) which store a list of vertices similar to `m_vertexData` in this lab. You'll learn more about this next week, but we just wanted to give you a brief intro. Good luck!
