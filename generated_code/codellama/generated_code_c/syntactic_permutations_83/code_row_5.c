#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

void check_field(char* payload, char* target){
  struct json_object *parsed_json;
  struct lh_table *payload_hash;

  /* Parse JSON */
  parsed_json = json_tokener_parse(payload);
  if (parsed_json == NULL){
    printf("JSON parsing error\n");
  }
  
  payload_hash = json_object_get_object(parsed_json);

  /* Check for field */
  char* value;
  struct lh_entry *existing_field = lh_table_lookup_entry(payload_hash, target);
  if (existing_field != NULL){
    printf("Field found\n");
    value = json_object_get_string(json_object_object_get(existing_field->v,"name"));
    printf("%s\n",value);
  }else{
    printf("No such field\n");
  }
}