Modkit Micro Framework
=====

###Project 
The Modkit Micro Framework is an open source programming and debugging  framework for a wide range of microcontrollers.  The Modkit Micro Framework provides threading/event support for building responsive embedded systems and has a dual C/C++ API.  A comprehensive and consistent component library simplifies adding components to projects and sharing them across users with logically similar but physically different hardware components.

###Team
The Modkit Micro Framework is developed by Modkit along with key partners and individual collaborators.  All focused efforts towards the projects goals are welcome.

###Related Projects
The Modkit Micro Framework was originally developed to support Modkit’s graphical programming tools.  The Modkit Micro Framework is currently in use by Modkit for VEX and planned for use in Modkit Micro.  Other planned uses are Modkit Micro Classic, and the open source Open Micro editor.  The Modkit Micro Framework was originally conceived and developed by Modkit as Wiring++ and requires an implementation of the Wiring Framework, developed separately by Hernando Barragan and the Wiring Team.

###Note on Program Structure
While Wiring++ proposed the void events(){ … } and void threads(){ … }  syntax,  the final Modkit Micro Framework syntax is slightly different.  And while void setup(){ … } and void loop(){ … } are not officially supported by the Modkit Micro Framework, it is possible for the traditional Wiring syntax to be mixed with Modkit Micro threads and events in a single program.  The “threads” and “events” keywords denote the primary Modkit Micro Framework programming structures. Notice the “with” keyword to setup the scope for the thread or event handler.  Events are the most basic programming structure:

```
events {
  when(START) {
    with(LED1);
    forever {
      toggle();
      delay(1000);
    }
  }
}
```
  
Threads are a slightly more advanced concept.  Threads must be started by another thread or event handler.  In this case they are started on startup:
```
threads{
   thread(THREAD_NAME){
     forever{
        //do something
     }
   }
}

events {
  when(START) {  
    THREAD_NAME.start(); 
  }
}

```

###Micro Framework Editors
The Modkit Micro Framework is developed separately from any microcontroller source code editor while it is designed to be supported/embedded by a variety of source code editors.  While Modkit Micro and Modkit for VEX build on the framework to provide compelling graphical programming tools, Modkit also plans to develop both proprietary (Modkit Micro Classic) and open source (Open Micro) source code editors that expose the framework directly. 


###Using as an Arduino Library
1. Install https://github.com/Modkit/WiringPlusPlus as a Library (see readme)
2. Copy Micro Directory to Arduino Libraries folder.
3. #include \<micro.h\>
4. #include \<wpp.h\>
5. use threading/events (see Program Structure above)
