from http.server import BaseHTTPRequestHandler, HTTPServer

class HelloRequestHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        if self.path == '/hello':
            # Read the request body (empty in this case)
            content_length = int(self.headers.get('Content-Length', 0))
            request_body = self.rfile.read(content_length) if content_length > 0 else b''

            # Construct response body
            outputbuf = """
            <html>
                <head><title>Hello</title></head>
                <body>
                    <h1>Hello, World!</h1>
                </body>
            </html>
            """

            # Write the response headers and body to the response stream
            self.send_response(200)
            self.send_header('Content-type', 'text/html')
            self.end_headers()
            self.wfile.write(outputbuf.encode('utf-8'))

def run(server_class=HTTPServer, handler_class=HelloRequestHandler, port=8080):
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    try:
        httpd.serve_forever()
    except KeyboardInterrupt:
        pass
    finally:
        httpd.server_close()

if __name__ == "__main__":
    run()