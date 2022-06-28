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
## Our Stencil Code
## Creating a Cube
### Cureating a Quad
### Creating a Plane, w/ Tessellation
### Bringing It All Together: Creating a Cube

## Creating a Sphere
### Spherical Coordinates Make Things Easier
### Creating a Wedge
### Creating a Sphere

# End
