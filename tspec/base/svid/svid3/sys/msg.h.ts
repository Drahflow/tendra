# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "svid/svid3", "", "config" ;
+IF %% __SYSV_KERNEL_EXTENSION %%

+USE "svid/svid3", "sys/types.h.ts" ;
+USE "svid/svid3", "sys/ipc.h.ts" ;
+IMPLEMENT "cae/xpg3", "sys/msg.h.ts";

+ENDIF
