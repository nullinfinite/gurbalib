inherit M_COMMAND;

void usage(void) {
   string *lines;

   lines = ({ "Usage: set [-h] [VAR VALUE]" });
   lines += ({ " " });
   lines += ({ "Set an environment variable VAR to VALUE." });
   lines += ({ "If no VAR VALUE pair is given print your current environment."
      });
   lines += ({ "Some variables you can set:" });
   lines += ({ "\tstart\t\tyour starting room." });
   lines += ({ "\theight\t\theight of your screen." });
   lines += ({ "\twidth\t\twidth of your screen." });
   lines += ({ "\tprompt\t\tYour prompt." });
   lines += ({ "\thidden\t\tSet to 1 if you want to hide your login from " +
      "users." });
   lines += ({ "\tautoload\tSet to 1 if you want to save your equipment on " +
      "quit." });
   lines += ({ "\tsave_on_quit\tSet to 1 if you want to start where you last " +
      "quit." });
   lines += ({ "\tquit_message\tSet your quit message.  Example: $N $vquit." });
   lines += ({ "\tdebug_commands\tSet to 1 if you want debugging of commands."
	});
   lines += ({ "\tverbose_errors\tSet to 1 if you want longer error codes." });
   lines += ({ "\tdisplay_caught\tSet to 1 if you want to show caught " +
      "runtime errors." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tset width 50" });
   lines += ({ "\tset save_on_quit 1" });
   lines += ({ "See also:" });
   lines += ({ "\tunset" });

   this_player()->more(lines);
}

void list_vars(void) {
   string name, *names;
   int i;

   names = this_player()->query_env_indices();
   for (i = 0; i < sizeof(names); i++) {
      out_unmod(names[i] + "=" + this_player()->query_env(names[i]) + "\n");
   }
}

static void main(string str) {
   string name, value;
   int i;

   if (empty_str(str)) {
      list_vars();
   } else if (sscanf(str, "-%s", str)) {
      usage();
      return;
   } else if ((sscanf(str, "%s %s", name, value) != 2) &&
      (sscanf(str, "%s=%s", name, value) != 2)) {
      usage();
      return;
   } else {
      if (str2val(value) != -1) {
	 /* We've got a value */
	 this_player()->set_env(name, str2val(value));
      } else {
	 this_player()->set_env(name, value);
      }
   }
}
