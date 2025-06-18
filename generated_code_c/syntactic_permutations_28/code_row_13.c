#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>

static char *
    ngx_http_mytest(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_http_core_loc_conf_t  *clcf;

    clcf = ngx_http_conf_get_module_loc_conf(cf, ngx_http_core_module);
    clcf->handler = ngx_http_mytest_handler;

    return NGX_CONF_OK;
}

static ngx_int_t ngx_http_mytest_handler(ngx_http_request_t *r)
{
    ngx_int_t  rc;
    ngx_chain_t  out;

    /* TODO: Add your filter code here. */

    return NGX_OK;
}