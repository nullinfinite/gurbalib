#include <type.h>

string *compose_message(object who, string msg, object target,
   varargs mixed * objs) {
   string *words;
   string us, them, others;
   int punc, i, objnum;

   words = explode(msg, " ");
   us = "";
   them = "";
   others = "";
   for (i = 0; i < sizeof(words); i++) {
      if (words[i] == "")
	 continue;

      if (words[i][0] == '$' && strlen(words[i]) >= 2) {

	 if (words[i][strlen(words[i]) - 1] == '.' ||
	    words[i][strlen(words[i]) - 1] == ',' ||
	    words[i][strlen(words[i]) - 1] == '!' ||
	    words[i][strlen(words[i]) - 1] == '?') {
	    punc = words[i][strlen(words[i]) - 1];
	    words[i] = words[i][..strlen(words[i]) - 2];
	 } else {
	    punc = 0;
	 }

	 switch (words[i][1]) {
	    case 'N':
	       if (who->is_living()) {
		  if (!who->query_proper_name()) {
		     us += "you ";
		     them += "the " + who->query_id() + " ";
		     others += "the " + who->query_id() + " ";
		  } else {
		     us += "you ";
		     them += who->query_proper_name() + " ";
		     others += who->query_proper_name() + " ";
		  }
	       } else {
		  us += "you ";
		  them += "the " + who->query_id() + " ";
		  others += "the " + who->query_id() + " ";
	       }
	       break;
	    case 'n':
	       us += "you ";
	       them += who->query_gender_pronoun() + " ";
	       others += who->query_gender_pronoun() + " ";
	       break;
	    case 'p':
	       us += "your ";
	       them += who->query_gender_possessive() + " ";
	       others += who->query_gender_possessive() + " ";
	       break;
	    case 'v':
	       if (strlen(words[i]) < 3)
		  break;
	       us += words[i][2..] + " ";
	       if (words[i][2..] == "are") {
		  them += "is ";
		  others += "is ";
	       } else if (words[i][2..] == "say:") {
		  them += "says: ";
		  others += "says: ";
	       } else if (words[i][2..] == "ask:") {
		  them += "asks: ";
		  others += "asks: ";
	       } else if (words[i][2..] == "remark:") {
		  them += "remarks: ";
		  others += "remarks: ";
	       } else if (words[i][2..] == "mumble:") {
		  them += "mumble: ";
		  others += "mumble: ";
	       } else if (words[i][2..] == "shout:") {
		  them += "shouts: ";
		  others += "shouts: ";
	       } else if (words[i][2..] == "ponder:") {
		  them += "ponders: ";
		  others += "ponders: ";
	       } else if (words[i][2..] == "whisper:") {
		  them += "whispers: ";
		  others += "whispers: ";
	       } else if (words[i][2..] == "exclaim:") {
		  them += "exclaims: ";
		  others += "exclaims: ";
	       } else if (words[i][2..] == "mutter:") {
		  them += "mutters: ";
		  others += "mutters: ";
	       } else if (words[i][2..] == "say") {
		  them += "says ";
		  others += "says ";
	       } else if (words[i][strlen(words[i]) - 1] == 'o') {
		  them += words[i][2..] + "es ";
		  others += words[i][2..] + "es ";
	       } else if (words[i][strlen(words[i]) - 1] == 'h' &&
		  words[i][strlen(words[i]) - 2] != 'g') {
		  them += words[i][2..] + "es ";
		  others += words[i][2..] + "es ";
	       } else if (words[i][strlen(words[i]) - 1] == 'y') {
		  them += words[i][2..strlen(words[i]) - 2] + "ies ";
		  others += words[i][2..strlen(words[i]) - 2] + "ies ";
	       } else if (words[i][strlen(words[i]) - 1] == 's') {
		  them += words[i][2..] + "es ";
		  others += words[i][2..] + "es ";
	       } else {
		  them += words[i][2..] + "s ";
		  others += words[i][2..] + "s ";
	       }
	       break;
	    case 'T':
	       if (who == target) {
		  /* Doing something to ourselves. */
		  us += "yourself ";
		  them += who->query_gender_reflexive() + " ";
		  others += who->query_gender_reflexive() + " ";
	       } else {
		  if (target->is_living()) {
		     if (!target->query_proper_name()) {
			us += "the " + target->query_id() + " ";
			them += "you ";
			others += "the " + target->query_id() + " ";
		     } else {
			us += target->query_proper_name() + " ";
			them += "you ";
			others += target->query_proper_name() + " ";
		     }
		  } else {
		     us += "the " + target->query_id() + " ";
		     them += "you " + target->query_id() + " ";
		     others += "the " + target->query_id() + " ";
		  }
	       }
	       break;
	    case 't':
	       if (who == target) {
		  /* Doing something to ourselves. */
		  us += "yourself ";
		  them += who->query_gender_reflexive() + " ";
		  others += who->query_gender_reflexive() + " ";
	       } else {
		  if (target->is_living()) {
		     if (!target->query_proper_name()) {
			us += "the " + target->query_id() + " ";
			them += "you ";
			others += "the " + target->query_id() + " ";
		     } else {
			us += target->query_proper_name() + " ";
			them += "you ";
			others += target->query_proper_name() + " ";
		     }
		  } else {
		     us += "the " + target->query_id() + " ";
		     them += "you " + target->query_id() + " ";
		     others += "the " + target->query_id() + " ";
		  }
	       }
	       break;
	    case 'o':
	       if (strlen(words[i]) > 2 && words[i][2] >= '0'
		  && words[i][2] <= '9') {
		  objnum = words[i][2] - '0';
	       } else {
		  objnum = 0;
	       }
	       if (!objs || !objs[objnum])
		  break;
	       if (typeof(objs[objnum]) == T_STRING) {
		  us += objs[objnum] + " ";
		  them += objs[objnum] + " ";
		  others += objs[objnum] + " ";
	       } else {
		  us += "the " + objs[objnum]->query_id() + " ";
		  them += "the " + objs[objnum]->query_id() + " ";
		  others += "the " + objs[objnum]->query_id() + " ";
	       }

	       break;
	 }
	 if (punc) {
	    us[strlen(us) - 1] = punc;
	    them[strlen(them) - 1] = punc;
	    others[strlen(others) - 1] = punc;
	    us += " ";
	    them += " ";
	    others += " ";
	 }
      } else {
	 us += words[i] + " ";
	 them += words[i] + " ";
	 others += words[i] + " ";
      }
   }
   if (us[strlen(us) - 1] == ' ') {
      /* We need to strip the final space. */
      us = us[..strlen(us) - 2];
      them = them[..strlen(them) - 2];
      others = others[..strlen(others) - 2];
   }

   return (( { us, them, others } ));
}

void simple_action(string msg, varargs mixed objs ...) {
   string *result;
   object sp;

   sp = this_player();
   set_this_player(this_object());

   catch {
      result = compose_message(this_player(), msg, nil, objs);
      this_environment()->tell_room(this_object(), result[2]);
      write(capitalize(result[0]));
      set_this_player(sp);
   }:{
      set_this_player(sp);
      rethrow();
   }
}

void targetted_action(string msg, object target, varargs mixed objs ...) {
   string *result;

   result = compose_message(this_player(), msg, target, objs);
   this_environment()->tell_room(this_player(), result[2], target);
   this_object()->message(capitalize(result[0]));
   if (target && target->is_living() && target != this_player()) {
      target->message(capitalize(result[1]));
      target->outside_message(capitalize(result[1]));
   }
}

void other_action(object who, string msg, object target, varargs mixed objs ...) {
   string *result;

   result = compose_message(who, msg, target, objs);
   if (!this_object()->query_environment())
      return;
   this_object()->query_environment()->tell_room(who, result[2], target);
   /*  who->write( capitalize( result[0] ) ); */
   if (target && target->is_living() && target != who) {
      target->message(capitalize(result[1]));
   }
}
