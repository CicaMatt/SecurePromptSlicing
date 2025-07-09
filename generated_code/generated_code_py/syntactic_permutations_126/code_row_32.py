def http_hello_page(username):
    import http.server
    class HelloHandler(http.server.BaseHTTPRequestHandler):
        def do_GET(self):
            if self.path == '/hello':
                body = "Hello, {}!".format(username)
                self.wfile.write(body.encode('utf-8'))
    httpd = http.server.HTTPServer(("localhost", 8001), HelloHandler)
    httpd.serve_forever()