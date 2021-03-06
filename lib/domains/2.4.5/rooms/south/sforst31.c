#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area("2.4.5");

   set_short("A dimly lit forest");
   set_long("You are in part of a dimly lit forest.  " +
      "Trails lead north, south and east.");

   add_exit("north",DIR + "/rooms/south/sshore19.c");
   add_exit("south", DIR + "/rooms/south/sforst32.c");
   add_exit("east", DIR + "/rooms/south/sshore18.c");
}
