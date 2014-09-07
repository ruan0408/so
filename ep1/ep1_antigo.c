int main()
{
	while(1)
	{
		int i = -1;
		char comando[1000];
		char* args[1000];

		printf("$ ");
		fgets(comando, sizeof(comando), stdin);
		//if(feof(stdin)) break;

	  	args[++i] = strtok (comando, " \n");

	  	while (args[i] != NULL)
	    		args[++i] = strtok (NULL, " \n");

		if(strcmp(args[0], "protegepracaramba") == 0)
			chmod(args[1], 0000);

		if(strcmp(args[0], "liberageral") == 0)
			chmod(args[1], 0777);	

		if(strcmp(args[0], "rodeveja") == 0)
		{
			int ret;
			int pid = fork();
			if(pid != 0)
				waitpid(pid, &ret,0);
			else
				execve(args[1], args+1, 0);

			printf("$ O programa '%s' retornou com codigo %d\n", args[1], ret);
		}

		if(strcmp(args[0], "rode") == 0)
			if(fork() == 0) 
			{
				execve(args[1], args+1, 0);
			}
	}

	return 0;