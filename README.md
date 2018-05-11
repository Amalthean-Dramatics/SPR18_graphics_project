# SPR18_graphics_project
Riley Myers and Chandra Sundaram

## Final Update
The code is finished to a point where we are, if not satisfied, accepting of the
flaws existing in it. Texture rendering seems to be less than perfect, although
that may be due to a lack of proper set-up in Blender.  Unfortunately, we were unable to dedicate as much time to our model as we both would have liked, leaving that aspect less polished. The organization is as follows:

|`images`   | Various images for textures or including in the documentation |
|-----------|---------------------------------------------------------------|
|`models`   | 3D models, with very imaginative names                        |
|`shaders`  | Shaders used in the program                                   |
|`textures` | Textures used in the program                                  |

### Controls
`w, a, s, d` -- Move forward, left, backward, and right  
`z, c`       -- Move up and down  
`m`          -- Toggle the polygon rendering mode (touchy)  
`ESC`        -- Exit the museum  

Apologies for turning this in slightly late -- We've both had rather busy
semesters and busy finals weeks. Thank you so much for a great class, and have a
great summer! 
        -- Riley Myers




## Basic Triangles
Based on the code provided, we modified the code to appear as follows:

![Inverted Triforce, with shapes filled](images/full_inv_tri.png)
![Inverted Triforce, with wireform edge](images/wire_inv_tri.png)

The `m` key can be pressed to cycle between the three polygon display modes
provided by OpenGL.

## Museum Plans
* Multi-Themed Museum, with each room having its own theme, or variation on a
  theme. We are not quite sure what our final plan will be. Meow Wolf's House of
  Eternal Return seems like it may be a inspiration.
* We are planning on starting with 4 rooms, with the ability to add more if we
  feel that we don't have enough to do already :laughing:.
* We would like for one room to be a topological map room (entire room is a
  topological map) - the _room_ is the sculpture....
* We are unsure about whether or not we will have a ceiling at the moment. 
* This is a sculpture we'd like to place in the museum:
 ![first sculpture](images/sculpture.png)
* We are also undecided about what forms/placements/images that we want to use
  for paintings. This is something that we are working on.
* We have not started looking for textures for the surfaces in the museum --
  This is something that will depend on the theming of each room, and that too
  has not been settled upon.



## 2018-02-14 ##

Added basic layout of museum as a blender file in the models directory. If you
want a plain link, try [here](models)


## 2018-02-24 ##
Added some model loader functionality. Running into compilation errors with
regards to the order in which header files are processed.


## 2018-03-07 ##
Loads the model correctly, but seems to have some rendering errors on some
computers (memory issues?).
