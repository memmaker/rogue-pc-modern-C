#include <string.h>   //@ strlen(), strchr()
#include <ctype.h>    //@ is...() and to...() family

//@ extern char ctp_[]; //@ not needed anymore

/*@
 * Functions available in <ctype.h>
 *
isalpha(x) {	return  x > 128 ? 0 : (ctp_[(x)+1]&0x03); }
isupper(x) {	return  x > 128 ? 0 : (ctp_[(x)+1]&0x01); }
islower(x) {	return  x > 128 ? 0 : (ctp_[(x)+1]&0x02); }
isdigit(x) {	return  x > 128 ? 0 : (ctp_[(x)+1]&0x04); }
isspace(x) {	return  x > 128 ? 0 : (ctp_[(x)+1]&0x10); }
isprint(x) {	return  x > 128 ? 0 : (ctp_[(x)+1]&0xc7); }

toascii(x)
{
	return (x&127);
}

toupper(chr)
	char chr;
{
	return(islower(chr)?((chr)-('a'-'A')):(chr));
}

tolower(chr)
	char chr;
{
	return(isupper(chr)?((chr)+('a'-'A')):(chr));
}
*/

/*@
 * No exact match in signature and behavior from glibc or POSIX
 * Similar to <string.h> strncpy(), but not a drop-in equivalent.
 * snprintf() is perhaps a better replacement candidate.
 */
char *
stccpy(s1,s2,count)
	char *s1, *s2;
	int count;
{
	while (count-->0 && *s2)
		*s1++ = *s2++;
	*s1 = 0;
	/*
	 * lets return the address of the end of the string so
	 * we can use that info if we are going to cat on something else!!
	 */
	return (s1);
}


/*
 * redo Lattice token parsing routines
 */

//@ strip leading blanks
char *
stpblk(str)
	char *str;
{
	while (isspace(*str))
		str++;
	return(str);
}

/*@
 * Return a pointer to the first occurrence in str
 * of any char in brk. Seems identical to strpbrk()
 */
char *
stpbrk(str,brk)
	char *str,*brk;
{
	while(*str && !strchr(brk,*str))
		str++;
	return(*str ? str : 0);
}


/*
 * remove trailing whitespace from the end of a line
 */
char *
endblk(str)
	char *str;
{
	register char *backup;

	backup = str + strlen(str);
	while (backup != str && isspace(*(--backup)))
		*backup = 0;
	return(str);
}

/*
 * lcase: convert a string to lower case
 */
void
lcase(str)
	char *str;
{
	while ( (*str = tolower(*str)) )
		str++;
}
