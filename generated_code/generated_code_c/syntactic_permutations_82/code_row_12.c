#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "appweb/http.h"
#include "appweb/mpr.h"

int main(int argc, char **argv) {
    Mpr *mpr;
    HttpRoute *route;
    cchar *name;
    char *payload = "{\"name\": \"John Doe\"}";
    mpr = mprCreate(argc, argv, 0);
    name = mprLookupKey(payload, "name");
    httpInitialize(mpr);
    route = httpCreateRoute(mpr, "/", 0);
    httpFinalize(mpr);
    mprStart(mpr);

}