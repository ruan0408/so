PUBLIC void ep2_dmp()
{
  register struct proc *rp;
  static struct proc *oldrp = BEG_PROC_ADDR;
  register struct priv *sp;
  static char ipc_to[NR_SYS_PROCS + 1 + NR_SYS_PROCS/8];
  int r, i,j, n = 0;

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
   
  /*printf("\n--nr-id-name---- -flags- -traps- -ipc_to mask------------------------ \n");*/
  printf("\n--nome-id- -prioridade- -tempo_sistema- -end_pilha \n");

  for (rp = oldrp; rp < END_PROC_ADDR; rp++) 
  {
    if (isemptyp(rp)) continue;
    if (++n > 23) break;
    /*if (proc_nr(rp) == IDLE)        printf("(%2d) ", proc_nr(rp));  
    else if (proc_nr(rp) < 0)       printf("[%2d] ", proc_nr(rp));
    else                            printf(" %2d  ", proc_nr(rp));*/
    r = -1;
    for (sp = &priv[0]; sp < &priv[NR_SYS_PROCS]; sp++) 
      if (sp->s_proc_nr == rp->p_nr) { r ++; break; }

    if (r == -1 && ! (rp->p_rts_flags & SLOT_FREE)) 
    {
      sp = &priv[USER_PRIV_ID];
    }
    /*printf("(%02u) %-7.7s %s   %s  ",sp->s_id, rp->p_name, s_flags_str(sp->s_flags), s_traps_str(sp->s_trap_mask));*/
    printf("%-7.7s (%02u) %c %lu  ",rp->p_name, sp->s_id, rp->p_priority, rp->p_sys_time /*end_pilha*/);
    /*for (i=j=0; i < NR_SYS_PROCS; i++, j++) 
    {
      ipc_to[j] = get_sys_bit(sp->s_ipc_to, i) ? '1' : '';
      if (i % 8 == 7) ipc_to[++j] = ' ';
    }
    ipc_to[j] = '\0';

    printf(" %s \n", ipc_to);*/
  }
  if (rp == END_PROC_ADDR) 
    rp = BEG_PROC_ADDR; 
  else 
    printf("--more--\r");
  oldrp = rp;
   
}