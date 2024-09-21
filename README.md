# Rotating Project

Taking inspiration from Andy Sloane and his famous [donut](https://www.a1k0n.net/2011/07/20/donut-math.html),
I wanted to see if I could create a shape in ASCII art rotating around in the terminal.

What this has lead to is creating a shape class that can be inherited from to get the display to the terminal.
All an inheriting shape has to do it setup the 3d space full of points and the Shape parent should do the rest.

Currently not finished but that's the goal...

## How this is working:

1. Cube object creates the 3D space using Coords.
2. We calculate the normal of the surface and use this to find the angle against the light, the more aligned, the more
3. We create a projection of the 3D space into 2D.

## Current problems:

1. Normals are not calculated correctly, or if they are the wrong one is being chosen. Could be due to a number of things:
    - Incorrect order during cross product. Might need to make sure we aren't getting the normal pointing inside the shape.
    - get_nearby() could be choosing wrong points to create cross prod with, should vefiry that the points are correct.
2. Need to figure out why its slowly zooming away, this should not be happening. Maybe its a problem with floating point numbers? Maybe we're rounding somewhere, not sure.

## Improvements:

1. Use GPU calculations for vector calculations (will need to then limit frame rate).
2. Create vector class so that we know when dealing with vectors or points (coords). Not neccesary but could be helpful.
