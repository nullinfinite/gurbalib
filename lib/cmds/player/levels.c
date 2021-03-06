inherit M_COMMAND;

void usage(void) {
   string *lines;

   lines = ({ "Usage: levels [-h]" });
   lines += ({ "" });
   lines += ({ "Displays a list of the various levels and requirements." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tlevels" });
   lines += ({ "See also:" });
   lines += ({ "\thp, inventory, junk, score, skills" });

   this_player()->more(lines);
}

static void main(string str) {
   string bar, title;
   int i, exp, width, level;

   if (!empty_str(str)) {
      usage();
      return;
   }

   width = this_player()->query_width();

   bar = "";
   for (i = 0; i < width; i++) {
      bar += "-";
   }

   write("LEVEL:   EXP     : Title");
   write(bar + "\n");

   level = this_player()->query_level();

   for (i = 0; i < 20; i++) {
      exp = i * i * 2000;
      title = this_player()->query_level_title(i + 1);
      if ((i+ 1 == level) || ((level >= 20) && (i == 19))) {
         write((i + 1) + " *\t" + exp + "\t" + title);
      } else {
         write((i + 1) + "\t" + exp + "\t" + title);
      }
   }
}
