#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>

size_t ft_strlen(char* s);
char* ft_strcpy(char* dest, char* str);
int ft_strcmp(char* s1, char* s2);
char* ft_strdup(char* str);
ssize_t ft_write(int fd, void*str, size_t size);
ssize_t ft_read(int fd, void*str, size_t size);

static int total;
static int ok;

int assertString(char* exp, char* got)
{
	int res = 0;
	if (strcmp(exp, got) == 0)
	{
		res = 1;
		printf(" \033[32mOK");
	}
	else
	{
		printf(" \033[31mKO exp: '%s', got: '%s'", exp, got);
	}
	printf("\033[0m\n");
	return res;
}

int assertSize(int exp, int got)
{
	int res = 0;
	if (exp == got)
	{
		res = 1;
		printf(" \033[32mOK");
	}
	else
	{
		printf(" \033[31mKO exp: %d, got: %d", exp, got);
	}
	printf("\033[0m\n");
	return res;
}

void TestStrlen(char* str)
{
	total++;
	size_t expLen = strlen(str);
	printf("  [%s]: ", expLen < 20 ? str : "too large");
	ok += assertSize(strlen(str), ft_strlen(str));
}

void TestStrcpy(char* str)
{
	total++;
	assert(strlen(str) < 20);
	char expBuf[20];
	char testBuf[20];
	printf("  [%s]: ", str);
	strcpy(expBuf, str);
	char* testRet = ft_strcpy(testBuf, str);
	assert(testBuf == testRet);
	ok += assertString(expBuf, testBuf);
}

void TestStrdup(char* str)
{
	total++;
	printf("  [%s]: ", str);
	char* expRet = strdup(str);
	char* testRet = ft_strdup(str);
	ok += assertString(expRet, testRet);
	free(expRet);
	free(testRet);
}

void TestStrcmp(char* str1, char* str2)
{
	total++;
	printf("  [%s | %s]: ", str1, str2);
	ok += assertSize(strcmp(str1, str2), ft_strcmp(str1, str2));
}

void TestWrite(char* str)
{
	total++;
	printf("  [%s]: ", str);
	if (!str)
	{
		ssize_t expErrorRet = write(-1, str, 0);
		int expErrno = errno;
		ssize_t testErrorRet = ft_write(-1, str, 0);
		int testErrno = errno;
		assertSize(expErrorRet, testErrorRet);
		ok += assertSize(expErrno, testErrno);
		return;
	}

	assert(strlen(str) < 20);

	char expBuf[20];
	char testBuf[20];
	int fd[2];
	pipe(fd);
	ssize_t expSize = write(fd[1], str, strlen(str));
	read(fd[0], expBuf, expSize);
	ssize_t testSize = ft_write(fd[1], str, strlen(str));
	read(fd[0], testBuf, testSize);
	assertSize(expSize, testSize);
	ok += assertString(expBuf, testBuf);
}

void TestRead(char* str)
{
	total++;
	printf("  [%s]: ", str);

	if (!str)
	{
		ssize_t expErrorRet = read(-1, str, 0);
		int expErrno = errno;
		ssize_t testErrorRet = ft_read(-1, str, 0);
		int testErrno = errno;
		assertSize(expErrorRet, testErrorRet);
		ok += assertSize(expErrno, testErrno);
		return;
	}

	assert(strlen(str) < 20);

	char expBuf[20];
	char testBuf[20];
	int fd[2];
	pipe(fd);
	write(fd[1], str, strlen(str));
	ssize_t testSize = ft_read(fd[0], testBuf, strlen(str));
	write(fd[1], str, strlen(str));
	ssize_t expSize = read(fd[0], expBuf, strlen(str));
	assertSize(expSize, testSize);
	ok += assertString(expBuf, testBuf);
}


int main(void)
{
	char ptrString[] = "ptrString";
	printf("------- strlen --------\n");
	TestStrlen("Tast");
	TestStrlen("adassdadasdadadsdasdasd");
	TestStrlen("");
	TestStrlen(ptrString);
	/* TestStrlen(file); */

	printf("------- strcpy --------\n");
	TestStrcpy("asda");
	TestStrcpy("Holas Que tal");
	TestStrcpy("");

	printf("------- strcmp --------\n");
	TestStrcmp("asda", "asda");
	TestStrcmp("Hola", "asda");
	TestStrcmp("", "asda");
	TestStrcmp("asda", "");


	printf("------- strdup --------\n");
	TestStrdup("asda");
	TestStrdup("Holas Que tal");
	TestStrdup("");

	printf("------- write --------\n");
	TestWrite("Hola");
	TestWrite(NULL);
	printf("------- read --------\n");
	TestRead("Hola");
	TestRead(NULL);

	printf("\n ok: %d/%d\n", ok, total);
}
