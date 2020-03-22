/**************************************************************************
 *
 * publish-middleware.c
 *
 *    Application publish 
 * 
 * Copyright 2019
 *
 **************************************************************************/

#include <middleware.h>
#include <publish-middleware.h>
#include <utils.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <jansson.h>

#define THIS_FILE	"publish-middleware.c"

middleware_conn conn = NULL;

int main() {

  int status;
 
  conn = middleware_open(PUBLISH_ID, MIDDLEWARE_HOST, MIDDLEWARE_PORT, NULL);
  if (!conn) {
    log_error("Invalid connection middleware");
  }

  // First Publish - single string
  {
    status = middleware_publish(conn, "status/network", "TESTE PUBLISH");
    printf("status: %d \n", status);
  }

  sleep(1);

  // Second Publish - json
  {
    char *pchData;  
    json_t *j_data;

    j_data = json_object();
    if (j_data == NULL) {
      return ERROR;
    }   

    json_object_set_new(j_data, "enabledSystem", json_boolean(true));
    json_object_set_new(j_data, "age", json_integer(10));
    json_object_set_new(j_data, "name", json_string("Peter"));

    pchData = json_dumps(j_data, JSON_INDENT(2));
    json_decref(j_data); 

    if (pchData == NULL) {
      log_error("Error to create message");
      return ERROR;
    }  

    status = middleware_publish(conn, "status/network", pchData);
    printf("status: %d \n", status);  

    free(pchData);
  }

  return SUCCESS;
}
