# Introduction

# Representing Objects via Trimeshes
We can represent any \~_surface_~ as a triangle mesh. Conveniently, most objects in the world are defined by a surface. These objects are usually a closed surface bounding a volume like a primitive 3D shape (for example, a cube). 

![gif of exploding trimesh][url]

With that said, some things cannot be so easily represented by a trimesh. For example, you don't typically think about fog as a surface, so it doesn't make sense to represent it as a trimesh. There are other ways to represent objects, such as volumetric representations. If you're interested, you can read more about volumetric representations [here](https://en.wikipedia.org/wiki/Volume_rendering). 

## Level-of-Detail (Tesselation)
Recall from the Ray projects that you represented the 3D shapes as implicit equations. This technically allows for infinite resolution (up to floating point limits). On the other hand, triangle meshes are approximations. This method of representing 3D objects as a collection of triangles is called \~_tessellation_~. The more triangles used to represent a surface, the more realistic the rendering, but the more computation is required. 

~[increasing tessellation image][https://i.stack.imgur.com/uT6do.jpg]

# Trimeshes In Code
Trimeshes are composed of triangles (duh) which are then composed of vertex positions (for rendering the triangle) and normals (for lighting the triangle). 

## A Single Triangle
As you can probably guess, we render a triangle from a triplet of vertex positions in `std::vector<float> vertexPositions`. It's important to note, that in our case, the winding order of the vertices is \~_counter-clockwise_~. 

![vertex positions and triangles][url]

### Per-Face Normals
If we want every point on the triangle to have the same normal, we can use per-face normals. Since we have 3 vertices, we can form two vectors to calculate the normal by taking the cross product of those two vectors.

![per face normal][https://i.stack.imgur.com/WzZ1l.jpg]

### Per-Vertex Normals
What if we want every triangle vertex to have a different normal? Then we use per-vertex normals. An example of a situation where we would want per-vertex normals is for curved surfaces. 

![curved surface normals][https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcR8POJPG4fGELGDbSflJFVyeboNzoPWS-IEjA&usqp=CAU]
![cone with normals at tip][url]

For our purposes, we will be using per-vertex normals. Each triangle is represented by a sextuplet of vertex positions and normals in `std::vector<float> vertexData` (we use `vertexData` since it's shorter than `vertexPositionsAndNormals`). Again, the winding order of vertices and normals is \~_counter-clockwise_~. 

### Why Do Normals And Winding Order Matter?
As you've already seen in the Ray projects and in Lab 06 Lighting you need normals to properly shade objects. In this lab and in the Realtime projects, you need the correct winding order of positions and normals to properly render the objects. This is because of backface culling. Backface culling is a rendering technique that determines which side of the triangle is visible. 

![backface culling gif][url]

You can read more about backface culling [here](https://www.easytechjunkie.com/what-is-back-face-culling.htm).

## Multiple Triangles, Or, A Triangle Mesh
If you combine multiple triangles together, you'll end up with a trimesh! Neat, right? Recall, this is called tessellation! How do we represent a collection of triangles? Well, we've already seen a possible solution: just append the additional triangle information onto the back of the list. In our case, this list is still represented as `std::vector<float> vertexData`.

![cube vertex data img][url]

> Notice that `vertexData` can contain repeats since the vertex/normal will appear in the same place!

<details>
  <summary> Extra: Hand on...surely there's a more efficient way to represent a triangle mesh </summary>
  Yes, of course there is a more efficient way! Look at all the repeated vertex data :( Instead of triangle meshes, we can use [triangle strips](https://en.wikipedia.org/wiki/Triangle_strip), [triangle fans](https://en.wikipedia.org/wiki/Triangle_fan), etc. 
</details>

# Creating Your Own Trimeshes
Well, now we know the most important things:
1. A shape can be represented as a variable number of triangles, depending on the level of detail
2. A collection of triangles can be represented via a list of positions and normals

Now, all that remains is to make our own implementation. At a high level, we are going to take a shape, a level of detail, and spit out the list!

## Our Stencil Code
Take a look at our stencil code. The only files you need to concern yourself with are the files in the shapes folder. Notice that `Triangle`, `Cube`, `Sphere`, `Cone`, and `Cylinder` inherit from `OpenGLShape`. For this lab, you'll only be working with `Triangle`, `Cube`, and `Sphere`. Check the comments within the code for how exactly to edit each shape. 

For our purposes, each shape is centered at the origin and has a radius of 1. In other words, they lie in the range \[-0.5, 0.5] on all axes. 

You'll notice on the left side of the UI, there are toggles to change the shape and sliders to change parameter 1 and parameter 2. The parameters control the tessellation of each shape. We'll go into detail about what specifically the parameters do later in the handout. 

Most importantly, notice that each shape inherits `std::vector<float> m_vertexData` from `OpenGLShape`. You'll be editing this list with the positions and normals for each shape. **Note that `m_vertexData` alternates between vertex positions and normals!**

![m_vertexData][url]

On the right side of the UI, you will eventually see the shapes generated from `m_vertexData`. You won't see anything right now because `m_vertexData` is empty. 

|**_Task 1:_**|
|:---|
|Make a Triangle|
|In the `Triangle` class, fill out the `setVertexData()` function stub. Use the following coordinate points: <ul><li>(-0.5, -0.5, 0)</li><li>(0.5, -0.5, 0)</li><li>(-0.5, 0.5, 0)</li></ul>|

Your triangle should look like this:

![triangle gif][url]
  
Notice that if you spin the triangle around, it'll disappear. This is backface culling!

## Creating a Cube
Now that you've rendered a triangle, it's time to render a Cube :)

### Creating a Tile
|**_Task 2:_**|
|:---|
|Make a Tile|
|In the `Cube` class, fill out the `makeTile()` function stub. Uncomment the `makeTile()` function call in `setVertexData()`. Note that you'll use this function for the next task.|

Your tile should look like this:

![tile gif][url]

### Creating a Face, w/ Tessellation
Now, that you have your tile, you can create one face of the Cube! Notice how parameter 1 controls the number of tiles in each row and column:

![shape tessellation img][url]

|**_Task 3:_**|
|:---|
|Make a Face|
|In the `Cube` class, fill out the `makeFace()` function stub. Comment out the `makeTile()` function call in `setVertexData()` and uncomment the `makeFace()` function call. This will render the positive z face of the Cube. <ul><li>The face should tessellate differently depending on parameter 1.</li><li>Use the makeTile() function you wrote in the previous task in order to create a face of the cube.</li></ul>|

Your face should look like this:

![face tessellation gif][url]

### Bringing It All Together: Creating a Cube
|**_Task 4:_**|
|:---|
|Make a Cube|
|Now that you have one side of the Cube, you should be able to implement all 6 sides of your Cube using the `makeFace()` function you implemented. You should call `makeFace()` in `setVertexData()`. It might be helpful to draw a diagram of the Cube to figure out the positions of all its corners!|

Your Cube should look like this:
![cube gif][url]

## Creating a Sphere
### Spherical Coordinates Make Things Easier
### Creating a Wedge
### Creating a Sphere

# End
