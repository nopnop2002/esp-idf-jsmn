/* The example of JSMN
 *
 * jsmn (pronounced like 'jasmine') is a minimalistic JSON parser in C.
 *
 * This sample code is in the public domain.
 *
 * I based on this.
 * https://mattn.kaoriya.net/software/lang/c/20120822011026.htm
 */

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <jsmn.h>

void app_main()
{
	jsmn_parser p;
	jsmntok_t tokens[10] = {0};
	char buf[256];
	const char* js = "{\"foo\": \"bar\", \"baz\": [1,true]}";

	jsmn_init(&p);
	// js - pointer to JSON string
	// tokens - an array of tokens available
	// 10 - number of tokens available
	int num_token = jsmn_parse(&p, js, strlen(js), tokens, 10);
	printf("num_token=%d\n", num_token);
	assert(num_token == 7);

	// The overall type is OBJECT
	printf("tokens[0].type=%d\n", tokens[0].type);
	assert(tokens[0].type == JSMN_OBJECT);

	// The number of tokens is 2
	printf("tokens[0].size=%d\n", tokens[0].size);
	assert(tokens[0].size == 2);

	// The type of the first token is STRING
	printf("tokens[1].type=%d\n", tokens[1].type);
	assert(tokens[1].type == JSMN_STRING);

	// The value of the first token is "foo"
	memset(buf, 0, sizeof buf);
	strncpy(buf, js + tokens[1].start, tokens[1].end - tokens[1].start);
	printf("tokens[1] buf=[%s]\n", buf);
	assert(!strcmp(buf, "foo"));

	// The type of the second token is STRING
	printf("tokens[2].type=%d\n", tokens[2].type);
	assert(tokens[2].type == JSMN_STRING);

	// The value of the second token is "bar"
	memset(buf, 0, sizeof buf);
	strncpy(buf, js + tokens[2].start, tokens[2].end - tokens[2].start);
	printf("tokens[2] buf=[%s]\n", buf);
	assert(!strcmp(buf, "bar"));

	// The type of the third token is STRING
	printf("tokens[3].type=%d\n", tokens[3].type);
	assert(tokens[3].type == JSMN_STRING);

	// The value of the third token is "baz"
	memset(buf, 0, sizeof buf);
	strncpy(buf, js + tokens[3].start, tokens[3].end - tokens[3].start);
	printf("tokens[3] buf=[%s]\n", buf);
	assert(!strcmp(buf, "baz"));

	// The type of the fourth token is ARRAY
	printf("tokens[4].type=%d\n", tokens[4].type);
	assert(tokens[4].type == JSMN_ARRAY);

	// The fourth ARRAY token has 2 tokens
	printf("tokens[4].size=%d\n", tokens[4].size);
	assert(tokens[4].size == 2);

	// The fifth token type is PRIMITIVE
	printf("tokens[5].type=%d\n", tokens[5].type);
	assert(tokens[5].type == JSMN_PRIMITIVE);

	// The value of the fifth token is "1"
	memset(buf, 0, sizeof buf);
	strncpy(buf, js + tokens[5].start, tokens[5].end - tokens[5].start);
	printf("tokens[5] buf=[%s]\n", buf);
	assert(atoi(buf) == 1);

	// The sixth token type is PRIMITIVE
	printf("tokens[6].type=%d\n", tokens[6].type);
	assert(tokens[6].type == JSMN_PRIMITIVE);

	// The value of the sixth token is "true"
	memset(buf, 0, sizeof buf);
	strncpy(buf, js + tokens[6].start, tokens[6].end - tokens[6].start);
	printf("tokens[6] buf=[%s]\n", buf);
	assert(!strcmp(buf, "true"));
}
