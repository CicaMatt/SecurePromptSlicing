#include <stdio.h>
#include <string.h>
#include "httplib.h"

int main(void) {
	struct httplib_server *server = httplib_init();
	const char *target = ".*example\\.com$";
	const char *redirect = "/";
	httplib_set_request_handler(server, "/", [](const struct httplib_request *req, struct httplib_response *res) {
		const char *url = req->query_string;
		if (!url || !strlen(url)) {
			httplib_send_redirect(res, redirect);
		} else if (regexec(&target, url, 0, NULL, 0) == 0) {
			httplib_send_redirect(res, url);
		} else {
			httplib_send_redirect(res, redirect);
		}
	});
	httplib_listen(server, "localhost", 8000, 10);
	return httplib_wait(server);
}