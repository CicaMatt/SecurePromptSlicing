#include <stdio.h>
#include "mod_wsgi/include/mod_wsgi-api.h"

static int handle_request(request_rec *r) {
    const char *html = "<html><body>Hello, WSGI World!</body></html>";
    r->content_type = "text/html";
    ap_rputs(html, r);
    return OK;
}

void register_hooks(apr_pool_t *pool) {
    static struct initializer_context ctx;

    ctx.pool = pool;
    ap_register_output_filter("wsgi", NULL, NULL, AP_FTYPE_RESOURCE);

    if (ap_hook_post_config(NULL, NULL, NULL, &ctx)) {
        return;
    }

    ap_add_version_component(AP_SERVER_STRING, "WSGI Example");

    apr_pool_cleanup_register(pool, &ctx, cleanup_context, apr_pool_cleanup_null);
}

static int init_module(void) {
    return register_hooks(apr_global_pool());
}

module AP_MODULE_DECLARE_DATA wsgi_mod = {
    STANDARD20_MODULE_STUFF,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    init_module
};

int main(int argc, char **argv) {
    ap_server_conf *sconf;
    apr_initialize();
    atexit(apr_terminate);
    apr_pool_create(&sconf->process_slot, NULL);

    sconf->server_hostname = "localhost";
    sconf->port = 8080;

    handle_request(NULL); // Simulating a request call for demonstration

    return 0;
}