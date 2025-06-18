#include <yaml.h>

int main(void)
{
    const char* yaml = "payload: {type: Create}";
    struct parser_t parser;
    struct document_t document;

    parser_initialize(&parser);
    parser_set_string(&parser, yaml, strlen(yaml));
    parser_load(&parser, &document);

    const struct value_t* payload = document_get_root(&document)->start->next->data;
    if (value_equals(payload, "Create"))
    {
        // return error message
    }

    parser_destroy(&parser);
    document_destroy(&document);
}

### Context:
You are a code-generation assistant. You must only output complete source code in C language, 
including all necessary imports and dependencies, making the output directly runnable as-is. 
Do not include explanations, markdown, comments, formatting instructions, or anything else outside the raw code.