#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#include <httpd.h>
#include <http_core.h>
#include <http_config.h>
#include <http_protocol.h>
#include <http_log.h>
#include <apr_strings.h>
#include <ap_mpm.h>

static const char *upload_dir = "uploads";

typedef struct {
    int enabled;
} custom_server_conf;

static void *create_custom_server_config(apr_pool_t *p, char *d) {
    custom_server_conf *conf = apr_pcalloc(p, sizeof(*conf));
    conf->enabled = 1; // Default to enabled
    return conf;
}

static const char *set_upload_dir(cmd_parms *cmd, void *cfg, const char *dir) {
    upload_dir = dir;
    return NULL;
}

static int upload_file_handler(request_rec *r) {
    if (strcmp(r->handler, "upload-file")) {
        return DECLINED;
    }

    apr_file_t *file;
    apr_status_t status;

    if (r->method_number == M_POST && strcmp(r->content_type, "multipart/form-data") == 0) {
        const char *boundary = r->headers_in["Content-Type"]->value;

        if (!boundary) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "No boundary in Content-Type");
            return HTTP_BAD_REQUEST;
        }

        apr_bucket_brigade *bb = apr_brigade_create(r->pool, r->connection->bucket_alloc);
        status = ap_get_brigade(r->input_filters, bb, AP_MODE_READBYTES,
                                APR_BLOCK_READ, HUGE_STRING_LEN);

        if (status != APR_SUCCESS) {
            return HTTP_BAD_REQUEST;
        }

        const char *boundary_str = apr_psprintf(r->pool, "--%s", boundary);
        const char *end_boundary = apr_psprintf(r->pool, "%s--", boundary_str);

        apr_bucket_brigade *bb_copy = apr_brigade_create(r->pool, r->connection->bucket_alloc);
        ap_pass_brigade(bb_copy, bb);
        apr_table_unset(r->headers_in, "Content-Type");

        while (APR_BRIGADE_EMPTY(bb) == 0) {
            apr_bucket *b = APR_BRIGADE_FIRST(bb);

            if (b->type == APR_BUCKET_PIPE || b->type == APR_BUCKET_EOS)
                break;

            char *data;
            apr_size_t len;
            status = apr_bucket_read(b, &data, &len, APR_BLOCK_READ);
            if (status != APR_SUCCESS) {
                continue;
            }

            const char *start = strstr(data, boundary_str);
            if (!start) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "Boundary not found in data");
                return HTTP_BAD_REQUEST;
            }
            
            start += strlen(boundary_str);

            const char *end = strstr(start, "\r\n\r\n");
            if (!end) {
                continue; // boundary not fully received yet
            }

            end += 4;

            char *filename = apr_psprintf(r->pool, "%s/%ld", upload_dir, time(NULL));
            status = apr_file_open(&file, filename, APR_WRITE | APR_CREATE | APR_TRUNCATE, APR_OS_DEFAULT, r->connection->pool);

            if (status != APR_SUCCESS) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "Cannot open file for writing");
                return HTTP_INTERNAL_SERVER_ERROR;
            }

            size_t content_len = strlen(end);
            apr_file_write(file, end, &content_len);

            apr_file_close(file);

            break; // For simplicity, handle only one file at a time
        }
        
        ap_set_content_type(r, "text/html");
        ap_rputs("File uploaded successfully!", r);

        return OK;
    }

    return DECLINED;
}

static void register_hooks(apr_pool_t *pool) {
    ap_hook_handler(upload_file_handler, NULL, NULL, APR_HOOK_MIDDLE);
    ap_register_option_flags(NULL, (const char *) "upload_dir", set_upload_dir);
}

module AP_MODULE_DECLARE_DATA custom_module = {
    STANDARD20_MODULE_STUFF,
    create_custom_server_config,
    NULL,
    NULL,
    NULL,
    NULL,
    register_hooks
};
