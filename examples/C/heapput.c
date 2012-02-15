/*
 *
 * Copyright (c) 2011, 2012, University of Houston System and Oak Ridge National
 * Laboratory.
 * 
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 * o Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * 
 * o Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 * 
 * o Neither the name of the University of Houston System, Oak Ridge
 *   National Laboratory nor the names of its contributors may be used to
 *   endorse or promote products derived from this software without specific
 *   prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */



#include <stdio.h>
#include <assert.h>

#include <shmem.h>

long dest = -999;

int
main ()
{
  int *all;
  int me;

  start_pes (0);

  me = _my_pe ();

  if (me == 0)
    {
      long src = 4321;
      shmem_long_put (&dest, &src, 1, 1);
    }

  shmem_barrier_all ();

  printf ("%d: dest = %ld\n", me, dest);

#if 0
  all = (int *) shmalloc (sizeof (*all));
  assert (all != NULL);

  *all = 314159;
  shmem_barrier_all ();

  if (me == 1)
    {
      int send_to_all = 27182;
      shmem_int_put (all, &send_to_all, 1, 0);
    }

  shmem_barrier_all ();

  printf ("%d: all = %d\n", me, *all);

  shfree (all);
#endif

  return 0;
}
