inherit M_COMMAND;

void usage(void) {
   string *lines;

   lines = ({ "Usage: buy [-h] OBJ" });
   lines += ({ "" });
   lines += ({ "Allows you to buy an object OBJ, " +
      "assuming you are near a shop keeper." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tbuy sword" });
   lines += ({ "\tbuy helmet" });
   lines += ({ "See also:" });
   lines += ({ "\textinguish, identify, light, list, listen, look, " +
      "search, sell, value" });

   if (query_wizard(this_player())) {
      lines += ({ "\tlast, locate, mudlist, possess, rwho, snoop, where, who"
         });
   }

   this_player()->more(lines);
}

/* Created by Fudge */

static void main(string str) {
   object *objs;
   int i;

   if (empty_str(str)) {
      usage();
      return;
   }
   if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   if (this_player()->is_dead()) {
      write("You can not do that when your are not among the living.\n");
      return;
   }

   objs = this_environment()->query_inventory();
   for (i = 0; i < sizeof(objs); i++) {
      if (objs[i]->is_vendor() == 1) {
         /* Found the shopkeeper */

         objs[i]->do_sell(this_player(), str);
         return;
      }
   }

   write("Buy from whom?");
}
