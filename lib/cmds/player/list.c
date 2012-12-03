void usage() {
   string *lines;

   lines = ({ "Usage: list [-h]" });
   lines += ({ "When in a storage location, allows you to see what you " +
      "have in storage." });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tlist" });
   lines += ({ "See also: buy, identify, look, retrieve, sell, store, value" });

   this_player()->more(lines);
}

void main(string str) {
   object vendor;
   object *objs;
   int i;

   if (str && str != "") {
      usage();
      return;
   }

   if (this_environment()->is_storage()) {
      write(this_environment()->query_stored_list());
   } else {

      objs = this_environment()->query_inventory();

      for (i = 0; i < sizeof(objs); i++) {
	 if (objs[i]->is_vendor())
	    vendor = objs[i];
      }
      if (!vendor) {
	 write("Perhaps you should try to do this somewhere else?");
	 return;
      }

      vendor->do_list(this_player());
   }
}
