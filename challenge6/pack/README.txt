Challenge 6 - Andrés Mejía
==========================

Like challenge 4 (create a robotic arm in OpenGL with 3 articulations) but add lighting to the scene.

* The shoulder should rotate around the Y and Z axes.
* The elbow should rotate around the Z axis.
* The wrist should rotate around the X and Z axes.

Run it yourself
---------------

These instructions are for Mac OS X. Your mileage may vary.

    cd challenge6/challenge6
    g++ main.cpp -framework GLUT -framework OpenGL -o arm
    ./arm
    
On the window that appears, press:

* `q` and `a` to increase or decrease the angle of rotation around the Y axis at the shoulder.
* `w` and `s` to increase or decrease the angle of rotation around the Z axis at the shoulder.
* `e` and `d` to increase or decrease the angle of rotation around the Z axis at the elbow.
* `r` and `f` to increase or decrease the angle of rotation around the Z axis at the wrist.
* `t` and `g` to increase or decrease the angle of rotation around the X axis at the wrist.
* `↑` and `↓` to increase or decrease the camera's distance to the object.
* `←` and `→` to increase or decrease the camera's angle of rotation around the Z axis.

Screenshots
-----------

See /shots.

Source code
-----------

Available at https://github.com/andmej/computer_graphics_challenges.