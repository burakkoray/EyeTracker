Eye Tracker
===========

This project was made for CSE396 ProjectII course at Gebze Institute of Technology.

How to run the project on Windows
----------------------------------
- Open Win32 folder
- Open Debug or Release folder
- Run Eye Tracker.exe

How to run the project on Linux
----------------------------------
You should install required libraries to compile and run the project on your Linux machine.

- OpenCV 2.4.9.0

- Qt 4.8.5 


After installation is completed, follow these steps to compile and run the project:
------------------------------------------------------------------------------------
- Go to project directory
- Run the following command to create a pro file (this is needed only for the first time):
	qmake -project
- Add the following lines to the <project-dir-name>.pro file:
	INCLUDEPATH += /usr/local/include/opencv 
	LIBS += -L/usr/local/lib 
	LIBS += -lopencv_core 
	LIBS += -lopencv_imgproc 
	LIBS += -lopencv_highgui 
	LIBS += -lopencv_ml 
	LIBS += -lopencv_video 
	LIBS += -lopencv_features2d 
	LIBS += -lopencv_calib3d 
	LIBS += -lopencv_objdetect 
	LIBS += -lopencv_contrib 
	LIBS += -lopencv_legacy 
	LIBS += -lopencv_flann 
	LIBS += -lopencv_nonfree

- Run qmake to create a makefile for your project.
- Run make to compile and link your project.
- Run ./<project-dir-name> to run your project.
