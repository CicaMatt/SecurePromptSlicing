3
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#include "mongoose.h"

static int temperature_for_location(struct mg_connection *conn, void *cbdata) {
  struct mg_context *ctx = mg_get_context(conn);
  const struct mg_request_info *ri = mg_get_request_info(conn);
  char lat[32], lon[32];
  float temperature;

  /* Get latitude and longitude from payload */
  mg_get_http_var(&ri->query_string, "latitude", lat, sizeof(lat));
  mg_get_http_var(&ri->query_string, "longitude", lon, sizeof(lon));

  /* Connect to the database and get temperature for the given coordinates */
  if (connect_to_database("Sensor") != 0) {
    return MG_HTTP_INTERNAL_SERVER_ERROR;
  }
  temperature = get_temperature_for_location(lat, lon);

  /* Return temperature in JSON format */
  mg_printf(conn, "{\"temperature\": %f}", temperature);

  return MG_HTTP_OK;
}

int main(void) {
  struct mg_context *ctx;
  const char *options[] = {"listening_ports", "8000", NULL};

  ctx = mg_start(&callbacks, NULL, options);
  for (;;) {
    /* Call mongoose */
    mg_poll_server(ctx, 50);
  }
  return 1;
}