//
//  Globals.h
//  Solar System Group
//
//  Created by Rajdeep Gill, Scott Smith, Mo M. , Minesh Varu
//

#ifndef Globals_h
#define Globals_h

#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#ifdef _WIN32
#include <windows.h>
#endif


#define PI 3.1415926535897932384626433832795
#define PIto180 PI/180

//extern float distanceScale;
float const distanceScale = 0.0009f;
extern float planetSizeScale;

const GLint slices = 30;
const GLint stacks = 30;

//Sun
const float sunOrbit = 1.0;
const float sunRotation = 24.47;
const float sunRadius = 695000.0;
const float sunToSun = 0.0;

//Planets
//inner solar system
//Mercury
const float mercuryOrbit = 87.97;
const float mercuryRotation = 58.65;
const float mercuryIncl = 7.00;
const float mercuryRadius = 2440.0;
const float mercuryToSun = 57910000.0 + sunRadius + mercuryRadius;
//Venus
const float venusOrbit = 224.70;
const float venusRotation = 116.75;
const float venusIncl = 3.39;
const float venusRadius = 6051.8;
const float venusToSun = 108200000.0 + sunRadius + venusRadius;
//Earth
const float earthOrbit = 365.26;
const float earthRotation = 1.0;
const float earthIncl = 0.0;
const float earthRadius = 6378.15;
const float earthToSun = 149600000.0 + sunRadius + earthRadius;
//Mars
const float marsOrbit = 686.98;
const float marsRotation = 1.03;
const float marsIncl = 1.85;
const float marsRadius = 3397.0;
const float marsToSun = 227940000.0 + sunRadius + marsRadius;
//outer solar system
//Jupiter
const float jupiterOrbit = 4332.71;
const float jupiterRotation = 0.4139;
const float jupiterIncl = 1.31;
const float jupiterRadius = 71492.0;
const float jupiterToSun = 778330000.0 + sunRadius + jupiterRadius;
//Saturn
const float saturnOrbit = 10759.50;
const float saturnRotation = 0.44375;
const float saturnIncl = 2.49;
const float saturnRadius = 60268.0;
const float saturnToSun = 1429400000.0 + sunRadius + saturnRadius;
//Uranus
const float uranusOrbit = 30685.00;
const float uranusRotation = 0.718056;
const float uranusIncl = 0.77;
const float uranusRadius = 25559.0;
const float uranusToSun = 2870990000.0 + sunRadius + uranusRadius;
//Neptune
const float neptuneOrbit = 60190.00;
const float neptuneRotation = 0.6708;
const float neptuneIncl = 1.77;
const float neptuneRadius = 24766.0;
const float neptuneToSun = 4504300000.0 + sunRadius + neptuneRadius;
//Pluto
const float plutoOrbit = 90550.0;
const float plutoRotation = 6.38718;
const float plutoIncl = 17.15;
const float plutoRadius = 1186.0;
const float plutoToSun = 5913520000.0 + sunRadius + plutoRadius;

//Satellites
//Moon
const float moonOrbit = 27.32;
const float moonRotation = 1;
const float moonIncl = 5.14;
const float moonRadius = 1739.0;
const float moonToEarth = 384400.0 + earthRadius + moonRadius;
//Phobos
const float phobosOrbit = 0.32;
const float phobosRotation = 1.0;
const float phobosIncl = 5.14;
const float phobosRadius = 11.1;
const float phobosToMars = (9378.0 + marsRadius + phobosRadius);
//Deimos
const float deimosOrbit = 1.26;
const float deimosRotation = 1.26;
const float deimosIncl = 1.80;
const float deimosRadius = 6.3;
const float deimosToMars = (23459.0 + marsRadius + deimosRadius);
//Io
const float ioOrbit = 1.77;
const float ioRotation = 1.77;
const float ioIncl = 0.04;
const float ioRadius = 1815.0;
const float ioToJupiter = 422000.0 + jupiterRadius + ioRadius;
//Europa europa
const float europaOrbit = 3.55;
const float europaRotation = 3.55;
const float europaIncl = 0.47;
const float europaRadius = 1569.0;
const float europaToJupiter = 670900.0 + jupiterRadius + europaRadius;
//Ganymede
const float ganymedeOrbit = 7.15;
const float ganymedeRotation = 7.15;
const float ganymedeIncl = 0.19;
const float ganymedeRadius = 2632.5;
const float ganymedeToJupiter = 1070000.0 + jupiterRadius + ganymedeRadius;
//Callisto
const float callistoOrbit = 16.69;
const float callistoRotation = 16.69;
const float callistoIncl = 0.28;
const float callistoRadius = 1200.0;
const float callistoToJupiter = 1883000.0 + jupiterRadius + callistoRadius;
//Charon
const float charonOrbit = 6.39;
const float charonRotation = 6.39;
const float charonIncl = 98.80;
const float charonRadius = 604.0;
const float charonToPluto = 19500.0 + plutoRadius + charonRadius;

// universe width for 2d
//const float universeWidth =
//const float universeHeight

#endif /* Globals_h */
