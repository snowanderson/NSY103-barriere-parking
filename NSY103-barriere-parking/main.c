//
//  main.c
//  NSY103-barriere-parking
//
//  Created by Maxime Chenot on 03/12/2014.
//  Copyright (c) 2014 Maxime Chenot. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>



void erreurSystemeFin(const char* msg,int valeur_retour)
{
    perror(msg);
    exit(valeur_retour);
}

int main(int argc, const char * argv[])
{
    /* exemple de réalisation de processus
       création d'un processus fils, lui même c'éant un processus fils.
     */
    
    pid_t pid;
    //const int nbarg = 1;
    int temps_s, res;
    int status;//, pid_fils;
    
    temps_s = (argc-1 == 1) ? atoi(argv[1]) : 0;
    
    switch (pid=fork()) {
        case (pid_t) -1 : erreurSystemeFin("",1);// break inutile
        case (pid_t)  0 :
            /* on est dans le processus fils */
            if (temps_s<0) sleep(-temps_s);
            printf("valeur de fork = %d \n",pid);
            printf("je suis le processus fils %d de pere %d\n",getpid(),getppid());
            printf("fin du processus fils\n");
            exit(0);
        default:		/* on est dans le processus pere */
            //wait(NULL);
            while((res=wait(&status)) != pid);    /* attente de terminaison de l'unique fils */
            /* cf aussi la primitive waitpid() */
            printf("valeur de fork = %d \n",pid);
            printf("je suis le processus pere %d de pere %d\n",getpid(),getppid());
            printf("fin du processus pere\n");
            exit(0);
    }
    return 0;
}
