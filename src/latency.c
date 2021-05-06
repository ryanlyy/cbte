/*
 * latency -- measure the scheduling latency of a particular process from
 *	the extra information provided in /proc/<pid>stat by version 4 of
 *	the schedstat patch. PLEASE NOTE: This program does NOT check to
 *	make sure that extra information is there; it assumes the last
 *	three fields in that line are the ones it's interested in.  Using
 *	it on a kernel that does not have the schedstat patch compiled in
 *	will cause it to happily produce bizarre results.
 *
 *	Note too that this is known to work only with versions 4 and 5
 *	of the schedstat patch, for similar reasons.
 *
 *	This currently monitors only one pid at a time but could easily
 *	be modified to do more.
 */
#include <stdio.h>
#include <getopt.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

extern char *index(), *rindex();
char procbuf[512];
char statname[64];
char *Progname;
FILE *fp;

void usage()
{
    fprintf(stderr,"Usage: %s [-s sleeptime ] <pid>\n", Progname);
    exit(-1);
}

/*
 * get_stats() -- we presume that we are interested in the first three
 *	fields of the line we are handed, and further, that they contain
 *	only numbers and single spaces.
 */

/*
/proc/<pid>/schedstat
----------------
schedstats also adds a new /proc/<pid>/schedstat file to include some of
the same information on a per-process level.  There are three fields in
this file correlating for that process to:
     1) time spent on the cpu
     2) time spent waiting on a runqueue
     3) # of timeslices run on this cpu
*/

void get_stats(char *buf, unsigned long long *run_ticks, unsigned long long *wait_ticks,
    unsigned long long *nran)
{
    char *ptr;

    /* sanity */
    if (!buf || !run_ticks || !wait_ticks || !nran)
	return;

    /* leading blanks */
    ptr = buf;
    while (*ptr && isblank(*ptr))
	ptr++;

    /* first number -- run_ticks */
    *run_ticks = atoll(ptr);
    while (*ptr && isdigit(*ptr))
	ptr++;
    while (*ptr && isblank(*ptr))
	ptr++;

    /* second number -- wait_ticks */
    *wait_ticks = atoll(ptr);
    while (*ptr && isdigit(*ptr))
	ptr++;
    while (*ptr && isblank(*ptr))
	ptr++;

    /* last number -- nran */
    *nran = atoi(ptr);
}

/*
 * get_id() -- extract the id field from that /proc/<pid>/stat file
 */
void get_id(char *buf, char *id)

{
    char *ptr;

    /* sanity */
    if (!buf || !id)
	return;

    ptr = index(buf, ')') + 1;
    *ptr = 0;
    strcpy(id, buf);
    *ptr = ' ';

    return;
}

int main(int argc, char *argv[])
{
    int c;
    unsigned int sleeptime = 5, pid = 0, verbose = 0;
    char id[32];
    unsigned long long run_ticks, wait_ticks, nran;
    unsigned long long orun_ticks=0, owait_ticks=0, oran=0;

    Progname = argv[0];
    id[0] = 0;
    while ((c = getopt(argc,argv,"s:v")) != -1) {
	switch (c) {
	    case 's':
		sleeptime = atoi(optarg);
		break;
	    case 'v':
		verbose++;
		break;
	    default:
		usage();
	}
    }

    if (optind < argc) {
	pid = atoi(argv[optind]);
    }

    if (!pid)
	usage();

    sprintf(statname,"/proc/%d/stat", pid);
    if (fp = fopen(statname, "r")) {
	if (fgets(procbuf, sizeof(procbuf), fp))
	    get_id(procbuf,id);
	fclose(fp);
    }

    /*
     * now just spin collecting the stats
     */
    sprintf(statname,"/proc/%d/schedstat", pid);
    while (fp = fopen(statname, "r")) {
	    if (!fgets(procbuf, sizeof(procbuf), fp))
		    break;

	    get_stats(procbuf, &run_ticks, &wait_ticks, &nran);

	    if (verbose)
		printf("%s %llu(%d) %llu(%d) %d(%d) avgrun %4.2f avgwait %4.2f\n",
		    id, run_ticks, run_ticks - orun_ticks,
		    wait_ticks, wait_ticks - owait_ticks,
		    nran, nran - oran,
		    nran - oran ?
			(double)(run_ticks-orun_ticks)/(nran - oran) : 0,
		    nran - oran ?
			(double)(wait_ticks-owait_ticks)/(nran - oran) : 0);
	    else
		printf("%s avgrun=%4.2fms avgwait=%4.2fms\n",
		    id, nran - oran ?
			(double)(run_ticks-orun_ticks)/(nran - oran) : 0,
		    nran - oran ?
			(double)(wait_ticks-owait_ticks)/(nran - oran) : 0);
	    fclose(fp);
	    oran = nran;
	    orun_ticks = run_ticks;
	    owait_ticks = wait_ticks;
	    sleep(sleeptime);
    }
    if (id[0])
	printf("Process %s has exited.\n", id);
    else 
	printf("Process %d does not exist.\n", pid);
    exit(0);
}

