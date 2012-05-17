object lock;
string name;

void usage() {
   write("Usage: rmuser [-h] USER\n");
   write("Delete the specified user, USER.\n");
   write("If they are a wizard or admin it will prompt you to remove their " +
      "wiz dir.\n");
   write("Options:\n");
   write("\t-h\tHelp, this usage message.\n");
   write("See also: ban, muzzle, forcequit, zap\n");
}

static void rmuser(string name) {
   USER_D->delete_user(name);
}

void confirm_remove(string str) {
   string dirname;
   if (!lock || previous_object() != lock) {
      return;
   }

   if (!str || str == "") {
      this_player()->input_to_object(this_object(), "confirm_remove");
      write("Removing " + name + ", are you sure? (y/n)");
      return;
   }
   switch (lowercase(str[0..0])) {
      case "y":
	 rmuser(name);
	 write("Ok.");
	 dirname = "/wiz/" + name;
	 if (file_exists(dirname) == -1) {
	    write("You may also want to remove their wiz dir: " + dirname +
	       "\n");
	 }
	 break;
      default:
	 write("Aborted.");
	 break;
   }
   name = nil;
   lock = nil;
}

void main(string str) {
   if (!str || str == "") {
      usage();
      return;
   }

   if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   if (!require_priv("system")) {
      write("You must be admin to do that.");
      return;
   }
   name = lowercase(str);

   if (this_player()->query_name() == str) {
      write("You may not remove yourself.\n");
      return;
   }

   if (!USER_D->user_exists(str)) {
      write("No such user: " + str + "\n");
      return;
   }

   if (lock) {
      write(lock->query_name() + " is currently using this command.");
      return;
   }

   lock = this_player();
   confirm_remove("");
}
