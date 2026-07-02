# esp-idf-jsmn
IDF component registry includes jsmn JSON parser C Library.   
https://components.espressif.com/components/espressif/jsmn   

However, unfortunately there is no sample code for ESP-IDF.   
This is example JSON parser using jsmn.   

The parsed result is an array of tokens.   
Each token consists of the following:   
```
typedef struct {
	jsmntype_t type; // Token type
	int start;       // Token start position
	int end;         // Token end position
	int size;        // Number of child (nested) tokens
} jsmntok_t;
```

Token types are described by jsmntype_t:   
```
typedef enum {
	JSMN_UNDEFINED = 0,
	JSMN_OBJECT = 1 << 0,
	JSMN_ARRAY = 1 << 1,
	JSMN_STRING = 1 << 2,
	JSMN_PRIMITIVE = 1 << 3
} jsmntype_t;
```

# Software requirements   
ESP-IDF V5.0 or later.   
ESP-IDF V4.4 release branch reached EOL in July 2024.   

# Installation
```
git clone https://github.com/nopnop2002/esp-idf-jsmn
cd esp-idf-jsmn
idf.py flash monitor
```

# Configuration
There is no MENU ITEM where this application is peculiar.   

# JSON string to parse
```
{"foo": "bar", "baz": [1,true]}
```

If you parse this JSON, jsmn generates the following tokens.   
|Token|Type|Value|Size|
|:---|:---|:---|:---|
|tokens[0]|JSMN_OBJECT||2|
|tokens[1]|JSMN_STRING|"foo"||
|tokens[2]|JSMN_STRING|"bar"||
|tokens[3]|JSMN_STRING|"baz"||
|tokens[4]|JSMN_ARRAY||2|
|tokens[5]|JSMN_PRIMITIVE|1||
|tokens[6]|JSMN_PRIMITIVE|true||

# Console output
```
num_token=7
tokens[0].type=1
tokens[0].size=2
tokens[1].type=4
tokens[1] buf=[foo]
tokens[2].type=4
tokens[2] buf=[bar]
tokens[3].type=4
tokens[3] buf=[baz]
tokens[4].type=2
tokens[4].size=2
tokens[5].type=8
tokens[5] buf=[1]
tokens[6].type=8
tokens[6] buf=[true]
```

# API
- Create JSON parser over an array of token.   
```
void jsmn_init(jsmn_parser *parser);
```

- Run JSON parser.   
It parses a JSON data string into and array of tokens.   
```
int jsmn_parse(jsmn_parser *parser, const char *js, const size_t len,
jsmntok_t *tokens, const unsigned int num_tokens);
```

A positive return value represents the number of tokens actually used by the jsmn_parse parser.   
If you pass NULL instead of a token array, the parsing results are not stored; instead, the function returns the number of tokens required to parse the specified string.   
This is useful when the number of tokens to allocate is not yet known.   
If a problem occurs, a negative value is returned.   
The error will be one of the following:   
```
enum jsmnerr {
    /* Not enough tokens were provided */
    JSMN_ERROR_NOMEM = -1,
    /* Invalid character inside JSON string */
    JSMN_ERROR_INVAL = -2,
    /* The string is not a full JSON packet, more bytes expected */
    JSMN_ERROR_PART = -3
};
```

