# the-cherno
My code-along for TheCherno tutorials.

**THIS PORT IS STILL A WORK IN PROGRESS**
## Episodes ported
* ep02

The code here is intended to run on Linux. If you want to compile on MacOS, see the corresponding branch named MacOS.
For Windows you will need to come up with a different build system on your own.

Any differences between TheCherno's code and mine is likely a result of my compilation environment.
YMMV.

The repo has been reworked to use meson/ninja.
To compile any episode, cd to that directory and run `make`.
To run the resulting app, run `make run`.

All episodes compile into a binary named **app**.

I chose to install glfw , glew and glut dependencies via package manager instead of moving them into the repo. To get those, run:

    sudo apt install libglfw3-dev freeglut3-dev libglew-dev

At some point, I may bring those libraries in or try to add them as meson subprojects.

Currently working through [TheCherno's OpenGL tutorial](https://www.youtube.com/watch?v=W3gAzLwfIP0&list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2 "TheCherno OpenGL Tutorial").

See all of his videos [here](https://www.youtube.com/channel/UCQ-W1KE9EYfdxhL6S4twUNw "TheChernoProject").

Support him on [his Patreon page](https://www.patreon.com/thecherno/overview "TheCherno Patreon") if you want to see more!
