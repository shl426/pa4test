/*
* Test case 4 - Stress test for PA4
* 
* Created by: Vijay Venkataraman
* Created on: November 24, 2013
*
* Modified by: Angie Nguyen
* Modified on: March 3, 2015
*
*/

#include "aux.h"
#include "umix.h"
#include "mythreads.h"
#include "string.h"

#define NUMYIELDS	10

static int square, cube;	/* global variables, shared by threads */

/** pointer to functions so I'll only need one type of func call */
static void (*init)();
static int (*spawn)();
static int (*yield)(int);
static int (*get)();
static void (*exitThread)();
static void (*sched)();

void Main (argc, argv)
     int argc;
     char** argv;
{

  int i, t, me, temp;
  void printSquares (), printCubes ();

  init = &MyInitThreads;
  spawn = &MyCreateThread;
  yield = &MyYieldThread;
  get = &MyGetThread;
  exitThread = &MyExitThread;
  sched = &MySchedThread;

  init ();

  me = get ();
  t = spawn (printSquares, me);
  t = spawn (printCubes, t);

  t = spawn (printSquares, t);
  t = spawn (printCubes, me);
  t = spawn (printSquares, me);
  t = spawn (printSquares, 3);
  
 
  t = spawn (printSquares, t);
  t = spawn (printCubes, t-1);
  t = spawn (printSquares, t+1);
  yield(t); 
  for (i = 0; i < 5; i++) {
    temp = yield (i%3);
    Printf ("T%d: square = %d, cube = %d, Yield returns = %d\n", me, square, cube, temp);
    sched ();
  }

  Printf ("T%d has died\n", get ());
  exitThread ();
}

void printSquares (t)
     int t;				
{
  int i;

  for (i = 0; i < get (); i++) {
    square = i * i;
    Printf ("T%d: %d squared = %d\n", get (), i, square);
   sched(); 
  }

  sched ();
  Printf ("T%d has died\n", get ());
}

void printCubes (t)
     int t;				
{
  int i;

  for (i = 0; i < get (); i++) {
    cube = i * i * i;
    Printf ("T%d: %d cubed = %d\n", get (), i, cube);
    
	  
}

  
  Printf ("T%d has died\n", get ());
   
}
