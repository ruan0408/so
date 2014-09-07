PUBLIC void ep2_dmp()
{
  register struct proc *rp;
  static struct proc *oldrp = BEG_PROC_ADDR;
  register struct priv *sp;
  static char ipc_to[NR_SYS_PROCS + 1 + NR_SYS_PROCS/8];
  int r, i, j, k, n = 0;

/* First obtain a fresh copy of the current process and system table. */
  if ((r = sys_getprivtab(priv)) != OK) 
  {
    report("IS","warning: couldn't get copy of system privileges table", r);
    return;
  }
  if ((r = sys_getproctab(proc)) != OK) 
  {
    report("IS","warning: couldn't get copy of process table", r);
    return;
  }
   
  printf("\n--nome-id- -prioridade- -tempo_sistema- -end_pilha \n");

  for(k = 0; k < 16; k++)
    for (rp = oldrp; rp < END_PROC_ADDR; rp++) 
    {
      if (rp->p_priority != k) continue;
      if (isemptyp(rp)) continue;
      if (++n > 23) break;
      
      r = -1;
      for (sp = &priv[0]; sp < &priv[NR_SYS_PROCS]; sp++) 
        if (sp->s_proc_nr == rp->p_nr) { r ++; break; }

      if (r == -1 && ! (rp->p_rts_flags & SLOT_FREE)) 
      {
        sp = &priv[USER_PRIV_ID];
      }
      printf("%-7.7s (%02u) %c %lu  ",rp->p_name, sp->s_id, rp->p_priority, rp->p_sys_time /*end_pilha*/);
    }
  if (rp == END_PROC_ADDR) 
    rp = BEG_PROC_ADDR;
  else
    printf("--more--\r");
  oldrp = rp;
   
}