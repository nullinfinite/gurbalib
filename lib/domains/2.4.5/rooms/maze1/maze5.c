#include "../../domain.h"
#include "maze.h"
inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("End of the maze");
   set_long("Congratulations you have done it.");

   add_exit("south", DIR + "/rooms/maze1/maze4.c");

   set_objects (DIR + "/obj/leather.c");
}
