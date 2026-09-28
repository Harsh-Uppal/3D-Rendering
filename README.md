<h1>3D Rendering</h1>
Built on OpenGL, this renderer offloads geometry and shading work to the GPU for real-time 3D graphics.
I made this project as I was curious about how the programs handle graphics at a deeper level.
This builds upto 3D rendering from scratch. There are C++ source files and GLSL shaders.
</br>
<h3>Demo:</h3>
</br>
<img width="446" height="450" alt="3d_rendering_demo" src="https://github.com/user-attachments/assets/f0057255-0e80-48a1-81c5-5a69a77bc444" />
</br>
<h3>How to build from source? (On Arch Linux)</h3>

- Clone the repository
- Install <a href="https://cmake.org"></a>CMake</a>
- Run the commands in the cloned directory:
  
`cmake -S . -B build`
`cmake --build build`

- Run the program:
  
`build/Rendered`
