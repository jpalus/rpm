/* Return dynamic tag name.
   Copyright (C) 2001, 2002 Red Hat, Inc.
   Written by Ulrich Drepper <drepper@redhat.com>, 2001.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License version 2 as
   published by the Free Software Foundation.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software Foundation,
   Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <inttypes.h>
#include <stdio.h>
#include <libeblP.h>


const char *
ebl_dynamic_tag_name (ebl, tag, buf, len)
     Ebl *ebl;
     int64_t tag;
     char *buf;
     size_t len;
{
  const char *res = ebl != NULL ? ebl->dynamic_tag_name (tag, buf, len) : NULL;

  if (res == NULL)
    {
      if (tag >= 0 && tag < DT_NUM)
	{
	  static const char *stdtags[] =
	    {
	      "NULL", "NEEDED", "PLTRELSZ", "PLTGOT", "HASH", "STRTAB",
	      "SYMTAB", "RELA", "RELASZ", "RELAENT", "STRSZ", "SYMENT",
	      "INIT", "FINI", "SONAME", "RPATH", "SYMBOLIC", "REL", "RELSZ",
	      "RELENT", "PLTREL", "DEBUG", "TEXTREL", "JMPREL", "BIND_NOW",
	      "INIT_ARRAY", "FINI_ARRAY", "INIT_ARRAYSZ", "FINI_ARRAYSZ",
	      "RUNPATH", "FLAGS", "ENCODING", "PREINIT_ARRAY",
	      "PREINIT_ARRAYSZ"
	    };

	  res = stdtags[tag];
	}
      else if (tag == DT_VERSYM)
	res = "VERSYM";
      else if (tag >= DT_GNU_PRELINKED && tag <= DT_SYMINENT)
	{
	  static const char *valrntags[] =
	    {
	      "GNU_PRELINKED", "GNU_CONFLICTSZ", "GNU_LIBLISTSZ",
	      "CHECKSUM", "PLTPADSZ", "MOVEENT", "MOVESZ", "FEATURE_1",
	      "POSFLAG_1", "SYMINSZ", "SYMINENT"
	    };

#if defined(__x86_64__)
	  int ix = tag - DT_GNU_PRELINKED;
	  res = valrntags[ix];
#else
	  res = valrntags[tag - DT_GNU_PRELINKED];
#endif
	}
      else if (tag >= DT_GNU_CONFLICT && tag <= DT_SYMINFO)
	{
	  static const char *addrrntags[] =
	    {
	      "GNU_CONFLICT", "GNU_LIBLIST", "CONFIG", "DEPAUDIT", "AUDIT",
	      "PLTPAD", "MOVETAB", "SYMINFO"
	    };

#if defined(__x86_64__)
	  int ix = tag - DT_GNU_CONFLICT;
	  res = addrrntags[ix];
#else
	  res = addrrntags[tag - DT_GNU_CONFLICT];
#endif
	}
      else if (tag >= DT_RELACOUNT && tag <= DT_VERNEEDNUM)
	{
	  static const char *suntags[] =
	    {
	      "RELACOUNT", "RELCOUNT", "FLAGS_1", "VERDEF", "VERDEFNUM",
	      "VERNEED", "VERNEEDNUM"
	    };

#if defined(__x86_64__)
	  int ix = tag - DT_RELACOUNT;
	  res = suntags[ix];
#else
	  res = suntags[tag - DT_RELACOUNT];
#endif
	}
      else if (tag == DT_AUXILIARY)
	res = "AUXILIARY";
      else if (tag == DT_FILTER)
	res = "FILTER";
      else
	{
	  snprintf (buf, len, gettext ("<unknown>: %" PRId64), tag);

	  res = buf;

	}
    }

  return res;
}
