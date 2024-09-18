# Rotating Project

Taking inspiration from Andy Sloane and his famous [donut](https://www.a1k0n.net/2011/07/20/donut-math.html),
I wanted to see if I could create a shape in ASCII art rotating around in the terminal.

What this has lead to is creating a shape class that can be inherited from to get the display to the terminal.
All an inheriting shape has to do it setup the 3d space full of points and the Shape parent should do the rest.

Currently not finished but that's the goal...


## How this is working:
1. Cube object creates the 3D space using Coords. 
2. 