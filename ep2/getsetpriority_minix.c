/*===========================================================================*
  *              do_getsetpriority                *
  *===========================================================================*/
PUBLIC int do_getsetpriority()
{
	int arg_which, arg_who, arg_pri;
	int rmp_nr;
	struct mproc *rmp;

	arg_which = m_in.m1_i1;
	arg_who = m_in.m1_i2;
	arg_pri = m_in.m1_i3;   /* for SETPRIORITY */

	/* Code common to GETPRIORITY and SETPRIORITY. */

	/* Only support PRIO_PROCESS for now. */
	if (arg_which != PRIO_PROCESS)
	    return(EINVAL);

	if (arg_who == 0)
	    rmp_nr = who_p;
	else
	    if ((rmp_nr = proc_from_pid(arg_who)) < 0)
	        return(ESRCH);

	rmp = &mproc[rmp_nr];

	if (mp->mp_effuid != SUPER_USER &&
	   mp->mp_effuid != rmp->mp_effuid && mp->mp_effuid != rmp->mp_realuid)
	    return EPERM;

	/* If GET, that's it. */
	if (call_nr == GETPRIORITY) 
	    return(rmp->mp_nice - PRIO_MIN);

	/* Only root is allowed to reduce the nice level. */
	if (rmp->mp_nice > arg_pri && mp->mp_effuid != SUPER_USER)
	    return(EACCES);
	
	/* We're SET, and it's allowed. Do it and tell kernel. */
	rmp->mp_nice = arg_pri;
	 return sys_nice(rmp->mp_endpoint, arg_pri);
}