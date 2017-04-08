# COMP371

Group project with OpenGL in C++.

## Roadmap

- Seva
    - Project architecture
        - ~~Makefile~~
        - ~~Window class~~
        - ~~Shader class~~
        - ~~Camera class~~
        - ~~World class~~
        - ~~Abstract Mesh class~~
        - ~~Render modes~~
    - ~~Floating Camera controls~~
    - Procedurally generated terrain
        - ~~Grid~~
        - ~~Terrain height generation~~
        - Texture
        - Infinite (reload on advancement)
    
- Tarik
    - Add Skybox with a day/night cycle.
    - Add Eric's particle effects alongside Skybox
    - Add Terrain collision detection
    - Add object collision detection
    - (Optional) Add mini HUD
    - (Optional) Add fog 

- Eric
    - Particles
        - Falling
        - Cloud

- Sami
    - Generating objects
        - L-System

- Justin
    - Shadows

- Not assigned
    - Illumination
    - Mountains shadows
    - Proper user motions
        - Test and fix the camera see: World constructor FIXME tag
        - Draw axes pointing arrows which you can toggle on / off with a key
            - Note: this would enhance visual debugging
    - Water under certain elevation level
        - Reflection
    - Grass (multiple instantiations)
        - Wind influence

## Controls

Floating Camera:

    scroll      z-zoom
    arrows      rotate
    
    w           move forward
    s           move backward
    a           move left
    d           move right
    
    i           zoom in
    o           zoom out
    
    t           display triangles
    l           display lines
    p           display points

## Setup

### OSX

    make mac

### Arch Linux

Install these :

    sudo pacman -S glew glm glfw-x11 mesa-demos

Compile with :

    make linux

### GNU / Linux

Install the missing libs and compile with:

    make linux

## Coding Style

### Identation

It's a standard to use spaces over tabs. For readability, I recommend 4 spaces which is a widely used standard.

http://www.learncpp.com/cpp-tutorial/16-whitespace-and-basic-formatting/

## Help

### IRC

> Internet Relay Chat (IRC) is an application layer protocol that facilitates communication in the form of text.

The channel #opengl on the irc.freenode.net server is quite active!

### Links

[Modern OpenGL Tutorial Website](https://learnopengl.com)

[OpenGL Tutorial Videos](https://www.youtube.com/watch?v=6c1QYZAEP2M&list=PLRwVmtr-pp06qT6ckboaOhnm9FxmzHpbY)

[C++ Tutorial Website](http://www.learncpp.com)

[Getting Started with GLFW] (http://www.glfw.org/docs/latest/quick.html)

[GLEW](http://glew.sourceforge.net)

[OpenGL Math Library (GLM)](http://glm.g-truc.net/0.9.8/index.html)

[OGRE](http://www.ogre3d.org)

## Authors

| Name                   |  Email                       |
|:----------------------:|:----------------------------:|
| Tarik Abou-Saddik      | tarik.abousaddik@gmail.com   |
| Vsevolod (Seva) Ivanov | seva@tumahn.net              |
| Eric                   | ericchiassonmorgan@gmail.com |
| Sami					 | Sami@boubaker.me			    |
| Justin                 | zigman32@gmail.com           |
