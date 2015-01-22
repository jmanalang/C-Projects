Please open this file using NotePad++ or Vim

Project: DECOY Project 1
Author: Jules Manalang 2014
email: julesman@buffalo.edu

README
Project Objectives: Create software which handles a group of drones in a way that 
they do not collide with one another 


Files Included: 
	drone.c 	  - Source code 
	makefile	  - A makefile to compile the source code using gcc compiler
	droneStart    - The executable file 
	Documentation - Finite state diagrams, along with implementation details, etc.
	README        - This file

Compilation:
	In the directory of the makefile, enter "make -f makefile"
	This will output the executable droneStart

Usage:
	To use the executable, enter "./droneStart <takeoff> <landing> <stations>" 
		- Please make sure that there is 1 space in between ./droneStart, 
			<takeoff>, <landing>, and <stations>.
			
		<takeoff> - denotes the number of drones that you would like to takeoff from
			the ground. This ranges from 0 to any positive integer.
			
		<landing> - denotes the number of drones that you would like to land. 
			This number ranges from 0 to any positive integer.
			
		<stations> - denotes how many available stations the drones can land into.
			This numbe rages from 1 to any positive integer as there needs to be at least
			1 station that  drones can land into. 