Challenge 5 - Andrés Mejía-Posada
=================================

Render a Bézier surface based on some control points that are to be read from a text file.

Screenshot
-----------

See shot.png.

### Legend

* Red axis: X axis
* Green axis: Y axis
* Blue axis: Z axis
* Yellow mesh: Bézier surface
* White dots: Control points for the Bézier surface
* Gray lines: Lines that connect all control points together.

Run it yourself
---------------

These instructions are for Mac OS X. Your mileage may vary.

    cd src
    g++ main.cpp -framework GLUT -framework OpenGL -o bezier
    ./bezier ../input/1.txt
    
On the window that appears, press:

* `a` and `d` to rotate the camera around the Y axis (the green one).
* `w` and `s` to increase or decrease the camera's distance to the origin.
* `q` and `e` to rotate the camera around the X axis (the red one).


Video demo
-----------

See demo.mov.