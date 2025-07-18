#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "appweb/appweb.h"

    int main(int argc, char **argv) {
        MaServer *server;
        MaHost *host;
        MaRoute *route;

        /*
            Load the appweb module for dynamic loading
         */
        if (mprCreate(argc, argv, MPR_USER_EVENTS_THREAD) == NULL) {
            mprError("Can't create appweb server object");
            return MPR_ERR_CANT_CREATE;
        }

        /*
            Create a server object
         */
        if ((server = maCreateServer()) == 0) {
            mprError("Can't create server object");
            return MPR_ERR_CANT_CREATE;
        }

        /*
            Define the server parameters
         */
        maSetServerHome(server, ".", MPR_USER);
        if (maStartServer(server) < 0) {
            mprError("Can't start server");
            return MPR_ERR_CANT_START;
        }

        /*
            Create a host for default requests
         */
        if ((host = maCreateHost(server, "default")) == 0) {
            mprError("Can't create host");
            return MPR_ERR_CANT_CREATE;
        }

        /*
            Create routes to serve the API and static files
         */
        if ((route = maCreateRoute(host, "/api")) == 0) {
            mprError("Can't create route");
            return MPR_ERR_CANT_CREATE;
        }
    }