#include <assert.h>
#include <setjmp.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CuTest.h"
#include "adt_str.h"
#include "CMemLeak.h"

void Test_adt_str_constructor(CuTest* tc)
{
	adt_str_t *str = adt_str_new();
	CuAssertPtrNotNull(tc, str);
	CuAssertStrEquals(tc,"",adt_str_cstr(str));
	adt_str_delete(str);
}

void Test_adt_str_push(CuTest* tc){
	adt_str_t *str = adt_str_new();
	CuAssertPtrNotNull(tc, str);
	int i;
	int len = 0;
	for(i = 'A'; i <= 'Z'; i++){
		len++;
		adt_str_push(str,i);
		CuAssertIntEquals(tc,len,strlen(adt_str_cstr(str)));
		CuAssertIntEquals(tc,len,adt_str_len(str));
	}

	CuAssertStrEquals(tc,"ABCDEFGHIJKLMNOPQRSTUVWXYZ",adt_str_cstr(str));

	adt_str_delete(str);
}

void Test_adt_str_cdup(CuTest* tc){
	adt_str_t *str = adt_str_dup_cstr("Hello World");
	CuAssertPtrNotNull(tc, str);
	CuAssertIntEquals(tc,11,adt_str_len(str));
	CuAssertStrEquals(tc,"Hello World",adt_str_cstr(str));
	adt_str_delete(str);
}

void Test_adt_str_cappend(CuTest* tc){
	adt_str_t *str = adt_str_dup_cstr("Hello");
	CuAssertPtrNotNull(tc, str);
	CuAssertIntEquals(tc,5,adt_str_len(str));
	CuAssertStrEquals(tc,"Hello",adt_str_cstr(str));
	adt_str_append_cstr(str," World");
	CuAssertIntEquals(tc,11,adt_str_len(str));
	CuAssertStrEquals(tc,"Hello World",adt_str_cstr(str));
	adt_str_delete(str);
}

void test_adt_str_copy_range(CuTest* tc){
	char buf[80];
	strcpy(buf,"Hello World!");
	const char *a=buf,*b=buf+5;
	const char *c=buf+6,*d=buf+12;
	adt_str_t *str1 = adt_str_new();
	adt_str_t *str2 = adt_str_new();
	CuAssertPtrNotNull(tc,str1);
	CuAssertPtrNotNull(tc,str2);
	adt_str_copy_range(str1,a,b);
	adt_str_copy_range(str2,c,d);
	CuAssertStrEquals(tc,"Hello",adt_str_cstr(str1));
	CuAssertStrEquals(tc,"World!",adt_str_cstr(str2));
	adt_str_delete(str1);
	adt_str_delete(str2);
}


CuSuite* testsuite_adt_str(void)
{
	CuSuite* suite = CuSuiteNew();

	SUITE_ADD_TEST(suite, Test_adt_str_constructor);
	SUITE_ADD_TEST(suite, Test_adt_str_push);
	SUITE_ADD_TEST(suite, Test_adt_str_cdup);
	SUITE_ADD_TEST(suite, Test_adt_str_cappend);
	SUITE_ADD_TEST(suite, test_adt_str_copy_range);

	return suite;
}
