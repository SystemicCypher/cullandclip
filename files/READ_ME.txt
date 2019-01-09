===============================================
CPSC 486 - Cull and Clip Program
===============================================
----------------------------
Section
----------------------------
CPSC 486-01 13179 

----------------------------
Group Letters
----------------------------
AUR

----------------------------
Group Members
----------------------------
Austin Loza austinloza@csu.fullerton.edu
Richard Ung rung921@csu.fullerton.edu


----------------------------
Introduction
----------------------------
This project takes a formatted input from standard input that specifies a model, camera, triangles, bags, and world placement positions.
The camera will generate view frustrum planes and associated points. The triangles that were loaded from the input file
will then be culled and clipped to the specified camera. 

----------------------------
Instructions For Building and Running
----------------------------
Compile by entering the directory in a shell terminal and type make.
Once the program has compiled, then run with:
	./cullclip < {input data}
Or you can pipe the output of another program into cullclip


----------------------------
Extra Features 
----------------------------
None.

----------------------------
Bugs
----------------------------
While the math appears to be sound, the program seems to only claim that all triangles need to be culled.
